#include "chess.hpp"
#include "utils.hpp"
#include "evaluation.hpp"
#include <vector>

namespace evaluation
{
    std::tuple<std::vector<chess::Bitboard>, std::vector<chess::Bitboard>> initialize_bitboards(
        const chess::Board& board)
    {
        // Gets bitboards for each piece from the chess::Board
        // pawns, knights, bishops, rooks, queens, then same but black_pawns, etc.
        auto generated_bitboards = utils::generate_bitboards(board);
        return generated_bitboards;
    }

    int material_eval(const chess::Bitboard& pawns, const chess::Bitboard& knights,
                      const chess::Bitboard& bishops, const chess::Bitboard& rooks, const chess::Bitboard& queens,
                      const chess::Bitboard& black_pawns, const chess::Bitboard& black_knights,
                      const chess::Bitboard& black_bishops,
                      const chess::Bitboard& black_rooks, const chess::Bitboard& black_queens)
    {
        // initialize score
        int material_score = 0;

        // basic material counting
        const int p_count = pawns.count();
        const int n_count = knights.count();
        const int b_count = bishops.count();
        const int r_count = rooks.count();
        const int q_count = queens.count();

        const int p_count_black = black_pawns.count();
        const int n_count_black = black_knights.count();
        const int b_count_black = black_bishops.count();
        const int r_count_black = black_rooks.count();
        const int q_count_black = black_queens.count();
        // add to score
        material_score += p_count * 100 * 1;
        material_score += n_count * 300 * 1;
        material_score += b_count * 300 * 1;
        material_score += r_count * 500 * 1;
        material_score += q_count * 900 * 1;

        // subtract opposite side's piece values
        material_score -= p_count_black * 100;
        material_score -= n_count_black * 300;
        material_score -= b_count_black * 300;
        material_score -= r_count_black * 500;
        material_score -= q_count_black * 900;

        // give material imbalance FROM POV of side to move
        return material_score;
    }

    int piece_square_eval(const chess::Board& board, const std::vector<chess::Bitboard>& pieces,
                          const std::vector<chess::Bitboard>& enemy_pieces)
    {
        // initialize variables
        int positional_score = 0;
        // our pieces
        for (auto bitboard : pieces)
        {
            while (bitboard)
            {
                int square = bitboard.pop();

                auto piece = board.at(chess::Square(square));

                const int piece_index = static_cast<int>(piece.type());

                square = board.at(chess::Square(square)).color() == chess::Color::WHITE ? square : square ^ 56;

                const int psqt_value = utils::piece_square[piece_index][square];

                positional_score += psqt_value;
            }
        }
        // enemy pieces
        for (auto bitboard : enemy_pieces)
        {
            while (bitboard)
            {
                int square = bitboard.pop();

                auto piece = board.at(chess::Square(square));

                const int piece_index = static_cast<int>(piece.type());

                square = board.at(chess::Square(square)).color() == chess::Color::WHITE ? square : square ^ 56;

                const int psqt_value = utils::piece_square[piece_index][square];

                positional_score -= psqt_value;
            }
        }

        return positional_score;
    }

    std::optional<int> game_over_eval(const chess::Board& board, const int& ply)
    {
        const bool check = board.inCheck();

        chess::Movelist moves;
        chess::movegen::legalmoves(moves, board);

        const bool no_moves = moves.empty();

        if (check && no_moves)
        {
            return -10000 + ply;
        }
        if (board.isInsufficientMaterial() || board.isRepetition() || (!check && no_moves))
        {
            return 0;
        }
        return std::nullopt;
    }

    int main_eval(const chess::Board& board, const int& ply)
    {
        int score = 0;

        if (const std::optional<int> result = game_over_eval(board, ply); result != std::nullopt)
        {
            return result.value();
        }

        const auto generated_bitboards = initialize_bitboards(board);

        const std::vector<chess::Bitboard> our_pieces = std::get<0>(generated_bitboards);
        const std::vector<chess::Bitboard> enemy_pieces = std::get<1>(generated_bitboards);

        const auto pawns = our_pieces[0];
        const auto knights = our_pieces[1];
        const auto bishops = our_pieces[2];
        const auto rooks = our_pieces[3];
        const auto queens = our_pieces[4];
        const auto black_pawns = enemy_pieces[0];
        const auto black_knights = enemy_pieces[1];
        const auto black_bishops = enemy_pieces[2];
        const auto black_rooks = enemy_pieces[3];
        const auto black_queens = enemy_pieces[4];

        score += material_eval(pawns, knights, bishops, rooks, queens, black_pawns, black_knights, black_bishops,
                               black_rooks, black_queens);
        score += piece_square_eval(board, our_pieces, enemy_pieces);

        return score;
    }
} // namespace evaluation
