#include "chess.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace chess;

extern int piece_square[7][64];

std::vector<Bitboard> generate_bitboards(Board board);

