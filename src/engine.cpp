#include "chess.hpp"
#include "engine.hpp"
#include "evaluation.hpp"
#include "reader.hpp"
#include <filesystem>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include "utils.hpp"
#include "tt.hpp"
#include "timemanagement.hpp"

namespace engine
{
    constexpr auto TARGET_FEN = "r1bq1rk1/ppp2ppp/5n2/2b1p3/Q2p4/1PP1PN2/P1nPKPPP/R1BN1B1R b - - 2 10";
    constexpr int MAX_EXTENSIONS = 0; // BUG: extensions cause node explosion
    constexpr int QUIESCENCE_DEPTH = 0;
    constexpr int DELTA = 200;
    bool log_TT = false;
    int history[2][64][64];
    int nodes = 0;

    bool abort_due_to_time = false;
    bool manager_exists = false;

    Reader::Book book;
    TranspositionTable table; // TODO: add tests fr this
    std::optional<TimeManagement::TimeManager> manager; // TODO: add tests fr this

    const int initial_alpha = std::numeric_limits<int>::min() + 1; // to avoid wraparound bugs
    const int initial_beta = std::numeric_limits<int>::max();

    /**
 *
 * @param board
 * @return whether any White pawns are on 7th rank OR any Black pawns on 2nd rank,
 * i.e. they are one move away from promoting.
 * The main use is for passed pawn search extensions.
 */
    inline bool is_pawns_near_promotion(const chess::Board& board)
    {
        return
            0x00FF000000000000ULL & board.pieces(chess::PieceType::PAWN, chess::Color::BLACK).getBits() ||
            0x000000000000FF00ULL & board.pieces(chess::PieceType::PAWN, chess::Color::WHITE).getBits();
    }


    /**
     *
     * @param move
     * @return Whether it is a promotion or not
     */
    inline bool is_promotion(const chess::Move& move)
    {
        return move.typeOf() == chess::Move::PROMOTION;
    }

    // NOLINTBEGIN
    /**
     *
     * @param board The current game state
     * @return If current node is terminal, i.e. the game has ended
     */
    inline bool game_over(const chess::Board& board)
    {
        chess::Movelist moves;
        chess::movegen::legalmoves(moves, board);
        if (moves.empty() || board.isHalfMoveDraw() || board.isInsufficientMaterial() || board.isRepetition())
        {
            return true;
        }

        return false;
    }

    // NOLINTEND

    /**
     *
     * @param alpha Alpha, start with initial_alpha if not using aspiration windows
     * @param beta Beta, start with initial_beta if not using aspiration windows
     * @param board Board to evaluate
     * @param ply Current ply, used for mate evals. (default is 0)
     * @param q_manager
     * @return The score of the position after evaluating to a quiescent position (no captures).
     */
    int QuiescenceSearch(int alpha, const int beta, chess::Board& board, const int ply,
                         const std::optional<TimeManagement::TimeManager>& q_manager)
    {
        if (q_manager.has_value() && !q_manager->time_remaining())
        {
            abort_due_to_time = true;
            return 0;
        }
        nodes++;

        const uint64_t zobrist = board.hash();
        if (const auto ttEntry = table.find_usable_entry(alpha, beta, QUIESCENCE_DEPTH, zobrist, ply); ttEntry.
            has_value())
        {
            return std::get<0>(ttEntry.value());
        }

        const int original_alpha = alpha;
        int best_value = evaluation::main_eval(board, ply);

        if (best_value >= beta)
        {
            return best_value;
        }

        if (best_value > alpha)
        {
            alpha = best_value;
        }

        chess::Movelist capture_moves;
        chess::movegen::legalmoves<chess::movegen::MoveGenType::CAPTURE>(capture_moves, board);
        utils::order_capture_moves(capture_moves, board);

        for (const auto& move : capture_moves)
        {
            if (!board.inCheck() && !evaluation::is_endgame(board) && !is_promotion(move) &&
                best_value + utils::piece_values[board.at(move.to()).type()] + DELTA < alpha)
                continue;

            board.makeMove(move);
            const int score = -QuiescenceSearch(-beta, -alpha, board, ply + 1, q_manager);
            board.unmakeMove(move);


            if (score >= beta)
            {
                table.put(zobrist, chess::Move::NO_MOVE, QUIESCENCE_DEPTH, score, NodeType::LOWERBOUND, ply);
                return score;
            }
            if (score > best_value)
            {
                best_value = score;
            }
            if (alpha < score)
            {
                alpha = score;
            }
        }
        NodeType node_type;
        if (best_value <= original_alpha)
        {
            node_type = NodeType::UPPERBOUND;
        }
        else if (best_value >= beta)
        {
            node_type = NodeType::LOWERBOUND;
        }
        else
        {
            node_type = NodeType::EXACT;
        }

        table.put(zobrist, chess::Move::NO_MOVE, QUIESCENCE_DEPTH, best_value, node_type, ply);

        return best_value;
    }


