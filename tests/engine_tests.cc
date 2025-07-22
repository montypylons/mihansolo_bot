#include "chess.hpp"
#include <tuple>
#include <string>
#include "reader.hpp"
#include <optional>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <sstream>
#include "engine.hpp"
#include "gtest/gtest.h"

// many thanks to https://lichess.org/training for providing puzzle FENs

TEST(GameOverTest, BasicAssertions)
{
    ASSERT_FALSE(engine::game_over(chess::Board("2r3k1/p4p2/6pp/1pr2b2/2p5/1PR1PB2/P4PPP/2R3K1 w - - 2 26")));
    ASSERT_FALSE(engine::game_over(chess::Board("4rbkr/ppp3pp/5N2/n7/3pP2q/5Q1P/PPP1K2P/R1B2R2 b - - 0 15")));
    ASSERT_FALSE(
        engine::game_over(chess::Board("6k1/3n3b/1pq1r1p1/p1bpPrPp/Pp1p3P/1N1P1N2/R1P3Q1/2B1R1K1 w - - 1 28")));
    ASSERT_FALSE(engine::game_over(chess::Board("5rk1/5pp1/8/4p3/Qp2b1Pq/4b2P/4B2K/3R1R2 w - - 2 35")));

    ASSERT_TRUE(engine::game_over(chess::Board("3Q1k2/p4p2/qp2p2p/7N/8/4PP2/5KPP/8 b - - 0 31")));
    ASSERT_TRUE(engine::game_over(chess::Board("rnb2rk1/3pp2Q/pq4p1/1p1P1p2/1p6/P1b2N2/2P1PPP1/R2K1B1R b - - 3 15")));
    ASSERT_TRUE(engine::game_over(chess::Board("8/8/8/8/8/5K2/N5Q1/7k b - - 30 85")));
    ASSERT_TRUE(engine::game_over(chess::Board("r4rk1/pbp2p1p/1p2pBp1/4N3/3P4/1BP1b3/PP3QqP/R4RK1 w - - 0 23")));
}

TEST(BookMoveTest, BasicAssertions)
{
    ASSERT_NO_FATAL_FAILURE(engine::init_book());
    ASSERT_TRUE(
        engine::book_move(chess::Board("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2")).has_value());
    ASSERT_TRUE(
        engine::book_move(chess::Board("rnbqkbnr/ppp1pppp/8/3p4/2PP4/8/PP2PPPP/RNBQKBNR b KQkq - 0 2")).has_value());
    ASSERT_TRUE(
        engine::book_move(chess::Board("r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 1")).has_value(
        ));

    ASSERT_FALSE(
        engine::book_move(chess::Board("2rq1rk1/pQ3Rbp/3p2p1/1p4N1/2p3N1/2P5/PP3PPP/n5K1 b - - 0 21")).has_value());
}

TEST(SearchTestMateInOne, BasicAssertions)
{
    const std::string result1 = engine::search(chess::Board("1k6/1b6/3p1Q2/1p1P3p/1P2PR2/8/r2r4/5K2 b - - 0 41"));
    ASSERT_EQ(result1, "d2d1");

    const std::string result2 = engine::search(chess::Board("2r5/5Qnk/3p1Rp1/3Pp3/2P3PK/4q2P/8/2R5 b - - 6 43"));
    ASSERT_EQ(result2, "g6g5");

    const std::string result3 = engine::search(chess::Board("3rn2R/ppp1qkp1/8/2Np1r2/3Pp3/2P5/PP4Q1/1K4R1 w - - 6 32"));
    ASSERT_EQ(result3, "g2g6");

    const std::string result4 = engine::search(chess::Board("4Q3/p7/6p1/P1b2k2/3pq1p1/5N1P/2P5/7K w - - 0 41"));
    ASSERT_EQ(result4, "e8f7");
}

TEST(SearchTestMateInTwo, BasicAssertions)
{
}

TEST(LegalMovesTest, BasicAssertions)
{
}

TEST(MoveOrderingTest, BasicAssertions)
{
}

TEST(NegamaxTest, BasicAssertions)
{
    auto board2 = chess::Board("8/1k6/3b4/8/8/8/7R/1K6 b - - 0 1");

    const auto negamax_result2 = chess::uci::moveToUci(
        std::get<1>(engine::negamax(board2, engine::initial_alpha, engine::initial_beta, chess::Move::NO_MOVE, 3, 0)));
    const std::string expected_move2 = chess::uci::moveToUci(
        chess::Move::make<chess::Move::NORMAL>(chess::Square::SQ_D6, chess::Square::SQ_H2));

    ASSERT_EQ(negamax_result2, expected_move2);
}

TEST(SearchTestCrushingMove, BasicAssertions)
{
    const std::string search_result = engine::search(
        chess::Board("r1bqkb1r/pppp1ppp/2n2n2/4P3/8/5N2/PPP1PPPP/RNBQKB1R w KQkq - 3 4"));
    ASSERT_EQ(search_result, "e5f6");
}
