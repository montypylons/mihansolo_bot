#pragma once

#include "chess.hpp"
#include <array>

namespace utils
{

    extern int piece_square[7][64];
    extern int piece_values[7];
    std::tuple<std::array<chess::Bitboard,6>, std::array<chess::Bitboard,6>> generate_bitboards(const chess::Board& board);

}