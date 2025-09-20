#pragma once

namespace Logging
{
    constexpr std::array<std::string_view, 4> LogStrings = {"INFO: ", "WARNING: ", "DEBUG: ", "FATAL: "};

    enum class LogLevel
    {
        INFO,
        WARNING,
        DEBUG,
        FATAL
    };

    class Logger
    {
        std::ofstream log_file;
        std::string log_path = generate_log_path();
        static std::string get_date_time()
        {
            const auto now = std::chrono::system_clock::now();
            const std::time_t now_c = std::chrono::system_clock::to_time_t(now);

            std::tm ltm{};
#ifdef _WIN32
#include <process.h>
            localtime_s(&ltm, &now_c); // thread-safe on Windows
#else
#include <time.h>
            localtime_r(&now_c, &ltm); // thread-safe on POSIX
#endif

            std::ostringstream oss;
            oss << std::put_time(&ltm, "DATE=%Y_%m_%d_TIME=_%H_%M_%S");
            return oss.str();
        }

        static std::string get_PID()
        {
#if defined(_WIN32)
#include <windows.h>

                return GetCurrentProcessId();

#else
#include <unistd.h>
          return getpid();
#endif
        }

    public:

        static std::string generate_log_path()
        {
            return "../logs/internal/" + get_date_time() + "_PID="+get_PID() + ".log";
        }

        void log(const std::string& msg, LogLevel level = LogLevel::INFO)
        {
            log_file.open(log_path);
            if (!log_file.is_open())
            {
                throw std::runtime_error("Failed to open log file.");
            }
            log_file << LogStrings[static_cast<size_t>(level)] << msg;
            log_file.close();
        }
    };
}
