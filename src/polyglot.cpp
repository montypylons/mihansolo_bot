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

// By Mihin Benaragama (@montypylons on GitHub)
// Thanks to http://hgm.nubati.net/book_format.html for explaining the PolyGlot book format

// TODO: lazy endian swapping

namespace polyglot
{
    void Reader::swap_endians(std::vector<Entry>& entries)
    {
        for (auto& [key, move, weight, learn] : entries)
        {
            key = std::byteswap(key);
            move = std::byteswap(move);
            weight = std::byteswap(weight);
            learn = std::byteswap(learn);
        }
    }

    void Reader::LoadFromFile(const char* filename)
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

    void Reader::LoadFromArray(const unsigned char arr[], const unsigned int arr_len)
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

    uint16_t Reader::GetBookMove(const SelectionMethod method, const uint64_t zobrist_key)
    {
        std::vector<Entry> matching_entries;

        const auto lower_range = std::lower_bound(book.begin(), book.end(), zobrist_key,
                                                  [](const Entry& entry, const uint64_t key)
                                                  {
                                                      return entry.key < key;
                                                  });

        const auto upper_range = std::upper_bound(book.begin(), book.end(), zobrist_key,
                                                  [](const uint64_t key, const Entry& entry)
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

    std::string Reader::RawMoveToUci(const uint16_t move, const chess::Board& board)
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
}
