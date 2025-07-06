#include <gtest/gtest.h>
#include "evaluation.hpp"
#include "chess.hpp"
#include "utils.hpp"

chess::Board board = chess::Board("r4rk1/bppn2p1/p1nppq1p/4p3/PP2P3/1QPPBN1P/5PP1/R4RK1 b - - 3 15");
std::tuple<std::vector<chess::Bitboard>, std::vector<chess::Bitboard>> generated_bitboards = evaluation::initialize_bitboards(board);

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

TEST(BitboardTest, BasicAssertions)
{
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
  int material_evaluation = evaluation::material_eval(board, pawns, knights, bishops, rooks, queens,
                                        black_pawns, black_knights, black_bishops, black_rooks, black_queens);
  ASSERT_EQ(material_evaluation, 300);
}

TEST(PSQTTest, BasicAssertions)
{
  int psqt_eval = evaluation::piece_square_eval(board, our_pieces, enemy_pieces);
  ASSERT_EQ(psqt_eval, 10);
}

TEST(GameOverTest, BasicAssertions){
  // TODO: implement this to test game_over_eval
}