#pragma once

#include <array>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <sstream>
#include <string_view>

#ifdef _WIN32
#include <process.h>
#define NOMINMAX // NOLINT
#include <windows.h>
#else
#include <time.h>
#include <unistd.h>
#endif

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
    public:
        Logger()
        {
            const std::string log_path = generate_log_path();
            log_file.open(log_path);
            if (!log_file.is_open())
            {
                throw std::runtime_error("Failed to open log file: " + log_path);
            }
        }

        ~Logger()
        {
            if (log_file.is_open())
            {
                log_file.close();
            }
        }

    private:
        std::ofstream log_file;

        static std::string get_date_time(const std::string& format_string = "DATE=%Y_%m_%d_TIME=_%H_%M_%S")
        // Let's hide all the macro-using functions
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
            oss << std::put_time(&ltm, format_string.c_str());
            return oss.str();
        }

        static std::string get_PID()
        {
#if defined(_WIN32)

            return std::to_string(GetCurrentProcessId());

#else
            return std::to_string(getpid());
#endif
        }

    public:
        static std::string generate_log_path()
        {
            return "../../logs/internal/" + get_date_time() + "_PID=" + get_PID() + ".log";
        }

        void log(const std::string& msg, LogLevel level = LogLevel::INFO)
        {
            log_file << LogStrings[static_cast<size_t>(level)] << msg << std::endl;
        }
    };
}
