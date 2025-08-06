#pragma once

#include "chess.hpp"
#include <array>

namespace utils
{
    extern int piece_square[7][64];
    extern int piece_values[7];
    std::tuple<std::array<chess::Bitboard, 6>, std::array<chess::Bitboard, 6>> generate_bitboards(
        const chess::Board& board);
    int MVV_LAA_helper(const chess::Board& board, const chess::Move& move);
    inline int history_heuristic_helper(const int (&history)[2][64][64], const chess::Board& board,
                                        const chess::Move& move);
    chess::Movelist order_moves(const int (&history)[2][64][64], const chess::Move& PV_Move, chess::Movelist& moves,
                                const chess::Board& board);
}
