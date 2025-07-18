#pragma once

#include "chess.hpp"
#include <vector>

namespace utils
{

    extern int piece_square[7][64];
    std::tuple<std::vector<chess::Bitboard>, std::vector<chess::Bitboard>> generate_bitboards(const chess::Board& board);

}