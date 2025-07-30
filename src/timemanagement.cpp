#include "timemanagement.hpp"
#include <chrono>

namespace TimeManagement
{
    bool TimeManager::time_remaining() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_move_time).
            count() > time_remaining_for_move;
    }

    void TimeManager::go(const int wtime, const int btime, const int winc, const int binc)
    {
        last_move_time = std::chrono::steady_clock::now();
        if (white)
        {
            time_remaining_for_move = wtime / 20 + winc / 2;
        }
        if (!white)
        {
            time_remaining_for_move = btime / 20 + binc / 2;
        }
    }
}
