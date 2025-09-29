#pragma once

#include <string>
#include <tuple>
#include <optional>
#include "chess.hpp"
#include "timemanagement.hpp"
#include "tt.hpp"

namespace engine
{
    /* inline bool can_NMP(const chess::Board& board, int depth); */

    // Book initialization
    void init_book();
    extern bool log_TT;

    // Book move lookup
    std::optional<std::string> book_move(const chess::Board& board);

    // Search for best move (returns UCI string)
    std::string search(const std::optional<chess::Board>& fen,
                       TimeManagement::TimeManager& manager1, int default_depth = 5,
                       std::ostream& output =
                           std::cout);

    // Negamax search (returns eval and best move)
    std::tuple<int, chess::Move> negamax(TimeManagement::TimeManager& nega_manager,
                                         const chess::Move& PV_Move, TranspositionTable& table1, chess::Board& board,
                                         int alpha, int beta,
                                         const chess::Move& last_move,
                                         const int& depth, const int& ply, int numExtensions = 0);
    // Game over detection
    extern TranspositionTable table;

    inline bool game_over(const chess::Board& board, const chess::Movelist& moves)
    {
        return board.isHalfMoveDraw() || // if any are true then the game is over
            board.isRepetition() ||
            board.isInsufficientMaterial() ||
            moves.empty();
    }

    // UCI protocol loop
    void start_uci(std::istream& in = std::cin, std::ostream& out = std::cout);

    inline bool is_promotion(const chess::Move& move);
    inline bool is_pawns_near_promotion(const chess::Board& board);

    const extern int initial_alpha;
    const extern int initial_beta;

    extern TimeManagement::TimeManager manager;
    extern bool abort_due_to_time;
}
