#include "chess.hpp"
#include <tuple>
#include <string>
#include <iostream>
#include <pybind11/pybind11.h>
#include <Windows.h>

namespace py = pybind11;
using namespace chess;

int evaluate(std::string fen, int ply=0) {
    Board board = Board(fen); // from white's POV

    // std::cout << "FEN: " << fen << std::endl;
    // std::cout << "Side to move: " << (board.sideToMove()) << std::endl;
    
    // Check for checkmate: in check and no legal moves
    bool check = board.inCheck();
    Movelist moves;
    movegen::legalmoves(moves, board);
    bool no_moves = moves.empty();
    
    // std::cout << "Is check: " << (check ? "YES" : "NO") << std::endl;
    // std::cout << "No legal moves: " << (no_moves ? "YES" : "NO") << std::endl;
    
    // Check for checkmate first - this should override all other evaluation
    if (check && no_moves) {
        // std::cout << "Checkmate detected! Returning -10000 + " << ply << " = " << (-10000 + ply) << std::endl;
        // In negamax, always return -10000 + ply when the side to move is checkmated
        return -10000 + ply;
    }
    
    Bitboard pawns = board.pieces(PieceType::PAWN, Color::WHITE);
    Bitboard knights = board.pieces(PieceType::KNIGHT, Color::WHITE);
    Bitboard bishops = board.pieces(PieceType::BISHOP, Color::WHITE);
    Bitboard rooks = board.pieces(PieceType::ROOK, Color::WHITE);
    Bitboard queens = board.pieces(PieceType::QUEEN, Color::WHITE);
    // black piece bitboards
    Bitboard black_pawns = board.pieces(PieceType::PAWN, Color::BLACK);
    Bitboard black_knights = board.pieces(PieceType::KNIGHT, Color::BLACK);
    Bitboard black_bishops = board.pieces(PieceType::BISHOP, Color::BLACK);
    Bitboard black_rooks = board.pieces(PieceType::ROOK, Color::BLACK);
    Bitboard black_queens = board.pieces(PieceType::QUEEN, Color::BLACK);

    Color turn = board.sideToMove();
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
    
    // std::cout << "Material score: " << score << std::endl;
    
    // checkmate/draw checking
    if (board.isInsufficientMaterial() || board.isRepetition()){
        score = 0;
        // std::cout << "Draw detected, setting score to 0" << std::endl;
    }

    // std::cout << "Final score: " << score << std::endl;
    return score;
}

PYBIND11_MODULE(engine, m) {
    m.doc() = "engine cpp"; // optional module docstring

    m.def("evaluate", &evaluate, "evaluate the position");
}