    /**
     */
    void init_book()
    {
        book.Load("C:/Users/DELL/Documents/mihansolo_bot/gm2600.bin");
    }

    /**
     *
     * @param board Board to find book move for
     * @return A random book move if multiple found, if only one found return that, if none found return std::nullopt
     */
    std::optional<std::string> book_move(const chess::Board& board)
    {
        if (const Reader::BookMoves book_moves = book.GetBookMoves(board.hash()); !book_moves.empty())
        {
            std::string found_move = Reader::ConvertBookMoveToUci(Reader::RandomBookMove(book_moves));
            return found_move;
        }
        return std::nullopt;
    }

    /**
     *
     * @param depth Current search depth
     * @return The null move reduction R for that depth
     */
    inline int reduction_for(const int depth)
    {
        return depth >= 6 ? 3 : 2;
    }

    /**
     *
     * @param board Board to check for
     * @param depth Current search depth
     * @return Whether we can use null move pruning without adverse side effects
     */
    inline bool can_NMP(const chess::Board& board, const int depth)
    {
        const int R = reduction_for(depth);
        return depth >= R
            && depth > R + 1 // need at least one more ply than R
            && board.hasNonPawnMaterial(board.sideToMove())
            && !board.inCheck();
    }


    /**
     *
     * @param PV_Move Current principal variation move; for move ordering
     * @param table1 Transposition table
     * @param board Board to search for
     * @param alpha Alpha (for a/b pruning) - initially set to a very low value
     * @param beta Beta (for a/b pruning) - intially set to a very high value
     * @param last_move The last move made on the board
     * @param depth Current depth - start at 0
     * @param ply Current ply - start at 0
     * @param numExtensions Number of search extensions applied so far
     * @param nega_manager
     * @return A tuple of the believed evaluation and best move in the position
     */
    std::tuple<int, chess::Move> negamax(const std::optional<TimeManagement::TimeManager>& nega_manager,
                                         const chess::Move& PV_Move, TranspositionTable& table1, chess::Board& board,
                                         int alpha,
                                         const int beta,
                                         const chess::Move& last_move,
                                         const int& depth, const int& ply, const int numExtensions)
    {
        nodes++;
        // time management
        if (nega_manager.has_value() && !nega_manager->time_remaining())
        {
            if (board.zobrist() == chess::Board("r1bq1rk1/ppp2ppp/5n2/2b1p3/Q2p4/1PP1PN2/P1nPKPPP/R1BN1B1R b - - 2 10").
                zobrist())
            {
                std::cout << "TARGET FEN REACHED ... AND ABORTED" << std::endl;
            }

            abort_due_to_time = true;
            return std::make_tuple(0, chess::Move::NO_MOVE);
        }

        // transposition table stuff starts
        const int alpha_original = alpha;
        const int beta_original = beta;
        const auto zobrist_key = board.hash();

        if (auto TTResult = table1.find_usable_entry(alpha_original, beta, depth, zobrist_key, ply); TTResult.
            has_value())
        {
            return TTResult.value();
        }
        // transposition stuff ends

        if (depth == 0 || game_over(board)) // NOLINT
        {
            int leaf_eval{QuiescenceSearch(alpha, beta, board, ply, nega_manager)};
            return std::make_tuple(leaf_eval, last_move);
        }
        // NOLINTBEGIN
        chess::Move best_move = chess::Move::NO_MOVE;
        int best_eval = std::numeric_limits<int>::min();

        chess::Movelist legal_moves;
        chess::movegen::legalmoves(legal_moves, board);

        utils::order_moves(history, PV_Move, legal_moves, board);
        /*
        if (can_NMP(board, depth)) // NMP Conditions
        {
            int score = 0;
            chess::Move dummy{};
            board.makeNullMove();
            std::tie(score, dummy) = negamax(PV_Move, table1, board, -beta, -(beta - 1), last_move,
                                             depth - reduction_for(depth) - 1, ply + 1);
            score = -score;
            board.unmakeNullMove();
            if (score >= beta)
            {
                table1.put(zobrist_key,
                           chess::Move::NO_MOVE, // no preferred move
                           depth,
                           score,
                           NodeType::LOWERBOUND); // record that this node is ≥ score

                return std::make_tuple(score, chess::Move::NO_MOVE);
            }
        }
        */

        // SPRT shows NMP is -37.6 elo, so commented out for now
        if (board.getFen() == "r1bq1rk1/ppp2ppp/5n2/2b1p3/Q2p4/1PP1PN2/P1nPKPPP/R1BN1B1R b - - 2 10")
        {
            log_TT = true;
        }

        for (const auto& move : legal_moves)
        {
            int score;
            chess::Move dummy_move{};

            board.makeMove(move);
            int passed_pawn_extension = (is_pawns_near_promotion(board) && numExtensions < MAX_EXTENSIONS) ? 1 : 0;

            std::tie(score, dummy_move) = negamax(nega_manager, PV_Move, table1, board, -beta, -alpha, move,
                                                  (depth + passed_pawn_extension) - 1, ply + 1,
                                                  numExtensions + passed_pawn_extension);
            score = -score;

            board.unmakeMove(move);
            if (board.getFen() == "r1bq1rk1/ppp2ppp/5n2/2b1p3/Q2p4/1PP1PN2/P1nPKPPP/R1BN1B1R b - - 2 10")
            {
                std::cout << "\n\nEvaluating move " << chess::uci::moveToUci(move) << " ... " << "with score: " << score
                    <<
                    std::endl;
            }
            if (score > best_eval)
            {
                best_eval = score;
                best_move = move;

                if (score > alpha)
                    alpha = score;
            }
            if (score >= beta)
            {
                if (!board.isCapture(move))
                {
                    history[board.sideToMove()][move.from().index()][move.to().index()] += depth * depth;
                }

                table1.put(zobrist_key, best_move, depth, best_eval, NodeType::LOWERBOUND, ply);
                return std::make_tuple(best_eval, best_move);
            }
        }
        log_TT = false;
        // Start transposition table stuff
        NodeType node_type;
        if (best_eval <= alpha_original)
        {
            node_type = NodeType::UPPERBOUND;
        }
        else if (best_eval >= beta)
        {
            node_type = NodeType::LOWERBOUND;
        }
        else
        {
            node_type = NodeType::EXACT;
        }
        if (zobrist_key == chess::Board("r1bq1rk1/ppp2ppp/5n2/2b1p3/Q2p4/1PP1PN2/P1nPKPPP/R1BN1B1R b - - 2 10").
            zobrist())
        {
            std::cout << "\n\nNegamax PUTTING entry for zobrist key: " << zobrist_key << std::endl;
            std::cout << "Index: " << table1.address_calc(zobrist_key) << std::endl;
            std::cout << "Best move: " << chess::uci::moveToUci(best_move) << std::endl;
            std::cout << "Score: " << best_eval << std::endl;
            std::cout << "\nParams: " << std::endl;
            std::cout << "Board FEN: " << board.getFen() << std::endl;
            std::cout << "Alpha: " << alpha_original << std::endl;
            std::cout << "Beta: " << beta_original << std::endl;
            std::cout << "Depth: " << depth << std::endl;
            std::cout << "Ply: " << ply << std::endl;
            std::cout << "Last move: " << chess::uci::moveToUci(last_move) << std::endl;
            std::cout << "PV_Move: " << chess::uci::moveToUci(PV_Move) << std::endl;
            std::cout << "\n\n";
        }

        table1.put(zobrist_key, best_move, depth, best_eval, node_type, ply);
        // End transposition table stuff

        return std::make_tuple(best_eval, best_move);
        // NOLINTEND
    }


