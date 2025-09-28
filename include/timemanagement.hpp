#pragma once
#include <chrono>

#include "chess.hpp"

namespace TimeManagement
{
    constexpr int EMERGENCY_BUFFER = 25; // the min is 20, see include/engine_tests.cpp for explanation
    enum class TimeStatus
    {
        ManagerNotInitialized,
        TimeRanOut,
        TimeRemaining
    };

    class TimeManager
    {
    public:
        explicit TimeManager()
        = default;

        [[nodiscard]] TimeStatus time_status() const; // have you outrun the time allowed for this move
        void go(int wtime, int btime, int winc, int binc, const chess::Board& board);
        void movetime(int movetime);
        void no_time_control();

        bool is_initialized = false;

    private:
        int time_remaining_for_move = 0;
        std::chrono::steady_clock::time_point last_move_time;
    };
}
