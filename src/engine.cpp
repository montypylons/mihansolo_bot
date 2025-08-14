#include "chess.hpp"
#include "engine.hpp"
#include "evaluation.hpp"
#include "reader.hpp"
#include <filesystem>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include "utils.hpp"
#include "tt.hpp"
#include "timemanagement.hpp"
// TODO: SPRT this build against current production build.

namespace engine // TODO: add iterative deepening tests
{
    constexpr int MAX_EXTENSIONS = 0; // BUG: extensions cause node explosion
    constexpr int QUIESCENCE_DEPTH = 0;
    constexpr int DELTA = 200;

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
     * @return The score of the position after evaluating to a quiescent position (no captures).
     */
    int QuiescenceSearch(int alpha, const int beta, chess::Board& board, const int ply)
    {
        if (manager.has_value() && !manager->time_remaining())
        {
            abort_due_to_time = true;
            return 0;
        }
        nodes++;

        const uint64_t zobrist = board.zobrist();
        if (const auto ttEntry = table.find_usable_entry(alpha, beta, QUIESCENCE_DEPTH, zobrist); ttEntry.has_value())
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
            const int score = -QuiescenceSearch(-beta, -alpha, board, ply + 1);
            board.unmakeMove(move);


            if (score >= beta)
            {
                table.put(zobrist, chess::Move::NO_MOVE, QUIESCENCE_DEPTH, score, NodeType::LOWERBOUND);
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

        table.put(zobrist, chess::Move::NO_MOVE, QUIESCENCE_DEPTH, best_value, node_type);

        return best_value;
    }


    /**
     * @param book_path The path to load a Polyglot-format opening book from
     * Load the book (pretty obvious)
     */
    void init_book(const std::string& book_path)
    {
        book.Load(book_path.c_str());
    }

    /**
     *
     * @param board Board to find book move for
     * @return A random book move if multiple found, if only one found return that, if none found return std::nullopt
     */
    std::optional<std::string> book_move(const chess::Board& board)
    {
        if (const Reader::BookMoves book_moves = book.GetBookMoves(board.zobrist()); !book_moves.empty())
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
     * @return A tuple of the believed evaluation and best move in the position
     */
    std::tuple<int, chess::Move> negamax(const chess::Move& PV_Move, TranspositionTable& table1, chess::Board& board,
                                         int alpha,
                                         const int beta,
                                         const chess::Move& last_move,
                                         const int& depth, const int& ply, int numExtensions)
    {
        nodes++;
        // time management
        if (manager.has_value() && !manager->time_remaining())
        {
            abort_due_to_time = true;
            return std::make_tuple(0, chess::Move::NO_MOVE);
        }
        // transposition table stuff starts
        const int alpha_original = alpha;
        const auto zobrist_key = board.zobrist();

        if (auto TTResult = table1.find_usable_entry(alpha_original, beta, depth, zobrist_key); TTResult.has_value())
        {
            return TTResult.value();
        }
        // transposition stuff ends

        if (depth == 0 || game_over(board)) // NOLINT
        {
            int leaf_eval{QuiescenceSearch(alpha, beta, board, ply)};
            return std::make_tuple(leaf_eval, last_move);
        }

        // NOLINTBEGIN (linter says this is unreachable for some reason)
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

        for (const auto& move : legal_moves)
        {
            int score;
            chess::Move dummy_move{};

            board.makeMove(move);
            int passed_pawn_extension = (is_pawns_near_promotion(board) && numExtensions < MAX_EXTENSIONS) ? 1 : 0;

            std::tie(score, dummy_move) = negamax(PV_Move, table1, board, -beta, -alpha, move,
                                                  (depth + passed_pawn_extension) - 1, ply + 1,
                                                  numExtensions + passed_pawn_extension);
            score = -score;

            board.unmakeMove(move);

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
                table1.put(zobrist_key, best_move, depth, best_eval, NodeType::LOWERBOUND);
                return std::make_tuple(best_eval, best_move);
            }
        }
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
        table1.put(zobrist_key, best_move, depth, best_eval, node_type);
        // End transposition table stuff

        return std::make_tuple(best_eval, best_move);
        // NOLINTEND
    }


    /**
     *
     * @param fen Fen for testing, not required
     * @param manager1 The time manager, also not required
     * @param default_depth Depth to use if there is no time manager
     * @return The believed best move in the position as a UCI-formatted string
     */
    std::string search(const std::optional<chess::Board>& fen,
                       const std::optional<TimeManagement::TimeManager>& manager1, const int default_depth)
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
                auto result = negamax(PV_Move, table, board, initial_alpha, initial_beta,
                                      chess::Move::NO_MOVE, depth,
                                      0);

                returned_move = std::get<1>(result);
                eval = std::get<0>(result);


                if (!abort_due_to_time) // prevents using corrupted moves
                {
                    PV_Move = returned_move;
                    previous_eval = eval;
                }

                depth++;
            }
        }
        else // in testing time management is often not tested
        // TODO: add UCI E2E tests as part of CTest suite, since there are none currently
        {
            for (int _i = 1; _i < default_depth; _i++)
            {
                auto result = negamax(PV_Move, table, board, initial_alpha, initial_beta,
                                      chess::Move::NO_MOVE, _i,
                                      0);
                returned_move = std::get<1>(result);

                PV_Move = returned_move; // no time management logic here
            }
        }

        if (returned_move == chess::Move::NO_MOVE)
        {
            return "0000";
        }

        std::string move_uci = chess::uci::moveToUci(PV_Move);
        std::cout << "info depth " << depth << " nodes " << nodes << " score cp " << previous_eval << "\n";

        return move_uci;
    }

    /**
     * Start the UCI input/output loop, doesn't have all the options yet but working on it :D
     */
    void start_uci()
    {
        chess::Board board;
        std::string line;

        while (std::getline(std::cin, line))
        {
            std::istringstream iss(line);
            std::string token;
            iss >> token;

            if (token == "uci")
            {
                std::cout << "id name MihanSolo\n";
                std::cout << "id author Mihin Benaragama\n";
                std::cout << "option name Hash type spin default 16 min 1 max 1024\n";
                std::cout << "option name Threads type spin default 1 min 1 max 16\n";
                std::cout << "option name Move Overhead type spin default 30 min 0 max 5000\n";
                std::cout << "option name UCI_ShowWDL type check default false\n";
                std::cout << "option name Ponder type check default false\n";
                std::cout << "option name UCI_AnalyseMode type check default false\n";
                std::cout << "option name UCI_LimitStrength type check default false\n";
                std::cout << "option name UCI_Elo type spin default 1350 min 1350 max 2850\n";
                std::cout << "uciok\n";
            }
            else if (token == "isready")
            {
                std::cout << "readyok\n";
            }
            else if (token == "position")
            {
                std::string pos_type;
                iss >> pos_type;


                if (pos_type == "startpos")
                {
                    board.setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
                    manager = TimeManagement::TimeManager(board.sideToMove());
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
                    manager = TimeManagement::TimeManager(board.sideToMove());
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
                }
            }
            else if (token == "go")
            {
                int wtime = 0, btime = 0, winc = 0, binc = 0;

                std::string param;
                while (iss >> param)
                {
                    if (param == "wtime") iss >> wtime;
                    else if (param == "btime") iss >> btime;
                    else if (param == "winc") iss >> winc;
                    else if (param == "binc") iss >> binc;
                }

                if (manager.has_value())
                {
                    manager->go(wtime, btime, winc, binc);
                }

                std::string bestmove = search(board, manager);
                std::cout << "bestmove " << bestmove << "\n";
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
                std::cout << "info string unknown command: " << line << "\n";
            }
        }
    }
}