    /**
     *
     * @param fen Fen for testing, not required
     * @param manager1 The time manager, also not required
     * @param default_depth Depth to use if there is no time manager
     * @param output
     * @return The believed best move in the position as a UCI-formatted string
     */
    std::string search(const std::optional<chess::Board>& fen,
                       const std::optional<TimeManagement::TimeManager>& manager1, const int default_depth,
                       std::ostream& output)
    {
        manager_exists = manager1.has_value();
        int depth = 1;
        int previous_eval = 0;
        nodes = 0; // reset nodes every move

        abort_due_to_time = false;
        chess::Board board;
        chess::Move PV_Move = chess::Move::NO_MOVE;
        chess::Move returned_move{};

        if (fen.has_value())
        {
            board = fen.value();
        }
        if (auto bookmove = book_move(board);
            bookmove.has_value())
        {
            return bookmove.value();
        }
        if (manager_exists)
        {
            int eval = 0;
            while (manager1->time_remaining()) // Iterative deepening
            {
                auto result = negamax(manager1, PV_Move, table, board, initial_alpha, initial_beta,
                                      chess::Move::NO_MOVE, depth,
                                      0);
                returned_move = std::get<1>(result);
                eval = std::get<0>(result);


                if (!abort_due_to_time) // prevents using corrupted moves or eval
                {
                    std::cout << "no abort [line 396][engine::search]\n";
                    PV_Move = returned_move;
                    std::cout << "changed PV Move to: " << chess::uci::moveToUci(PV_Move) <<
                        " [line 398][engine::search]\n";
                    previous_eval = eval;
                }
                else
                {
                    std::cout << "Aborting due to time management[line 402][engine::search]\n";
                }

                depth++;
            }
        }
        // TODO: add UCI E2E tests as part of CTest suite, since there are none currently

        else
        {
            for (int i = 1; i <= default_depth; i++)
            {
                auto result = negamax(std::nullopt, PV_Move, table, board, initial_alpha, initial_beta,
                                      chess::Move::NO_MOVE, i,
                                      0);
                previous_eval = std::get<0>(result);
                PV_Move = std::get<1>(result);
            }
        }

        if (PV_Move == chess::Move::NO_MOVE)
        {
            return "0000";
        }

        const std::string move_uci = chess::uci::moveToUci(PV_Move);
        depth = manager_exists ? depth : default_depth;
        output << "info depth " << depth << " nodes " << nodes << " score cp " << previous_eval << "\n";
        return move_uci;
    }

