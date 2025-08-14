#pragma once

#include "chess.hpp"
#include <array>

namespace utils
{
    constexpr int BISHOP_MOBILITY_FACTOR = 3;
    constexpr int KNIGHT_MOBILITY_FACTOR = 3;
    constexpr int ROOK_MOBILITY_FACTOR = 5;
    constexpr int QUEEN_MOBILITY_FACTOR = 7;
    constexpr int GENERAL_MOBILITY_FACTOR = 5;

    constexpr int MOBILITY_FACTORS[17] = {
        0, 0, KNIGHT_MOBILITY_FACTOR, 0, BISHOP_MOBILITY_FACTOR, 0, 0, 0, ROOK_MOBILITY_FACTOR, 0, 0, 0, 0, 0, 0, 0,
        QUEEN_MOBILITY_FACTOR
    };


    constexpr int piece_square[7][64] = {
        // piece_square[piece][square] (piece -> 0,1,2,3,4)

        {
            0, 0, 0, 0, 0, 0, 0, 0, // rank 1 (a1-h1)
            5, 10, 10, -20, -20, 10, 10, 5, // rank 2 (a2-h2) - the -20 row
            5, -5, -10, 0, 0, -10, -5, 5, // rank 3 (a3-h3)
            0, 0, 0, 20, 20, 0, 0, 0, // rank 4 (a4-h4)
            5, 5, 10, 25, 25, 10, 5, 5, // rank 5 (a5-h5)
            10, 10, 20, 30, 30, 20, 10, 10, // rank 6 (a6-h6)
            50, 50, 50, 50, 50, 50, 50, 50, // rank 7 (a7-h7)
            0, 0, 0, 0, 0, 0, 0, 0 // rank 8 (a8-h8)
        },

        {
            -50, -40, -30, -30, -30, -30, -40, -50, // knight
            -40, -20, 0, 0, 0, 0, -20, -40,
            -30, 0, 10, 15, 15, 10, 0, -30,
            -30, 5, 15, 20, 20, 15, 5, -30,
            -30, 0, 15, 20, 20, 15, 0, -30,
            -30, 5, 10, 15, 15, 10, 5, -30,
            -40, -20, 0, 5, 5, 0, -20, -40,
            -50, -40, -30, -30, -30, -30, -40, -50
        },

        {
            -20, -10, -10, -10, -10, -10, -10, -20, // bishop rank 1 (a1-h1)
            -10, 5, 0, 0, 0, 0, 5, -10, // bishop rank 2 (a2-h2)
            -10, 10, 10, 10, 10, 10, 10, -10, // bishop rank 3 (a3-h3)
            -10, 0, 10, 10, 10, 10, 0, -10, // bishop rank 4 (a4-h4)
            -10, 5, 5, 10, 10, 5, 5, -10, // bishop rank 5 (a5-h5)
            -10, 0, 5, 10, 10, 5, 0, -10, // bishop rank 6 (a6-h6)
            -10, 0, 0, 0, 0, 0, 0, -10, // bishop rank 7 (a7-h7)
            -20, -10, -10, -10, -10, -10, -10, -20 // bishop rank 8 (a8-h8)
        },
        {
            0, 0, 0, 5, 5, 0, 0, 0, // rook rank 1 (a1-h1)
            -5, 0, 0, 0, 0, 0, 0, -5, // rook rank 2 (a2-h2)
            -5, 0, 0, 0, 0, 0, 0, -5, // rook rank 3 (a3-h3)
            -5, 0, 0, 0, 0, 0, 0, -5, // rook rank 4 (a4-h4)
            -5, 0, 0, 0, 0, 0, 0, -5, // rook rank 5 (a5-h5)
            -5, 0, 0, 0, 0, 0, 0, -5, // rook rank 6 (a6-h6)
            5, 10, 10, 10, 10, 10, 10, 5, // rook rank 7 (a7-h7)
            0, 0, 0, 0, 0, 0, 0, 0 // rook rank 8 (a8-h8)
        },

        {
            -20, -10, -10, -5, -5, -10, -10, -20, // queen rank 1 (a1-h1)
            -10, 0, 5, 0, 0, 0, 0, -10, // queen rank 2 (a2-h2)
            -10, 5, 5, 5, 5, 5, 0, -10, // queen rank 3 (a3-h3)
            0, 0, 5, 5, 5, 5, 0, -5, // queen rank 4 (a4-h4)
            -5, 0, 5, 5, 5, 5, 0, -5, // queen rank 5 (a5-h5)
            -10, 0, 5, 5, 5, 5, 0, -10, // queen rank 6 (a6-h6)
            -10, 0, 0, 0, 0, 0, 0, -10, // queen rank 7 (a7-h7)
            -20, -10, -10, -5, -5, -10, -10, -20 // queen rank 8 (a8-h8)
        },
        {
            20, 30, 10, 0, 0, 10, 30, 20, // king middle game rank 1 (a1-h1)
            20, 20, 0, 0, 0, 0, 20, 20, // king middle game rank 2 (a2-h2)
            -10, -20, -20, -20, -20, -20, -20, -10, // king middle game rank 3 (a3-h3)
            -20, -30, -30, -40, -40, -30, -30, -20, // king middle game rank 4 (a4-h4)
            -30, -40, -40, -50, -50, -40, -40, -30, // king middle game rank 5 (a5-h5)
            -30, -40, -40, -50, -50, -40, -40, -30, // king middle game rank 6 (a6-h6)
            -30, -40, -40, -50, -50, -40, -40, -30, // king middle game rank 7 (a7-h7)
            -30, -40, -40, -50, -50, -40, -40, -30 // king middle game rank 8 (a8-h8)
        },
        {
            -50, -30, -30, -30, -30, -30, -30, -50, // king end game rank 1 (a1-h1)
            -30, -30, 0, 0, 0, 0, -30, -30, // king end game rank 2 (a2-h2)
            -30, -10, 20, 30, 30, 20, -10, -30, // king end game rank 3 (a3-h3)
            -30, -10, 30, 40, 40, 30, -10, -30, // king end game rank 4 (a4-h4)
            -30, -10, 30, 40, 40, 30, -10, -30, // king end game rank 5 (a5-h5)
            -30, -10, 20, 30, 30, 20, -10, -30, // king end game rank 6 (a6-h6)
            -30, -20, -10, 0, 0, -10, -20, -30, // king end game rank 7 (a7-h7)
            -50, -40, -30, -20, -20, -30, -40, -50 // king end game rank 8 (a8-h8)
        },
    };
    constexpr int piece_values[7] = {
        100, // PAWN
        300, // KNIGHT
        300, // BISHOP
        500, // ROOK
        900, // QUEEN
        0, // KING (usually infinite, but 0 in evaluation)
        0 // NONE
    };


    std::tuple<std::array<chess::Bitboard, 6>, std::array<chess::Bitboard, 6>> generate_bitboards(
        const chess::Board& board);
    int MVV_LAA_helper(const chess::Board& board, const chess::Move& move);
    inline int history_heuristic_helper(const int (&history)[2][64][64], const chess::Board& board,
                                        const chess::Move& move);
    void order_moves(const int (&history)[2][64][64], const chess::Move& PV_Move, chess::Movelist& moves,
                     const chess::Board& board);
    void order_capture_moves(chess::Movelist& moves, const chess::Board& board);
}
