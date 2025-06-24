#include "chess.hpp"
#include <tuple>
#include <string>
#include <iostream>
#include <pybind11/pybind11.h>
#include <Windows.h>


// std::tuple<int, Move> negamax(int alpha, int beta, Move last_move, int depth, std::string fen, Board board, int ply=0){

// }
// tables are from Tomasz Michniewski's Simplified Evaluation Function
int piece_square[7][64] = {
{
 0,  0,  0,  0,  0,  0,  0,  0, // pawn
 50, 50, 50, 50, 50, 50, 50, 50,
 10, 10, 20, 30, 30, 20, 10, 10,
 5,  5, 10, 25, 25, 10,  5,  5,
 0,  0,  0, 20, 20,  0,  0,  0,
 5, -5,-10,  0,  0,-10, -5,  5,
 5, 10, 10,-20,-20, 10, 10,  5,
 0,  0,  0,  0,  0,  0,  0,  0
},

{-50,-40,-30,-30,-30,-30,-40,-50, // knight
-40,-20,  0,  0,  0,  0,-20,-40,
-30,  0, 10, 15, 15, 10,  0,-30,
-30,  5, 15, 20, 20, 15,  5,-30,
-30,  0, 15, 20, 20, 15,  0,-30,
-30,  5, 10, 15, 15, 10,  5,-30,
-40,-20,  0,  5,  5,  0,-20,-40,
-50,-40,-30,-30,-30,-30,-40,-50},

{-20,-10,-10,-10,-10,-10,-10,-20, // bishop
-10,  0,  0,  0,  0,  0,  0,-10,
-10,  0,  5, 10, 10,  5,  0,-10,
-10,  5,  5, 10, 10,  5,  5,-10,
-10,  0, 10, 10, 10, 10,  0,-10,
-10, 10, 10, 10, 10, 10, 10,-10,
-10,  5,  0,  0,  0,  0,  5,-10,
-20,-10,-10,-10,-10,-10,-10,-20
},
{ 0,  0,  0,  0,  0,  0,  0,  0, // rook
  5, 10, 10, 10, 10, 10, 10,  5,
 -5,  0,  0,  0,  0,  0,  0, -5,
 -5,  0,  0,  0,  0,  0,  0, -5,
 -5,  0,  0,  0,  0,  0,  0, -5,
 -5,  0,  0,  0,  0,  0,  0, -5,
 -5,  0,  0,  0,  0,  0,  0, -5,
  0,  0,  0,  5,  5,  0,  0,  0
},

{-20,-10,-10, -5, -5,-10,-10,-20, // queen
 -10,  0,  0,  0,  0,  0,  0,-10, 
 -10,  0,  5,  5,  5,  5,  0,-10,
 -5,  0,  5,  5,  5,  5,  0, -5,
  0,  0,  5,  5,  5,  5,  0, -5,
 -10,  5,  5,  5,  5,  5,  0,-10,
 -10,  0,  5,  0,  0,  0,  0,-10,
 -20,-10,-10, -5, -5,-10,-10,-20
},
{-30,-40,-40,-50,-50,-40,-40,-30, // king middle game
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-20,-30,-30,-40,-40,-30,-30,-20,
-10,-20,-20,-20,-20,-20,-20,-10,
 20, 20,  0,  0,  0,  0, 20, 20,
 20, 30, 10,  0,  0, 10, 30, 20
},
{-30,-40,-40,-50,-50,-40,-40,-30, // king end game
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-30,-40,-40,-50,-50,-40,-40,-30,
-20,-30,-30,-40,-40,-30,-30,-20,
-10,-20,-20,-20,-20,-20,-20,-10,
 20, 20,  0,  0,  0,  0, 20, 20,
 20, 30, 10,  0,  0, 10, 30, 20
}};



namespace py = pybind11;
using namespace chess;


uint64_t flipVertical(uint64_t x) {
    return _byteswap_uint64(x);
}

int evaluate(std::string fen, int ply=0) {
    int score = 0;
    bool is_endgame;
    Board board = Board(fen); 
    bool check = board.inCheck();
    Movelist moves;
    bool no_moves = moves.empty();
    chess::Color side_to_move = board.sideToMove();
    int turn = board.sideToMove() == chess::Color::WHITE ? 1 : -1;

    
    movegen::legalmoves(moves, board);

    if (check && no_moves) {
        return -10000 + ply;
    }
    if (board.isInsufficientMaterial() || board.isRepetition() || (!check && no_moves)){
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

    while (p_count > 0) {
        int p_score = piece_square[0][pawns.pop()] * turn;
        score += p_score;
    }
    while (n_count > 0) {
        int n_score = piece_square[1][knights.pop()] * turn;
        score += n_score;
    }
    while (b_count > 0) {
        int b_score = piece_square[2][bishops.pop()] * turn;
        score += b_score;
    }
    while (r_count > 0) {
        int r_score = piece_square[3][rooks.pop()] * turn;
        score += r_score;
    }
    while (q_count > 0) {
        int q_score = piece_square[4][queens.pop()] * turn;
        score += q_score;
    }
// black pieces
    while (p_count_black > 0) {
        int p_score = piece_square[0][black_pawns.pop() ^ 56] * -turn;
        score += p_score;
    }
    while (n_count_black > 0) {
        int n_score = piece_square[1][black_knights.pop() ^ 56] * -turn;
        score += n_score;
    }
    while (b_count_black > 0) {
        int b_score = piece_square[2][black_bishops.pop() ^ 56] * -turn;
        score += b_score;
    }
    while (r_count_black > 0) {
        int r_score = piece_square[3][black_rooks.pop() ^ 56] * -turn;
        score += r_score;
    }
    while (q_count_black > 0) {
        int q_score = piece_square[4][black_queens.pop() ^ 56] * -turn;
        score += q_score;
    }


    

    
    
    // material eval
    score += p_count * turn;
    score += n_count * 3 * turn;
    score += b_count * 3 * turn;
    score += r_count * 5 * turn;
    score += q_count * 9 * turn;

    score += p_count_black * -turn;
    score += n_count_black * 3 * -turn;
    score += b_count_black * 3 * -turn;
    score += r_count_black * 5 * -turn;
    score += q_count_black * 9 * -turn;
        

    return score;
}

PYBIND11_MODULE(engine, m) {
    m.doc() = "engine cpp"; // optional module docstring

    m.def("evaluate", &evaluate, "evaluate the position");
}
