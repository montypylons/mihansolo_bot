#pragma once

#include "chess.hpp"
#include <string>
#include <tuple>
#include <optional>
#include "tt.hpp"

namespace engine
{
    int MVV_LAA_helper(const chess::Board& board, const chess::Move& move);

    chess::Movelist MVV_LAA(const chess::Move& PV_Move, chess::Movelist& moves, const chess::Board& board);

    // Book initialization
    void init_book();

    // Book move lookup
    std::optional<std::string> book_move(const chess::Board& board);

    // Search for best move (returns UCI string)
    std::string search(const std::optional<chess::Board>& fen);

    // Negamax search (returns eval and best move)
    std::tuple<int, chess::Move> negamax(const chess::Move& PV_Move, TranspositionTable& table, chess::Board& board,
                                         int alpha, int beta,
                                         const chess::Move& last_move,
                                         const int& depth, const int& ply);
    // Game over detection
    bool game_over(const chess::Board& board);

    // Move ordering heuristic
    int move_ordering(const chess::Board& board, const std::string& move_uci);

    // UCI protocol loop
    void start_uci();

    const extern int initial_alpha;
    const extern int initial_beta;
}
