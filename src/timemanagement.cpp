#include "timemanagement.hpp"
#include "chess.hpp"
#include <chrono>

namespace TimeManagement
{
    TimeStatus TimeManager::time_status() const
    {
        if (!is_initialized) return TimeStatus::ManagerNotInitialized;

        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_move_time).
            count() <= time_remaining_for_move)
        {
            return TimeStatus::TimeRanOut;
        }

        return TimeStatus::TimeRemaining;
    }

    /**
     *
     * @param wtime Default 0, UCI wtime
     * @param btime Default 0, UCI wtime
     * @param winc Default 0, UCI winc
     * @param binc Default 0, UCI binc
     * @param board
     */
    void TimeManager::go(const int wtime, const int btime, const int winc, const int binc, const chess::Board& board)
    {
        is_initialized = true;

        if (board.sideToMove() == chess::Color::WHITE)
        {
            last_move_time = std::chrono::steady_clock::now();
            time_remaining_for_move = wtime / 20 + winc / 2;
        }
        else
        {
            last_move_time = std::chrono::steady_clock::now();
            time_remaining_for_move = btime / 20 + binc / 2;
        }
    }

    /**
     * @param movetime UCI movetime parameter
     */
    void TimeManager::movetime(const int movetime) // side to move does not matter
    {
        is_initialized = true;

        last_move_time = std::chrono::steady_clock::now();
        time_remaining_for_move = movetime;
    }

    void TimeManager::no_time_control()
    {
        is_initialized = false;
    }
}
