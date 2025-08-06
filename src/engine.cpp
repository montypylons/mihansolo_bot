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

namespace engine // TODO: add iterative deepening tests
{
    constexpr int TIME_RAN_OUT_EVAL = -88888888;
    constexpr int NULL_MOVE_REDUCTION = 3;


    int history[2][64][64];
    int nodes = 0;


    bool abort_due_to_time = false;
    bool manager_exists = false;

    Reader::Book book;
    TranspositionTable table; // TODO: add tests fr this
    std::optional<TimeManagement::TimeManager> manager; // TODO: add tests fr this

    const int initial_alpha = std::numeric_limits<int>::min() + 1; // to avoid wraparound bugs
    const int initial_beta = std::numeric_limits<int>::max();

    // NOLINTBEGIN
    bool game_over(const chess::Board& board)
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

    int QuiescenceSearch(int alpha, int beta, chess::Board& board, int ply)
    {
        nodes++;
        if (manager.has_value() && !manager->time_remaining())
        {
            abort_due_to_time = true;
            return 0;
        }
        const int static_eval = evaluation::main_eval(board, ply);
        int best_value = static_eval;
        // UPDATE: using native capture move generator now
        chess::Movelist capture_moves;
        chess::movegen::legalmoves<chess::movegen::MoveGenType::CAPTURE>(capture_moves, board);


        if (best_value >= beta)
        {
            return best_value;
        }
        if (best_value > alpha)
        {
            alpha = best_value;
        }

        for (const auto& move : capture_moves)
        {
            board.makeMove(move);
            const int score = -QuiescenceSearch(-beta, -alpha, board, ply + 1);
            board.unmakeMove(move);

            if (score >= beta)
            {
                return score;
            }
            if (score > best_value)
            {
                best_value = score;
            }
            if (score > alpha)
            {
                alpha = score;
            }
        }
        return best_value;
    }


    void init_book()
    {
        book.Load("C:/Users/DELL/Documents/mihansolo_bot/gm2600.bin");
    }

    std::optional<std::string> book_move(const chess::Board& board)
    {
        if (const Reader::BookMoves book_moves = book.GetBookMoves(board.zobrist()); !book_moves.empty())
        {
            std::string found_move = Reader::ConvertBookMoveToUci(Reader::RandomBookMove(book_moves));
            return found_move;
        }
        return std::nullopt;
    }

    inline bool can_NMP(const chess::Board& board, const int depth)
    {
        // cannot null move prune when it is a zugzwang-ish position, side to move is in check, or the reduction factor (NULL_MOVE_REDUCTION)
        // would cause a depth < 1
        return depth > NULL_MOVE_REDUCTION && board.hasNonPawnMaterial(board.sideToMove()) && !board.inCheck();
    }


    std::tuple<int, chess::Move> negamax(const chess::Move& PV_Move, TranspositionTable& table1, chess::Board& board,
                                         int alpha,
                                         const int beta,
                                         const chess::Move& last_move,
                                         const int& depth, const int& ply)
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
            // int leaf_eval{evaluation::main_eval(board, ply)};
            return std::make_tuple(leaf_eval, last_move);
        }

        // NOLINTBEGIN (linter says this is unreachable for some reason)
        chess::Move best_move = chess::Move::NO_MOVE;
        int best_eval = std::numeric_limits<int>::min();
        chess::Movelist legal_moves;
        chess::movegen::legalmoves(legal_moves, board);
        legal_moves = utils::order_moves(history, PV_Move, legal_moves, board);

        for (const auto& move : legal_moves)
        {
            board.makeMove(move);

            int score;
            chess::Move dummy_move{};
            std::tie(score, dummy_move) = negamax(PV_Move, table1, board, -beta, -alpha, move, depth - 1, ply + 1);
            score = -score;

            board.unmakeMove(move);


            if (score > best_eval)
            {
                best_eval = int{score};
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


    std::string search(const std::optional<chess::Board>& fen, const std::optional<TimeManagement::TimeManager>& manager1)
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
            constexpr int default_depth = 5;
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
