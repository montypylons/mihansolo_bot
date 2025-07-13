#include "chess.hpp"
#include "engine.hpp"
#include "evaluation.hpp"
#include "reader.hpp"
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace engine
{


    Reader::Book book;
    int intial_alpha = std::numeric_limits<int>::min();
    int inital_beta = std::numeric_limits<int>::max();

    chess::Movelist get_legal_moves(const chess::Board& board)

    {
        chess::Movelist moves;
        chess::movegen::legalmoves(moves, board);
        return moves;
    }

    bool game_over(const chess::Board& board)
    {
        chess::Movelist moves = get_legal_moves(board);
        bool no_moves = moves.empty();
        if ((no_moves) || board.isHalfMoveDraw() || board.isInsufficientMaterial() || board.isRepetition())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int move_ordering(const chess::Board& board, const std::string& move_uci)

    {
        chess::Move move = chess::uci::uciToMove(board, move_uci);
        if (board.isCapture(move) && (move.typeOf() != chess::Move::CASTLING && chess::Move::ENPASSANT))
        {
            if ((board.at(move.from()) == chess::Piece::NONE) || (board.at(move.to()) == chess::Piece::NONE))
            {
                std::cerr << "[Warning] Tried to evaluate a capture move with no target piece (bad move?): " << move_uci << "\n";
                return -100;
            }

            int from_value = 3; // piece_values[static_cast<int>(board.at(move.from()))];
            int to_value = 3;   // piece_values[static_cast<int>(board.at(move.to()))];
            return to_value - from_value;
        }
        return -100;
    }

    void init_book()
    {
        book.Load("C:/Users/DELL/Documents/mihansolo_bot/gm2600.bin");
    }

    std::optional<std::string> book_move(const chess::Board& board)
    {
        Reader::BookMoves book_moves = book.GetBookMoves((uint64_t)board.zobrist());
        if (!(book_moves.empty()))
        {
            std::string found_move = Reader::ConvertBookMoveToUci(Reader::RandomBookMove(book_moves));
            return found_move;
        }
        return std::nullopt;
    }

    std::tuple<int, chess::Move> negamax(chess::Board& board, int alpha, int beta, const chess::Move& last_move, int depth, int ply)
    {
        if (depth == 0 || (game_over(board)))
        {
            int leaf_eval = evaluation::main_eval(board, ply);
            return std::make_tuple(leaf_eval, last_move);
        }
        chess::Move best_move = chess::Move::NO_MOVE;
        int best_eval = std::numeric_limits<int>::min();
        chess::Movelist legal_moves = get_legal_moves(board);
        for (const auto &move : legal_moves)
        {
            board.makeMove(move);
            int score;
            chess::Move dummy_move;
            std::tie(score, dummy_move) = negamax(board, -beta, -alpha, move, depth - 1, ply + 1);

            score = -score;
            board.unmakeMove(move);
            if (score > best_eval)
            {
                best_eval = score;
                best_move = move;
            }
            alpha = std::max(alpha, score);
            if (beta <= alpha)
            {
                break;
            }
        }
        return std::make_tuple(best_eval, best_move);
    }

    std::string search(std::optional<chess::Board> fen)
    {
        chess::Board board;

        if (fen.has_value())
        {
            board = fen.value();
        }
        auto bookmove = book_move(board);
        if (bookmove.has_value())
        {
            return bookmove.value();
        }

        chess::Move returned_move;
        int eval;
        std::tie(eval, returned_move) = negamax(board, intial_alpha, inital_beta, chess::Move::NO_MOVE, 5, 0);

        if (returned_move == chess::Move::NO_MOVE)
        {
            return "0000";
        }

        std::string move_uci = chess::uci::moveToUci(returned_move);

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
                std::string bestmove = search(board);
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
