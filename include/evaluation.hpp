#pragma once

#include "chess.hpp"
#include <array>
#include <optional>

namespace evaluation
{
    int king_psqt_eval(const chess::Board& board, const std::array<chess::Bitboard,6>& pieces,
                       const std::array<chess::Bitboard,6>& enemy_pieces);

    bool is_endgame(const chess::Board& board);

    std::tuple<std::array<chess::Bitboard, 6>, std::array<chess::Bitboard, 6>> initialize_bitboards(
        const chess::Board& board);

    int material_eval(const chess::Bitboard& pawns, const chess::Bitboard& knights,
                      const chess::Bitboard& bishops, const chess::Bitboard& rooks, const chess::Bitboard& queens,
                      const chess::Bitboard& black_pawns, const chess::Bitboard& black_knights,
                      const chess::Bitboard& black_bishops,
                      const chess::Bitboard& black_rooks, const chess::Bitboard& black_queens);

    int piece_square_eval(const chess::Board& board, const std::array<chess::Bitboard,6>& pieces,
                          const std::array<chess::Bitboard,6>& enemy_pieces);

    std::optional<int> game_over_eval(const chess::Board& board, const int& ply = 0);

    int main_eval(const chess::Board& board, const int& ply = 0);
}
