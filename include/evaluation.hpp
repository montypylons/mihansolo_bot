#pragma once

#include "chess.hpp"
#include "utils.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <optional>

namespace evaluation
{
    std::tuple<std::vector<chess::Bitboard>, std::vector<chess::Bitboard>> initialize_bitboards(chess::Board board);

    int material_eval(chess::Board board, chess::Bitboard pawns, chess::Bitboard knights, chess::Bitboard bishops, chess::Bitboard rooks, chess::Bitboard queens, chess::Bitboard black_pawns, chess::Bitboard black_knights, chess::Bitboard black_bishops, chess::Bitboard black_rooks, chess::Bitboard black_queens);

    int piece_square_eval(chess::Board board, std::vector<chess::Bitboard> pieces, std::vector<chess::Bitboard> enemy_pieces);

    std::optional<int> game_over_eval(chess::Board board, int ply = 0);

    int main_eval(chess::Board board, int ply = 0);
}