#pragma once

#include "chess.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

namespace utils
{

    extern int piece_square[7][64];
    extern int piece_values[5];
    std::tuple<std::vector<chess::Bitboard>, std::vector<chess::Bitboard>> generate_bitboards(chess::Board board);

}