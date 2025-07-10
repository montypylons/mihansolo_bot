#include "chess.hpp"
#include <tuple>
#include <string>
#include <iostream>
#include "reader.hpp"
#include <optional>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <chrono>
#include <sstream>
#include "evaluation.hpp"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/logger.h"

using namespace chess;

auto logger2 = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");

Board board = Board();
Reader::Book book;
int intial_alpha = std::numeric_limits<int>::min();
int inital_beta = std::numeric_limits<int>::max();

Movelist get_legal_moves()

{
    Movelist moves;
    logger2->info("board: {}", board.getFen());
    movegen::legalmoves(moves, board);
    return moves;
}

bool game_over()
{
    Movelist moves = get_legal_moves();
    bool no_moves = moves.empty();
    if ((no_moves) || board.isHalfMoveDraw() || board.isInsufficientMaterial() || board.isRepetition())
    {
        logger2->info("Game over detected: no legal moves or draw conditions met.");
        return true;
    }
    else
    {
        logger2->info("game not over");
        return false;
    }
}

int move_ordering(std::string move_uci)

{
    Move move = uci::uciToMove(board, move_uci);
    if (board.isCapture(move) && (move.typeOf() != Move::CASTLING && Move::ENPASSANT))
    {
        if ((board.at(move.from()) == Piece::NONE) || (board.at(move.to()) == Piece::NONE))
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
    logger2->info("successfuly initiated book");
}

std::optional<std::string> book_move()
{
    Reader::BookMoves book_moves = book.GetBookMoves((uint64_t)board.zobrist());
    if (!(book_moves.empty()))
    {
        std::string found_move = Reader::ConvertBookMoveToUci(Reader::RandomBookMove(book_moves));
        logger2->info("book move {} found for position {}", found_move, board.getFen());
        return found_move;
    }
    logger2->info("no book move found for position {}", board.getFen());
    return std::nullopt;
}

std::tuple<int, Move> negamax(int alpha, int beta, Move last_move, int depth, int ply)
{
    if (depth == 0 || (game_over()))
    {
        logger2->info("found leaf node at depth {}, ply {}, board {} with last move {}", depth, ply, board.getFen(), uci::moveToUci(last_move));
        int leaf_eval = evaluation::main_eval(board, ply);
        logger2->info("leaf eval {} on position {}", leaf_eval, board.getFen());
        return std::make_tuple(leaf_eval, last_move);
    }
    Move best_move = Move::NO_MOVE;
    int best_eval = std::numeric_limits<int>::min();
    Movelist legal_moves = get_legal_moves();
    for (const auto &move : legal_moves)
    {
        board.makeMove(move);
        int score;
        Move dummy_move;
        std::tie(score, dummy_move) = negamax(-beta, -alpha, move, depth - 1, ply + 1);

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

std::string search(const std::string &fen)
{
    if (fen != "0")
    {
        board.setFen(fen);
    }
    auto bookmove = book_move();
    if (bookmove.has_value())
    {
        return bookmove.value();
    }

    Move returned_move;
    int eval;
    std::tie(eval, returned_move) = negamax(intial_alpha, inital_beta, Move::NO_MOVE, 4, 0);

    if (returned_move == Move::NO_MOVE)
    {
        return "0000";
    }

    std::string move_uci = uci::moveToUci(returned_move);
    logger2->info("negamax believes best move {} in position {}", move_uci, board.getFen());

    return move_uci;
}

void start_uci()
{
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
                    Move m = uci::uciToMove(board, move_str);
                    board.makeMove(m);
                }
            }
        }
        else if (token == "go")
        {
            std::string bestmove = search("0");
            std::cout << "bestmove " << bestmove << "\n";
        }
        else if (token == "quit")
        {
            break;
        }
        else if (token == "setoption")
        {
            // nothing except the DPRK missle program
        }
        else
        {
            std::cout << "info string unknown command: " << line << "\n";
        }
    }
}

void main()
{
    init_book();
    start_uci();
}
