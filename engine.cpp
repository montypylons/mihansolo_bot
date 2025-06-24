#include "chess.hpp"
#include <tuple>
#include <string>
#include <iostream>
#include <pybind11/pybind11.h>
#include <Windows.h>


std::tuple<int, Move> negamax(int alpha, int beta, Move last_move, int depth, std::string fen, Board board, int ply=0){
    
}


namespace py = pybind11;
using namespace chess;

int evaluate(std::string fen, int ply=0) {
    Board board = Board(fen); 
    bool check = board.inCheck();
    Movelist moves;
    bool no_moves = moves.empty();
    chess::Color side_to_move = board.sideToMove();
    
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

    int score = 0;
    
    // material eval
    score += pawns.count();
    score += knights.count()*3;
    score += bishops.count()*3;
    score += rooks.count()*5;
    score += queens.count()*9;

    score -= black_pawns.count();
    score -= black_knights.count()*3;
    score -= black_bishops.count()*3;
    score -= black_rooks.count()*5;
    score -= black_queens.count()*9;
        

    return score;
}

PYBIND11_MODULE(engine, m) {
    m.doc() = "engine cpp"; // optional module docstring

    m.def("evaluate", &evaluate, "evaluate the position");
}
