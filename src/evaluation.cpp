#include "chess.hpp"
#include "utils.hpp"
#include "evaluation.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

auto initialize_bitboards(chess::Board board)
{
    // Gets bitboards for each piece from the chess::Board
    // pawns, knights, bishops, rooks, queens, then same but black_pawns, etc.
    auto generated_bitboards = utils::generate_bitboards(board);
    return generated_bitboards;
}

int material_eval(chess::Board board, chess::Bitboard pawns, chess::Bitboard knights, chess::Bitboard bishops, chess::Bitboard rooks, chess::Bitboard queens, chess::Bitboard black_pawns, chess::Bitboard black_knights, chess::Bitboard black_bishops, chess::Bitboard black_rooks, chess::Bitboard black_queens)
{
    // intialize score
    int material_score = 0;

    // basic material counting
    int p_count = pawns.count();
    int n_count = knights.count();
    int b_count = bishops.count();
    int r_count = rooks.count();
    int q_count = queens.count();

    int p_count_black = black_pawns.count();
    int n_count_black = black_knights.count();
    int b_count_black = black_bishops.count();
    int r_count_black = black_rooks.count();
    int q_count_black = black_queens.count();
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

int piece_square_eval(chess::Board board, std::vector<chess::Bitboard> pieces, std::vector<chess::Bitboard> enemy_pieces)
{
    // initialize variables
    int positional_score = 0;

    for (auto bitboard : pieces)
    {
        while (bitboard)
        {
            int square = bitboard.pop();
            positional_score += utils::piece_square[0][board.at(chess::Square(square)).color() == chess::Color::WHITE ? square : square ^ 56];
        }
    }

    for (auto bitboard : enemy_pieces)
    {
        while (bitboard)
        {
            int square = bitboard.pop();
            positional_score -= utils::piece_square[0][board.at(chess::Square(square)).color() == chess::Color::WHITE ? square : square ^ 56];
        }
    }

    return positional_score;
}

int game_over_eval(chess::Board board, int ply = 0)
{
    bool is_endgame;
    bool check = board.inCheck();
    chess::Movelist moves;
    chess::movegen::legalmoves(moves, board);
    bool no_moves = moves.empty();
    if (check && no_moves)
    {
        return -10000 + ply;
    }
    if (board.isInsufficientMaterial() || board.isRepetition() || (!check && no_moves))
    {
        return 0;
    }
}

int main_eval(chess::Board board)
{
    auto generated_bitboards = initialize_bitboards(board);
    std::vector<chess::Bitboard> our_pieces = std::get<0>(generated_bitboards);
    std::vector<chess::Bitboard> enemy_pieces = std::get<1>(generated_bitboards);

    auto pawns = our_pieces[0];
    auto knights = our_pieces[1];
    auto bishops = our_pieces[2];
    auto rooks = our_pieces[3];
    auto queens = our_pieces[4];
    auto black_pawns = enemy_pieces[0];
    auto black_knights = enemy_pieces[1];
    auto black_bishops = enemy_pieces[2];
    auto black_rooks = enemy_pieces[3];
    auto black_queens = enemy_pieces[4];
}
