#include "chess.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace chess;

int material_eval(Board board)
{
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

    material_score += p_count * 100 * 1;
    material_score += n_count * 300 * 1;
    material_score += b_count * 300 * 1;
    material_score += r_count * 500 * 1;
    material_score += q_count * 900 * 1;
    material_score += p_count_black * 100 * -1;
    material_score += n_count_black * 300 * -1;
    material_score += b_count_black * 300 * -1;
    material_score += r_count_black * 500 * -1;
    material_score += q_count_black * 900 * -1;
}

int piece_square_eval(Board board)
{
    while (pawns)
    {
        int square = pawns.pop();
        int p_score = piece_square[0][side_to_move == Color::WHITE ? square : square ^ 56];
        positional_score += p_score;
    }
    while (knights)
    {
        int square = knights.pop();
        int n_score = piece_square[1][side_to_move == Color::WHITE ? square : square ^ 56];

        positional_score += n_score;
    }
    while (bishops)
    {
        int square = bishops.pop();
        int b_score = piece_square[2][side_to_move == Color::WHITE ? square : square ^ 56];

        positional_score += b_score;
    }
    while (rooks)
    {
        int square = rooks.pop();
        int r_score = piece_square[3][side_to_move == Color::WHITE ? square : square ^ 56];
        positional_score += r_score;
    }
    while (queens)
    {
        int square = queens.pop();
        int q_score = piece_square[4][side_to_move == Color::WHITE ? square : square ^ 56];

        positional_score += q_score;
    }

    while (black_pawns)
    {
        int square = black_pawns.pop();
        int p_score = piece_square[0][side_to_move == Color::WHITE ? square : square ^ 56];
        positional_score -= p_score;
    }
    while (black_knights)
    {
        int square = black_knights.pop();
        int n_score = piece_square[1][side_to_move == Color::WHITE ? square : square ^ 56];
        positional_score -= n_score;
    }
    while (black_bishops)
    {
        int square = black_bishops.pop();
        int b_score = piece_square[2][side_to_move == Color::WHITE ? square : square ^ 56];
        positional_score -= b_score;
    }
    while (black_rooks)
    {
        int square = black_rooks.pop();
        int r_score = piece_square[3][side_to_move == Color::WHITE ? square : square ^ 56];
        positional_score -= r_score;
    }
    while (black_queens)
    {
        int square = black_queens.pop();
        int q_score = piece_square[4][side_to_move == Color::WHITE ? square : square ^ 56];
        positional_score -= q_score;
    }
}

int game_over_eval(Board board, int ply = 0)
{
    bool is_endgame;
    bool check = board.inCheck();
    Movelist moves;
    movegen::legalmoves(moves, board);
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

int main_eval(Board board)
{
}

int evaluate(Board board, int ply = 0)
{
    int score = 0;
    int positional_score = 0;
    score += positional_score;
    int material_score = 0;
    score += material_score;
    return score;
}
