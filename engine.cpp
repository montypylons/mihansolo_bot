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

using namespace chess;

Board board = Board();
Reader::Book book;
int intial_alpha = std::numeric_limits<int>::min();
int inital_beta = std::numeric_limits<int>::max();

Movelist get_legal_moves()

{
    Movelist moves;
    movegen::legalmoves(moves, board);
    return moves;
}

bool game_over()
{
    Movelist moves = get_legal_moves();
    bool no_moves = moves.empty();
    if ((no_moves) | board.isHalfMoveDraw() | board.isInsufficientMaterial() | board.isRepetition())
    {
        return true;
    }
    else
    {
        return false;
    }
}
// tables are from Tomasz Michniewski's Simplified Evaluation Function
int piece_square[7][64] = {
    {
        0, 0, 0, 0, 0, 0, 0, 0,         // rank 1 (a1-h1)
        5, 10, 10, -20, -20, 10, 10, 5, // rank 2 (a2-h2) - the -20 row
        5, -5, -10, 0, 0, -10, -5, 5,   // rank 3 (a3-h3)
        0, 0, 0, 20, 20, 0, 0, 0,       // rank 4 (a4-h4)
        5, 5, 10, 25, 25, 10, 5, 5,     // rank 5 (a5-h5)
        10, 10, 20, 30, 30, 20, 10, 10, // rank 6 (a6-h6)
        50, 50, 50, 50, 50, 50, 50, 50, // rank 7 (a7-h7)
        0, 0, 0, 0, 0, 0, 0, 0          // rank 8 (a8-h8)
    },

    {-50, -40, -30, -30, -30, -30, -40, -50, // knight
     -40, -20, 0, 0, 0, 0, -20, -40,
     -30, 0, 10, 15, 15, 10, 0, -30,
     -30, 5, 15, 20, 20, 15, 5, -30,
     -30, 0, 15, 20, 20, 15, 0, -30,
     -30, 5, 10, 15, 15, 10, 5, -30,
     -40, -20, 0, 5, 5, 0, -20, -40,
     -50, -40, -30, -30, -30, -30, -40, -50},

    {
        -20, -10, -10, -10, -10, -10, -10, -20, // bishop rank 1 (a1-h1)
        -10, 5, 0, 0, 0, 0, 5, -10,             // bishop rank 2 (a2-h2)
        -10, 10, 10, 10, 10, 10, 10, -10,       // bishop rank 3 (a3-h3)
        -10, 0, 10, 10, 10, 10, 0, -10,         // bishop rank 4 (a4-h4)
        -10, 5, 5, 10, 10, 5, 5, -10,           // bishop rank 5 (a5-h5)
        -10, 0, 5, 10, 10, 5, 0, -10,           // bishop rank 6 (a6-h6)
        -10, 0, 0, 0, 0, 0, 0, -10,             // bishop rank 7 (a7-h7)
        -20, -10, -10, -10, -10, -10, -10, -20  // bishop rank 8 (a8-h8)
    },
    {
        0, 0, 0, 5, 5, 0, 0, 0,       // rook rank 1 (a1-h1)
        -5, 0, 0, 0, 0, 0, 0, -5,     // rook rank 2 (a2-h2)
        -5, 0, 0, 0, 0, 0, 0, -5,     // rook rank 3 (a3-h3)
        -5, 0, 0, 0, 0, 0, 0, -5,     // rook rank 4 (a4-h4)
        -5, 0, 0, 0, 0, 0, 0, -5,     // rook rank 5 (a5-h5)
        -5, 0, 0, 0, 0, 0, 0, -5,     // rook rank 6 (a6-h6)
        5, 10, 10, 10, 10, 10, 10, 5, // rook rank 7 (a7-h7)
        0, 0, 0, 0, 0, 0, 0, 0        // rook rank 8 (a8-h8)
    },

    {
        -20, -10, -10, -5, -5, -10, -10, -20, // queen rank 1 (a1-h1)
        -10, 0, 5, 0, 0, 0, 0, -10,           // queen rank 2 (a2-h2)
        -10, 5, 5, 5, 5, 5, 0, -10,           // queen rank 3 (a3-h3)
        0, 0, 5, 5, 5, 5, 0, -5,              // queen rank 4 (a4-h4)
        -5, 0, 5, 5, 5, 5, 0, -5,             // queen rank 5 (a5-h5)
        -10, 0, 5, 5, 5, 5, 0, -10,           // queen rank 6 (a6-h6)
        -10, 0, 0, 0, 0, 0, 0, -10,           // queen rank 7 (a7-h7)
        -20, -10, -10, -5, -5, -10, -10, -20  // queen rank 8 (a8-h8)
    },
    {
        20, 30, 10, 0, 0, 10, 30, 20,           // king middle game rank 1 (a1-h1)
        20, 20, 0, 0, 0, 0, 20, 20,             // king middle game rank 2 (a2-h2)
        -10, -20, -20, -20, -20, -20, -20, -10, // king middle game rank 3 (a3-h3)
        -20, -30, -30, -40, -40, -30, -30, -20, // king middle game rank 4 (a4-h4)
        -30, -40, -40, -50, -50, -40, -40, -30, // king middle game rank 5 (a5-h5)
        -30, -40, -40, -50, -50, -40, -40, -30, // king middle game rank 6 (a6-h6)
        -30, -40, -40, -50, -50, -40, -40, -30, // king middle game rank 7 (a7-h7)
        -30, -40, -40, -50, -50, -40, -40, -30  // king middle game rank 8 (a8-h8)
    },
    {
        -50, -30, -30, -30, -30, -30, -30, -50, // king end game rank 1 (a1-h1)
        -30, -30, 0, 0, 0, 0, -30, -30,         // king end game rank 2 (a2-h2)
        -30, -10, 20, 30, 30, 20, -10, -30,     // king end game rank 3 (a3-h3)
        -30, -10, 30, 40, 40, 30, -10, -30,     // king end game rank 4 (a4-h4)
        -30, -10, 30, 40, 40, 30, -10, -30,     // king end game rank 5 (a5-h5)
        -30, -10, 20, 30, 30, 20, -10, -30,     // king end game rank 6 (a6-h6)
        -30, -20, -10, 0, 0, -10, -20, -30,     // king end game rank 7 (a7-h7)
        -50, -40, -30, -20, -20, -30, -40, -50  // king end game rank 8 (a8-h8)
    },
};

