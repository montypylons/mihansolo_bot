#include "timemanagement.hpp"
#include <chrono>

namespace TimeManagement
{
    bool TimeManager::time_remaining() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_move_time).
            count() < time_remaining_for_move;
    }

    /**
     *
     * @param wtime Default 0, UCI wtime
     * @param btime Default 0, UCI wtime
     * @param winc Default 0, UCI winc
     * @param binc Default 0, UCI binc
     * @param movetime Default -1, UCI movetime
     */
    void TimeManager::go(const int wtime, const int btime, const int winc, const int binc,
                         const int movetime)
    {
        if (movetime > 0)
        {
            last_move_time = std::chrono::steady_clock::now();
            time_remaining_for_move = movetime;
            return;
        }
        if (white)
        {
            last_move_time = std::chrono::steady_clock::now();
            time_remaining_for_move = wtime / 20 + winc / 2;
        }
        if (!white)
        {
            last_move_time = std::chrono::steady_clock::now();
            time_remaining_for_move = btime / 20 + binc / 2;
        }
    }
}
