#pragma once

#include <iomanip>

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
    extern bool log_TT;

    // Book move lookup
    std::optional<std::string> book_move(const chess::Board& board);

    // Search for best move (returns UCI string)
    std::string search(const std::optional<chess::Board>& fen,
                       const std::optional<TimeManagement::TimeManager>& manager1, int default_depth = 5,
                       std::ostream& output =
                           std::cout);

    // Negamax search (returns eval and best move)
    std::tuple<int, chess::Move> negamax(const std::optional<TimeManagement::TimeManager>& nega_manager,
                                         const chess::Move& PV_Move, TranspositionTable& table1, chess::Board& board,
                                         int alpha, int beta,
                                         const chess::Move& last_move,
                                         const int& depth, const int& ply, int numExtensions = 0);
    // Game over detection
    extern TranspositionTable table;

    inline bool game_over(const chess::Board& board)
    {
        chess::Movelist moves;
        chess::movegen::legalmoves(moves, board);
        if (moves.empty() || board.isHalfMoveDraw() || board.isInsufficientMaterial() || board.isRepetition())
        {
            return true;
        }

        return false;
    }

    inline auto get_date_time()
    {
        const auto now = std::chrono::system_clock::now();
        const std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        std::tm ltm{};
#ifdef _WIN32
        localtime_s(&ltm, &now_c); // thread-safe on Windows
#else
        localtime_r(&now_c, &ltm); // thread-safe on POSIX
#endif

        std::ostringstream oss;
        oss << std::put_time(&ltm, "%Y_%m_%d__%H_%M_%S");
        return oss.str();
    }


    // UCI protocol loop
    void start_uci(std::istream& in = std::cin, std::ostream& out = std::cout);

    inline bool is_promotion(const chess::Move& move);
    inline bool is_pawns_near_promotion(const chess::Board& board);

    const extern int initial_alpha;
    const extern int initial_beta;

    extern std::optional<TimeManagement::TimeManager> manager;
    extern bool abort_due_to_time;
}