int move_ordering(std::string move_uci)

{
    Move move = uci::uciToMove(board, move_uci);
    if (board.isCapture(move) && (move.typeOf() != Move::CASTLING && Move::ENPASSANT))
    {
        if ((board.at(move.from()) == Piece::NONE) | (board.at(move.to()) == Piece::NONE))
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

    book.Load("gm2600.bin");
}

std::optional<std::string> book_move()
{
    Reader::BookMoves book_moves = book.GetBookMoves((uint64_t)board.zobrist());
    if (!(book_moves.empty()))
    {
        return Reader::ConvertBookMoveToUci(Reader::RandomBookMove(book_moves));
    }
    return std::nullopt;
}

int evaluate(int ply = 0)
{
    int score = 0;
    bool is_endgame;
    bool check = board.inCheck();
    Movelist moves;
    chess::Color side_to_move = board.sideToMove();
    int turn = board.sideToMove() == chess::Color::WHITE ? 1 : -1;

    movegen::legalmoves(moves, board);
    bool no_moves = moves.empty();

    if (check && no_moves)
    {
        return -10000 + ply;
    }
    if (board.isInsufficientMaterial() || board.isRepetition() || (!check && no_moves))
    {
        return 0;
    }

    // TODO: MAKE THIS RETURN FROM THE SIDE TO MOVE'S PERSPECTIVE
    Bitboard pawns = board.pieces(PieceType::PAWN, side_to_move);
    Bitboard knights = board.pieces(PieceType::KNIGHT, side_to_move);
    Bitboard bishops = board.pieces(PieceType::BISHOP, side_to_move);
    Bitboard rooks = board.pieces(PieceType::ROOK, side_to_move);
    Bitboard queens = board.pieces(PieceType::QUEEN, side_to_move);

    Bitboard black_pawns = board.pieces(PieceType::PAWN, !side_to_move);
    Bitboard black_knights = board.pieces(PieceType::KNIGHT, !side_to_move);
    Bitboard black_bishops = board.pieces(PieceType::BISHOP, !side_to_move);
    Bitboard black_rooks = board.pieces(PieceType::ROOK, !side_to_move);
    Bitboard black_queens = board.pieces(PieceType::QUEEN, !side_to_move);

    int p_count = pawns.count();
    int n_count = knights.count();
    int b_count = bishops.count();
    int r_count = rooks.count();
    int q_count = queens.count();

    int p_count_black = black_pawns.count();
    int n_count_black = black_knights.count();
    int b_count_black = black_bishops.count();
    int r_count_black = black_rooks.count();
    int q_count_black = black_queens.count();

    int positional_score = 0;

    while (pawns)
    {
        int square = pawns.pop();
        int p_score = piece_square[0][square] * turn;
        positional_score += p_score;
    }
    while (knights)
    {
        int square = knights.pop();
        int n_score = piece_square[1][square] * turn;
        positional_score += n_score;
    }
    while (bishops)
    {
        int square = bishops.pop();
        int b_score = piece_square[2][square] * turn;
        positional_score += b_score;
    }
    while (rooks)
    {
        int square = rooks.pop();
        int r_score = piece_square[3][square] * turn;
        positional_score += r_score;
    }
    while (queens)
    {
        int square = queens.pop();
        int q_score = piece_square[4][square] * turn;
        positional_score += q_score;
    }

    // black pieces
    while (black_pawns)
    {
        int square = black_pawns.pop();
        int flipped_square = square ^ 56;
        int p_score = piece_square[0][flipped_square] * -turn;
        positional_score += p_score;
    }
    while (black_knights)
    {
        int square = black_knights.pop();
        int flipped_square = square ^ 56;
        int n_score = piece_square[1][flipped_square] * -turn;
        positional_score += n_score;
    }
    while (black_bishops)
    {
        int square = black_bishops.pop();
        int flipped_square = square ^ 56;
        int b_score = piece_square[2][flipped_square] * -turn;
        positional_score += b_score;
    }
    while (black_rooks)
    {
        int square = black_rooks.pop();
        int flipped_square = square ^ 56;
        int r_score = piece_square[3][flipped_square] * -turn;
        positional_score += r_score;
    }
    while (black_queens)
    {
        int square = black_queens.pop();
        int flipped_square = square ^ 56;
        int q_score = piece_square[4][flipped_square] * -turn;
        positional_score += q_score;
    }

    score += positional_score;

    int material_score = 0;

    // material eval - using standard piece values (pawn=1, knight/bishop=3, rook=5, queen=9)
    material_score += p_count * 100 * turn; // pawn = 100 centipawns
    material_score += n_count * 300 * turn; // knight = 300 centipawns
    material_score += b_count * 300 * turn; // bishop = 300 centipawns
    material_score += r_count * 500 * turn; // rook = 500 centipawns
    material_score += q_count * 900 * turn; // queen = 900 centipawns

    material_score += p_count_black * 100 * -turn;
    material_score += n_count_black * 300 * -turn;
    material_score += b_count_black * 300 * -turn;
    material_score += r_count_black * 500 * -turn;
    material_score += q_count_black * 900 * -turn;

    score += material_score;

    return score;
}

std::tuple<int, Move> negamax(int alpha, int beta, Move last_move, int depth, int ply)
{
    if (depth == 0 | (game_over()))
    {
        return std::make_tuple(evaluate(ply), last_move);
    }
    Move best_move = Move::NO_MOVE;
    int best_eval = std::numeric_limits<int>::min();
    Movelist legal_moves = get_legal_moves();
    for (const auto &move : legal_moves)
    {
        // std::cout << "[DEBUG]: cpp: depth = " << depth << ", move = " << uci::moveToUci(move) << std::endl;
        // added for debugging
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

void search(std::string fen)
{
    int eval;
    Move returned_move;
    if (!(fen == "0"))
    {
        board.setFen(fen);
        std::tie(eval, returned_move) = negamax(intial_alpha, inital_beta, Move::NO_MOVE, 5, 0);
    }
    std::cout << "Move: " << uci::moveToUci(returned_move) << std::endl;
}

void main()
{
    auto start = std::chrono::high_resolution_clock::now();
    search("8/8/8/8/8/1k1r4/8/1K6 b - - 0 1");
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double seconds = static_cast<double>(duration) / 1000000000.0;
    std::cout << std::to_string(seconds) << " seconds" << std::endl;
}
