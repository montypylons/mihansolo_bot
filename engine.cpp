#include "chess.hpp"
#include <tuple>
#include <string>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace chess;

int evaluate(chess::Board board) {

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
    Movelist moves;
    movegen::legalmoves(moves, board);
    bool check = board.inCheck();
    bool no_moves = moves.empty();
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
    // mobility bonus
    // TODO: add this
    // checkmate/draw checking
    if (board.isInsufficientMaterial() || board.isRepetition() || !check && no_moves){
        score = 0;
    };
    if (check && no_moves && turn == Color::WHITE){
        score = -10000;
    }
    if (turn == Color::BLACK){
        score = -score;
    }

    return score;
}

