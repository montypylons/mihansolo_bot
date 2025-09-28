#pragma once
#include <chrono>

namespace TimeManagement
{
    constexpr int EMERGENCY_BUFFER = 25; // the min is 20, see include/engine_tests.cpp for explanation

    class TimeManager
    {
    public:
        explicit TimeManager()
        {
        }

        void initialize(bool is_white);
        [[nodiscard]] bool time_remaining() const; // have you outrun the time allowed for this move
        void go(int wtime, int btime, int winc, int binc, int movetime = -1);
        bool white{}; // true if bot is White, false if bot is Black
        bool is_initialized = false;

    private:
        int time_remaining_for_move = 0;
        std::chrono::steady_clock::time_point last_move_time;
    };
}
