#include "chess.hpp"
#include <chrono>
#include <iostream>

const auto board = chess::Board("r1bqr1k1/1pp2pbp/p1n3p1/3pp3/3P4/P2BPNP1/1PP1N1PP/R2Q1RK1 w - - 0 12");

int main()
{
    chess::Movelist moves;

    const auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++)
    {
        moves.clear();
        chess::movegen::legalmoves(moves, board);
    }
    const auto end = std::chrono::high_resolution_clock::now();
    const double time_per_call_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() /
        100.0 /
        1'000'000.0;
    std::cout << "Time taken for ALL: " << time_per_call_ms << " ms" << std::endl;

    const auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++)
    {
        moves.clear();
        chess::movegen::legalmoves(moves, board, chess::PieceGenType::BISHOP);
        chess::movegen::legalmoves(moves, board, chess::PieceGenType::KNIGHT);
        chess::movegen::legalmoves(moves, board, chess::PieceGenType::KING);
        chess::movegen::legalmoves(moves, board, chess::PieceGenType::ROOK);
        chess::movegen::legalmoves(moves, board, chess::PieceGenType::QUEEN);
        chess::movegen::legalmoves(moves, board, chess::PieceGenType::PAWN);
    }
    const auto end1 = std::chrono::high_resolution_clock::now();
    const double time_per_split_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count() /
        100.0 /
        1'000'000.0;
    std::cout << "Time taken for split piece types: " << time_per_split_ms << " ms" << std::endl;
}
