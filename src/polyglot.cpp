#include "polyglot.hpp"
#include "chess.hpp"
#include <cstdint>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <bit>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

// By Mihin Benaragama (@montypylons on Github)
// Thanks to http://hgm.nubati.net/book_format.html for explaining the PolyGlot book format

// TODO: lazy endian swapping

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

        static void swap_endians(std::vector<Entry>& entries)
        {
            for (auto& [key, move, weight, learn] : entries)
            {
                key = std::byteswap(key);
                move = std::byteswap(move);
                weight = std::byteswap(weight);
                learn = std::byteswap(learn);
            }
        }

    public:
        void LoadFromFile(const char* filename)
        {
            std::ifstream bookFile(filename, std::ios::in | std::ios::binary);
            if (!bookFile.is_open()) throw std::invalid_argument(std::string("Failed to open book at: ") + filename);

            book.clear();
            Entry entry;

            while (bookFile.read(reinterpret_cast<char*>(&entry), sizeof(entry)))
            {
                book.push_back(entry);
            }
            if constexpr (std::endian::native == std::endian::little)
            {
                swap_endians(book);
            }
        }

        void LoadFromArray(const unsigned char arr[], const unsigned int arr_len)
        {
            // made to work with xxd hex dumps for embedded books
            if (arr_len % 16 != 0) throw std::invalid_argument("Array does not contain a whole number of entries");

            book.clear();

            book.resize(arr_len / sizeof(Entry));
            std::memcpy(book.data(), arr, arr_len);

            if constexpr (std::endian::native == std::endian::little)
            {
                swap_endians(book);
            }
        }

        uint16_t GetBookMove(const SelectionMethod method, const uint64_t zobrist_key)
        {
            std::vector<Entry> matching_entries;

            const auto lower_range = std::lower_bound(book.begin(), book.end(), zobrist_key,
                                                      [](const Entry& entry, const int key)
                                                      {
                                                          return entry.key < key;
                                                      });

            const auto upper_range = std::upper_bound(book.begin(), book.end(), zobrist_key,
                                                      [](const int key, const Entry& entry)
                                                      {
                                                          return key < entry.key;
                                                      });

            for (auto it = lower_range; it != upper_range; ++it)
            {
                if (it->key == zobrist_key)
                {
                    matching_entries.push_back(*it);
                }
            }
            if (matching_entries.empty()) throw std::runtime_error("No entries found!");

            switch (method)
            {
            case SelectionMethod::Random:
                {
                    const unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();

                    std::mt19937 generator(seed);

                    constexpr int min_val = 0;
                    const int max_val = matching_entries.size() - 1;

                    std::uniform_int_distribution distribution(min_val, max_val);

                    const int random_number = distribution(generator);

                    return matching_entries[random_number].move;
                }
            case SelectionMethod::Weight:
                {
                    uint16_t best_move{};
                    uint16_t best_weight{};

                    for (const auto& entry : matching_entries)
                    {
                        if (entry.weight > best_weight) best_move = entry.move;
                        best_weight = entry.weight;
                    }
                    return best_move;
                }
            default:
                throw std::runtime_error("Unknown SelectionMethod.");
            }
        }

        static std::string RawMoveToUci(const uint16_t move, const chess::Board& board)
        {
            /* example raw move: 0b0110100000000111
            starts from 0, RIGHT TO LEFT [ <- ]
            shift 3 right would get: 0b0000110100000000
            since it is now little-endian, the least significant bits are first
            */
            if (
                move == king_side_white && board.castlingRights().has(chess::Color::WHITE,
                                                                      chess::Board::CastlingRights::Side::KING_SIDE))
            {
                return "e1g1";
            }

            if (move == king_side_black && board.castlingRights().has(chess::Color::BLACK,
                                                                      chess::Board::CastlingRights::Side::KING_SIDE))
            {
                return "e8g8";
            }

            if (move == queen_side_white && board.castlingRights().has(chess::Color::WHITE,
                                                                       chess::Board::CastlingRights::Side::QUEEN_SIDE))
            {
                return "e1c1";
            }

            if (move == queen_side_black && board.castlingRights().has(chess::Color::BLACK,
                                                                       chess::Board::CastlingRights::Side::QUEEN_SIDE))
            {
                return "e8c8";
            }


            const uint16_t to_file = move & last_3_bits; // we want 0, 1, and 2
            const uint16_t to_rank = move >> 3 & last_3_bits; // 3, 4, and 5
            const uint16_t from_file = move >> 6 & last_3_bits; // 6, 7, 8
            const uint16_t from_rank = move >> 9 & last_3_bits; // 9, 10, 11
            const uint16_t promotion_move = move >> 12 & last_3_bits; // 12, 13, 14
            // the last 2 bits are unused

            return files[from_file] + ranks[from_rank] + files[to_file] + ranks[to_rank] + promotions[promotion_move];
        }
    };
}
