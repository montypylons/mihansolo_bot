#include <gtest/gtest.h>
#include "evaluation.hpp"
#include "chess.hpp"
#include "utils.hpp"

TEST(BitboardTest, BasicAssertions)
{
    chess::Board board1("r4rk1/bppn2p1/p1nppq1p/4p3/PP2P3/1QPPBN1P/5PP1/R4RK1 b - - 3 15");
    auto generated_bitboards = evaluation::initialize_bitboards(board1);

    auto our_pieces = std::get<0>(generated_bitboards);
    auto enemy_pieces = std::get<1>(generated_bitboards);

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

    ASSERT_EQ(our_pieces.size(), 5);
    ASSERT_EQ(enemy_pieces.size(), 5);

    ASSERT_EQ(pawns.count(), 8);
    ASSERT_EQ(knights.count(), 2);
    ASSERT_EQ(bishops.count(), 1);
    ASSERT_EQ(rooks.count(), 2);
    ASSERT_EQ(queens.count(), 1);

    ASSERT_EQ(black_pawns.count(), 8);
    ASSERT_EQ(black_knights.count(), 1);
    ASSERT_EQ(black_bishops.count(), 1);
    ASSERT_EQ(black_rooks.count(), 2);
    ASSERT_EQ(black_queens.count(), 1);
}

TEST(MaterialEvalTest, BasicAssertions)
{
    chess::Board board1("r4rk1/bppn2p1/p1nppq1p/4p3/PP2P3/1QPPBN1P/5PP1/R4RK1 b - - 3 15");
    auto generated_bitboards = evaluation::initialize_bitboards(board1);

    auto our_pieces = std::get<0>(generated_bitboards);
    auto enemy_pieces = std::get<1>(generated_bitboards);

    int material_evaluation = evaluation::material_eval(
        board1,
        our_pieces[0], our_pieces[1], our_pieces[2], our_pieces[3], our_pieces[4],
        enemy_pieces[0], enemy_pieces[1], enemy_pieces[2], enemy_pieces[3], enemy_pieces[4]);
    ASSERT_EQ(material_evaluation, 300);
}

TEST(PSQTTest, BasicAssertions)
{
    chess::Board board1("r4rk1/bppn2p1/p1nppq1p/4p3/PP2P3/1QPPBN1P/5PP1/R4RK1 b - - 3 15");
    auto generated_bitboards = evaluation::initialize_bitboards(board1);

    auto our_pieces = std::get<0>(generated_bitboards);
    auto enemy_pieces = std::get<1>(generated_bitboards);

    int psqt_eval = evaluation::piece_square_eval(board1, our_pieces, enemy_pieces);
    ASSERT_EQ(psqt_eval, 10);
}

TEST(GameOverTest, BasicAssertions)
{
    // TODO: implement this to test game_over_eval
}