    /**
     * Start the UCI input/output loop, doesn't have all the options yet but working on it :D
     */
    void start_uci(std::istream& in, std::ostream& out)
    {
        chess::Board board;
        std::string line;

        while (std::getline(in, line))
        {
            std::istringstream iss(line);
            std::string token;
            iss >> token;

            if (token == "uci")
            {
                out << "id name MihanSolo\n";
                out << "id author Mihin Benaragama\n";
                out << "option name Hash type spin default 16 min 1 max 1024\n";
                out << "option name Threads type spin default 1 min 1 max 16\n";
                out << "option name Move Overhead type spin default 30 min 0 max 5000\n";
                out << "option name UCI_ShowWDL type check default false\n";
                out << "option name Ponder type check default false\n";
                out << "option name UCI_AnalyseMode type check default false\n";
                out << "option name UCI_LimitStrength type check default false\n";
                out << "option name UCI_Elo type spin default 1350 min 1350 max 2850\n";
                out << "uciok\n";
            }
            else if (token == "d")
            {
                out << board.getFen() << std::endl;
            }
            else if (token == "isready")
            {
                out << "readyok\n";
            }
            else if (token == "position")
            {
                std::string pos_type;
                iss >> pos_type;

                if (pos_type == "startpos")
                {
                    board.setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
                    manager = TimeManagement::TimeManager(true);
                    manager_exists = true;
                }
                else if (pos_type == "fen")
                {
                    std::string fen, temp;
                    for (int i = 0; i < 6 && iss >> temp; ++i)
                    {
                        fen += temp + " ";
                    }
                    fen.pop_back(); // remove trailing space
                    board.setFen(fen);
                    manager = TimeManagement::TimeManager(~board.sideToMove());
                    // chess::Color is defined as an enum with WHITE = 0 and BLACK = 1,
                    // which is contradictory to how TimeManager is implemented, so we have to invert it using ~.
                    manager_exists = true;
                }

                std::string next;
                iss >> next;
                if (next == "moves")
                {
                    std::string move_str;
                    while (iss >> move_str)
                    {
                        chess::Move m = chess::uci::uciToMove(board, move_str);
                        board.makeMove(m);
                    }

                    if (manager_exists) { manager->white = ~board.sideToMove(); }
                }
            }
            else if (token == "go")
            {
                std::string bestmove;
                int wtime = 0, btime = 0, winc = 0, binc = 0, depth = 0, movetime = -1;

                std::string param;
                while (iss >> param)
                {
                    if (param == "depth")
                    {
                        iss >> depth;
                        break;
                    }

                    if (param == "movetime")
                    {
                        iss >> movetime;
                        break;
                    }
                    if (param == "wtime") iss >> wtime;
                    else if (param == "btime") iss >> btime;
                    else if (param == "winc") iss >> winc;
                    else if (param == "binc") iss >> binc;
                }
                if (manager_exists)
                {
                    manager->go(wtime, btime, winc, binc, movetime);
                }
                if (depth > 0)
                {
                    bestmove = search(board, std::nullopt, depth, out);
                }
                else
                {
                    bestmove = search(board, manager, -1, out);
                }
                out << "bestmove " << bestmove << "\n";
            }
            else if (token == "quit")
            {
                break;
            }
            else if (token == "setoption")
            {
                // good luck debugging suckers :)
            }
            else
            {
                out << "info string unknown command: " << line << "\n";
            }
        }
    }
}
