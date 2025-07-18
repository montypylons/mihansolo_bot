#pragma once

#include "chess.hpp"
#include <vector>
#include <optional>

namespace evaluation
{
    std::tuple<std::vector<chess::Bitboard>, std::vector<chess::Bitboard>> initialize_bitboards(
        const chess::Board& board);

    int material_eval(const chess::Bitboard& pawns, const chess::Bitboard& knights,
                      const chess::Bitboard& bishops, const chess::Bitboard& rooks, const chess::Bitboard& queens,
                      const chess::Bitboard& black_pawns, const chess::Bitboard& black_knights,
                      const chess::Bitboard& black_bishops,
                      const chess::Bitboard& black_rooks, const chess::Bitboard& black_queens);

    int piece_square_eval(const chess::Board& board, const std::vector<chess::Bitboard>& pieces,
                          const std::vector<chess::Bitboard>& enemy_pieces);

    std::optional<int> game_over_eval(const chess::Board& board, const int& ply = 0);

    int main_eval(const chess::Board& board, const int& ply = 0);
}
