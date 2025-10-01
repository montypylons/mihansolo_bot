#pragma once

#include "polyglot.hpp"
#include "chess.hpp"
#include <cstdint>
#include <vector>
#include <string>
#include <chrono>

// By Mihin Benaragama (@montypylons on Github)

namespace polyglot
{
    constexpr unsigned int last_3_bits = 0x7;

    constexpr unsigned int king_side_white = 0x0107;
    constexpr unsigned int king_side_black = 0x0f3f;
    constexpr unsigned int queen_side_white = 0x0100;
    constexpr unsigned int queen_side_black = 0x0f38;

    constexpr std::string files[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
    constexpr std::string ranks[] = {"1", "2", "3", "4", "5", "6", "7", "8"};
    constexpr std::string promotions[] = {"", "n", "b", "r", "q"};

    struct Entry
    {
        uint64_t key;
        uint16_t move;
        uint16_t weight;
        uint32_t learn;
    };

    enum class SelectionMethod
    {
        Random,
        Weight
    };

    class Reader
    {
        std::vector<Entry> book;

        static void swap_endians(std::vector<Entry>& entries);

    public:
        void LoadFromFile(const char* filename);
        void LoadFromArray(const unsigned char arr[], const unsigned int arr_len);
        uint16_t GetBookMove(SelectionMethod method, uint64_t zobrist_key);
        static std::string RawMoveToUci(uint16_t move, const chess::Board& board);
    };
}
