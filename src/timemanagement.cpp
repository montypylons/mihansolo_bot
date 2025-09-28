#include "timemanagement.hpp"
#include "chess.hpp"
#include <chrono>

namespace TimeManagement
{
    TimeStatus TimeManager::time_status() const
    {
        if (!is_initialized) return TimeStatus::ManagerNotInitialized;

        if (const auto now = std::chrono::steady_clock::now();
            std::chrono::duration_cast<std::chrono::milliseconds>(now - last_move_time)
            >=
            std::chrono::duration_cast<std::chrono::milliseconds>(time_remaining_for_move))
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
     * @param side_to_move
     */
    void TimeManager::go(const int wtime, const int btime, const int winc, const int binc,
                         const chess::Color side_to_move)
    {
        is_initialized = true;
        if (side_to_move == chess::Color::WHITE)
        {
            time_remaining_for_move = std::chrono::milliseconds(wtime / 20 + winc / 2);
        }
        else
        {
            time_remaining_for_move = std::chrono::milliseconds(btime / 20 + binc / 2);
        }
        last_move_time = std::chrono::steady_clock::now();
    }

    /**
     * @param movetime UCI movetime parameter
     */
    void TimeManager::movetime(const int movetime) // side to move does not matter
    {
        is_initialized = true;

        last_move_time = std::chrono::steady_clock::now();
        time_remaining_for_move = std::chrono::milliseconds(movetime);
    }

    void TimeManager::no_time_control()
    {
        is_initialized = false;
    }
}
