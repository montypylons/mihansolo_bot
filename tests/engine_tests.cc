#include "chess.hpp"
#include <tuple>
#include <string>
#include <iostream>
#include "reader.hpp"
#include <optional>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <chrono>
#include <sstream>
#include "evaluation.hpp"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/logger.h"
#include "engine.hpp"
#include "gtest/gtest.h"

// many thanks to https://lichess.org/training for providing puzzle FENs

TEST(GameOverTest, BasicAssertions) 
{
    ASSERT_FALSE(engine::game_over(chess::Board("2r3k1/p4p2/6pp/1pr2b2/2p5/1PR1PB2/P4PPP/2R3K1 w - - 2 26")));
    ASSERT_FALSE(engine::game_over(chess::Board("4rbkr/ppp3pp/5N2/n7/3pP2q/5Q1P/PPP1K2P/R1B2R2 b - - 0 15")));
    ASSERT_FALSE(engine::game_over(chess::Board("6k1/3n3b/1pq1r1p1/p1bpPrPp/Pp1p3P/1N1P1N2/R1P3Q1/2B1R1K1 w - - 1 28")));
    ASSERT_FALSE(engine::game_over(chess::Board("5rk1/5pp1/8/4p3/Qp2b1Pq/4b2P/4B2K/3R1R2 w - - 2 35")));

    ASSERT_TRUE(engine::game_over(chess::Board("3Q1k2/p4p2/qp2p2p/7N/8/4PP2/5KPP/8 b - - 0 31")));
    ASSERT_TRUE(engine::game_over(chess::Board("rnb2rk1/3pp2Q/pq4p1/1p1P1p2/1p6/P1b2N2/2P1PPP1/R2K1B1R b - - 3 15")));
    ASSERT_TRUE(engine::game_over(chess::Board("8/8/8/8/8/5K2/N5Q1/7k b - - 30 85")));
    ASSERT_TRUE(engine::game_over(chess::Board("r4rk1/pbp2p1p/1p2pBp1/4N3/3P4/1BP1b3/PP3QqP/R4RK1 w - - 0 23")));
}


TEST(BookMoveTest, BasicAssertions)
{
    ASSERT_NO_FATAL_FAILURE(engine::init_book());
    ASSERT_NO_FATAL_FAILURE(engine::book_move(chess::Board("rnbqkbnr/ppp1pppp/8/3p4/2PP4/8/PP2PPPP/RNBQKBNR b KQkq - 0 2")));
    ASSERT_NO_FATAL_FAILURE(engine::book_move(chess::Board("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2")));
}

TEST(SearchTest, BasicAssertions){

}

TEST(LegalMovesTest, BasicAssertions){

}

TEST(MoveOrderingTest, BasicAssertions){

}

TEST(NegamaxTest, BasicAssertions){

}