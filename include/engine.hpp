#pragma once

#include "chess.hpp"
#include <string>
#include <tuple>
#include <optional>
#include <vector>

namespace engine{
// Book initialization
void init_book();

// Book move lookup
std::optional<std::string> book_move(chess::Board board);

// Search for best move (returns UCI string)
std::string search(const std::string &fen);

// Negamax search (returns eval and best move)
std::tuple<int, chess::Move> negamax(
    chess::Board board, int alpha, int beta, chess::Move last_move, int depth, int ply);

// Game over detection
bool game_over(chess::Board board);

// Generate legal moves
chess::Movelist get_legal_moves(chess::Board board);

// Move ordering heuristic
int move_ordering(chess::Board board, std::string move_uci);

// UCI protocol loop
void start_uci();
}