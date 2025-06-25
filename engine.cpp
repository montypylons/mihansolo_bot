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
 0,  0,  0,  0,  0,  0,  0,  0, // rank 1 (a1-h1)
 5, 10, 10,-20,-20, 10, 10,  5, // rank 2 (a2-h2) - the -20 row
 5, -5,-10,  0,  0,-10, -5,  5, // rank 3 (a3-h3)
 0,  0,  0, 20, 20,  0,  0,  0, // rank 4 (a4-h4)
 5,  5, 10, 25, 25, 10,  5,  5, // rank 5 (a5-h5)
10, 10, 20, 30, 30, 20, 10, 10, // rank 6 (a6-h6)
50, 50, 50, 50, 50, 50, 50, 50, // rank 7 (a7-h7)
 0,  0,  0,  0,  0,  0,  0,  0  // rank 8 (a8-h8)
},

{-50,-40,-30,-30,-30,-30,-40,-50, // knight
-40,-20,  0,  0,  0,  0,-20,-40,
-30,  0, 10, 15, 15, 10,  0,-30,
-30,  5, 15, 20, 20, 15,  5,-30,
-30,  0, 15, 20, 20, 15,  0,-30,
-30,  5, 10, 15, 15, 10,  5,-30,
-40,-20,  0,  5,  5,  0,-20,-40,
-50,-40,-30,-30,-30,-30,-40,-50},

{-20,-10,-10,-10,-10,-10,-10,-20, // bishop rank 1 (a1-h1)
-10,  5,  0,  0,  0,  0,  5,-10, // bishop rank 2 (a2-h2)
-10, 10, 10, 10, 10, 10, 10,-10, // bishop rank 3 (a3-h3)
-10,  0, 10, 10, 10, 10,  0,-10, // bishop rank 4 (a4-h4)
-10,  5,  5, 10, 10,  5,  5,-10, // bishop rank 5 (a5-h5)
-10,  0,  5, 10, 10,  5,  0,-10, // bishop rank 6 (a6-h6)
-10,  0,  0,  0,  0,  0,  0,-10, // bishop rank 7 (a7-h7)
-20,-10,-10,-10,-10,-10,-10,-20  // bishop rank 8 (a8-h8)
},
{ 0,  0,  0,  5,  5,  0,  0,  0, // rook rank 1 (a1-h1)
 -5,  0,  0,  0,  0,  0,  0, -5, // rook rank 2 (a2-h2)
 -5,  0,  0,  0,  0,  0,  0, -5, // rook rank 3 (a3-h3)
 -5,  0,  0,  0,  0,  0,  0, -5, // rook rank 4 (a4-h4)
 -5,  0,  0,  0,  0,  0,  0, -5, // rook rank 5 (a5-h5)
 -5,  0,  0,  0,  0,  0,  0, -5, // rook rank 6 (a6-h6)
  5, 10, 10, 10, 10, 10, 10,  5, // rook rank 7 (a7-h7)
  0,  0,  0,  0,  0,  0,  0,  0  // rook rank 8 (a8-h8)
},

