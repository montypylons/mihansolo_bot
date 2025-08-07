#pragma once

#include "chess.hpp"
#include <string>
#include <tuple>
#include <optional>

#include "timemanagement.hpp"
#include "tt.hpp"

namespace engine
{
    /* inline bool can_NMP(const chess::Board& board, int depth); */

    // Book initialization
    void init_book();

    // Book move lookup
    std::optional<std::string> book_move(const chess::Board& board);

    // Search for best move (returns UCI string)
    std::string search(const std::optional<chess::Board>& fen,
                       const std::optional<TimeManagement::TimeManager>& manager1);

    // Negamax search (returns eval and best move)
    std::tuple<int, chess::Move> negamax(const chess::Move& PV_Move, TranspositionTable& table1, chess::Board& board,
                                         int alpha, int beta,
                                         const chess::Move& last_move,
                                         const int& depth, const int& ply);
    // Game over detection
    bool game_over(const chess::Board& board);

    // UCI protocol loop
    void start_uci();

    const extern int initial_alpha;
    const extern int initial_beta;
}
