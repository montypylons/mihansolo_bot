#pragma once

#include "chess.hpp"
#include <string>
#include <tuple>
#include <optional>

namespace engine
{
    // logger initialization
    void init_logger();

    // Book initialization
    void init_book();

    // Book move lookup
    std::optional<std::string> book_move(const chess::Board& board);

    // Search for best move (returns UCI string)
    std::string search(const std::optional<chess::Board>& fen);

    // Negamax search (returns eval and best move)
    std::tuple<int, chess::Move> negamax(chess::Board& board, int alpha, int beta, const chess::Move& last_move,
                                         const int& depth, const int& ply);
    // Game over detection
    bool game_over(const chess::Board& board);

    // Generate legal moves
    chess::Movelist get_legal_moves(const chess::Board& board);

    // Move ordering heuristic
    int move_ordering(const chess::Board& board, const std::string& move_uci);

    // UCI protocol loop
    void start_uci();

    const extern int initial_alpha;
    const extern int initial_beta;
}