{-20,-10,-10, -5, -5,-10,-10,-20, // queen rank 1 (a1-h1)
 -10,  0,  5,  0,  0,  0,  0,-10, // queen rank 2 (a2-h2)
 -10,  5,  5,  5,  5,  5,  0,-10, // queen rank 3 (a3-h3)
  0,  0,  5,  5,  5,  5,  0, -5, // queen rank 4 (a4-h4)
 -5,  0,  5,  5,  5,  5,  0, -5, // queen rank 5 (a5-h5)
 -10,  0,  5,  5,  5,  5,  0,-10, // queen rank 6 (a6-h6)
 -10,  0,  0,  0,  0,  0,  0,-10, // queen rank 7 (a7-h7)
 -20,-10,-10, -5, -5,-10,-10,-20  // queen rank 8 (a8-h8)
},
{20, 30, 10,  0,  0, 10, 30, 20, // king middle game rank 1 (a1-h1)
 20, 20,  0,  0,  0,  0, 20, 20, // king middle game rank 2 (a2-h2)
-10,-20,-20,-20,-20,-20,-20,-10, // king middle game rank 3 (a3-h3)
-20,-30,-30,-40,-40,-30,-30,-20, // king middle game rank 4 (a4-h4)
-30,-40,-40,-50,-50,-40,-40,-30, // king middle game rank 5 (a5-h5)
-30,-40,-40,-50,-50,-40,-40,-30, // king middle game rank 6 (a6-h6)
-30,-40,-40,-50,-50,-40,-40,-30, // king middle game rank 7 (a7-h7)
-30,-40,-40,-50,-50,-40,-40,-30  // king middle game rank 8 (a8-h8)
},
{-50,-30,-30,-30,-30,-30,-30,-50, // king end game rank 1 (a1-h1)
-30,-30,  0,  0,  0,  0,-30,-30, // king end game rank 2 (a2-h2)
-30,-10, 20, 30, 30, 20,-10,-30, // king end game rank 3 (a3-h3)
-30,-10, 30, 40, 40, 30,-10,-30, // king end game rank 4 (a4-h4)
-30,-10, 30, 40, 40, 30,-10,-30, // king end game rank 5 (a5-h5)
-30,-10, 20, 30, 30, 20,-10,-30, // king end game rank 6 (a6-h6)
-30,-20,-10,  0,  0,-10,-20,-30, // king end game rank 7 (a7-h7)
-50,-40,-30,-20,-20,-30,-40,-50  // king end game rank 8 (a8-h8)
},
};



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
    
    chess::Color side_to_move = board.sideToMove();
    int turn = board.sideToMove() == chess::Color::WHITE ? 1 : -1;

    
    movegen::legalmoves(moves, board);
    bool no_moves = moves.empty();

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

    int positional_score = 0;
    
    while (pawns) {
        int square = pawns.pop();
        int p_score = piece_square[0][square] * turn;
        positional_score += p_score;
    }
    while (knights) {
        int square = knights.pop();
        int n_score = piece_square[1][square] * turn;
        positional_score += n_score;
    }
    while (bishops) {
        int square = bishops.pop();
        int b_score = piece_square[2][square] * turn;
        positional_score += b_score;
    }
    while (rooks) {
        int square = rooks.pop();
        int r_score = piece_square[3][square] * turn;
        positional_score += r_score;
    }
    while (queens) {
        int square = queens.pop();
        int q_score = piece_square[4][square] * turn;
        positional_score += q_score;
    }
    
// black pieces
    while (black_pawns) {
        int square = black_pawns.pop();
        int flipped_square = square ^ 56;
        int p_score = piece_square[0][flipped_square] * -turn;
        positional_score += p_score;
    }
    while (black_knights) {
        int square = black_knights.pop();
        int flipped_square = square ^ 56;
        int n_score = piece_square[1][flipped_square] * -turn;
        positional_score += n_score;
    }
    while (black_bishops) {
        int square = black_bishops.pop();
        int flipped_square = square ^ 56;
        int b_score = piece_square[2][flipped_square] * -turn;
        positional_score += b_score;
    }
    while (black_rooks) {
        int square = black_rooks.pop();
        int flipped_square = square ^ 56;
        int r_score = piece_square[3][flipped_square] * -turn;
        positional_score += r_score;
    }
    while (black_queens) {
        int square = black_queens.pop();
        int flipped_square = square ^ 56;
        int q_score = piece_square[4][flipped_square] * -turn;
        positional_score += q_score;
    }

    score += positional_score;

    int material_score = 0;
    
    // material eval - using standard piece values (pawn=1, knight/bishop=3, rook=5, queen=9)
    material_score += p_count * 100 * turn;  // pawn = 100 centipawns
    material_score += n_count * 300 * turn;  // knight = 300 centipawns
    material_score += b_count * 300 * turn;  // bishop = 300 centipawns
    material_score += r_count * 500 * turn;  // rook = 500 centipawns
    material_score += q_count * 900 * turn;  // queen = 900 centipawns

    material_score += p_count_black * 100 * -turn;
    material_score += n_count_black * 300 * -turn;
    material_score += b_count_black * 300 * -turn;
    material_score += r_count_black * 500 * -turn;
    material_score += q_count_black * 900 * -turn;
    
    score += material_score;
        
    return score;
}

PYBIND11_MODULE(engine, m) {
    m.doc() = "engine cpp"; // optional module docstring

    m.def("evaluate", &evaluate, "evaluate the position");
}
