#ifndef READER_HPP
// Created by Shreyas Deo, find license here https://github.com/deoshreyas/Chess-Polyglot-Reader
// LoadArray added by Mihin Benaragama
#define READER_HPP

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <random>
#include <algorithm>
#include <cstring> // For memcpy

namespace Reader {
    class underlying {
    public:
        uint16_t endian_swap_u16(uint16_t x) {
            return (x>>8) | (x<<8);
        }

        uint32_t endian_swap_u32(uint32_t x) {
            return (x>>24) | 
            ((x<<8) & 0x00FF0000) | 
            ((x>>8) & 0x0000FF00) | 
            (x<<24);
        }

        uint64_t endian_swap_u64(uint64_t x) {
            return (x>>56) | 
            ((x<<40) & 0x00FF000000000000) | 
            ((x<<24) & 0x0000FF0000000000) | 
            ((x<<8)  & 0x000000FF00000000) | 
            ((x>>8)  & 0x00000000FF000000) | 
            ((x>>24) & 0x0000000000FF0000) | 
            ((x>>40) & 0x000000000000FF00) | 
            (x<<56);
        }
    };
}

namespace Reader {
    struct EntryStruct {
        uint64_t key;
        uint16_t move;
        uint16_t weight;
        uint32_t learn;
    };

    static long int num_entries = 0;

    static EntryStruct* entries;

    struct BookMove {
        uint8_t toFile = 0;
        uint8_t toRow = 0;
        uint8_t fromFile = 0;
        uint8_t fromRow = 0;
        uint8_t promotion = 0;
    };

    typedef std::vector<BookMove> BookMoves;

    static std::string Files[8] = {"a", "b", "c", "d", "e", "f", "g", "h"};
    static std::string Rows[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};

    // @brief Convert book move to UCI Format
    // @param move Book move
    // @return UCI move string
    static std::string ConvertBookMoveToUci(BookMove move) {
        std::string move_string = "";
        move_string += Files[move.fromFile];
        move_string += Rows[move.fromRow];
        move_string += Files[move.toFile];
        move_string += Rows[move.toRow];
        if (move.promotion!=0) {
            move_string += "nbrq"[move.promotion-1];
        }
        return move_string;
    }

    // @brief Get random book move from book moves
    // @param book_moves Vector with book moves
    // @return Random book move
    static BookMove RandomBookMove(BookMoves book_moves) {
        std::vector<BookMove> move;
        size_t nelems = 1;
        std::sample(
            book_moves.begin(),
            book_moves.end(),
            std::back_inserter(move),
            nelems,
            std::mt19937{std::random_device{}()}
        );
        return move[0];
    }

    struct BookEntry {
        BookMove move;
        uint16_t weight;
        uint32_t learn;
    };

    typedef std::vector<BookEntry> BookEntries;
}

namespace Reader {
    class Book {
    public:
        // @brief Load book from file
        // @param path Path to book file
        void Load(const char *path) {
            FILE *file = std::fopen(path, "rb");

            if (file==NULL) {
                throw std::runtime_error("Book not found at given path");
                return;
            } else {
                std::fseek(file, 0, SEEK_END);
                long position = std::ftell(file);

                if (position < sizeof(EntryStruct)) {
                    std::cerr << "<Error> No entries found" << std::endl;
                    std::fclose(file);
                    return;
                }

                num_entries = position / sizeof(EntryStruct);

                entries = (EntryStruct*)std::malloc(num_entries * sizeof(EntryStruct));
                if (!entries) {
                    std::fclose(file);
                    throw std::runtime_error("Memory allocation failed");
                }

                std::rewind(file);
                size_t returnValue = std::fread(entries, sizeof(EntryStruct), num_entries, file);

                std::fclose(file);
            }
        }

        // @brief Load book from a byte array in memory
        // @param data Pointer to byte array containing book data
        // @param size Size of the byte array in bytes
        void LoadArray(const uint8_t* data, size_t size) {
            if (size < sizeof(EntryStruct)) {
                throw std::runtime_error("No entries found in data");
                return;
            }

            if (size % sizeof(EntryStruct) != 0) {
                throw std::runtime_error("Invalid data size, not multiple of EntryStruct size");
                return;
            }

            num_entries = size / sizeof(EntryStruct);

            entries = (EntryStruct*) std::malloc(num_entries * sizeof(EntryStruct));
            if (!entries) {
                throw std::runtime_error("Memory allocation failed");
            }

            std::memcpy(entries, data, size);
        }

        // @brief Get move from book
        // @param key Zobrist key
        // @param minimum_weight Minimum weight of book moves to be returned (default 0)
        // @return Vector with the book moves (toFile, toRow, fromFile, fromRow, promotion, weight)
        BookMoves GetBookMoves(uint64_t key, uint16_t minimum_weight=0) {
            EntryStruct *entry;
            uint16_t move;
            BookMove book_move;
            underlying u;
            BookMoves bookMoves;
            for (entry=entries; entry<entries+num_entries; entry++) {
                if (u.endian_swap_u64(entry->key) == key && u.endian_swap_u16(entry->weight) >= minimum_weight) {
                    move = u.endian_swap_u16(entry->move);
                    book_move.fromFile = ((move>>6) & 7);
                    book_move.fromRow = ((move>>9) & 7);    
                    book_move.toFile = ((move>>0) & 7);
                    book_move.toRow = ((move>>3) & 7);  
                    book_move.promotion = ((move>>12) & 7); 
                    bookMoves.push_back(book_move);
                }
            }
            return bookMoves;
        }

        // @brief Search book for key. Unlike GetBookMoves(), which only returns the book moves, SearchBook()
        // also returns the weight and learn value of the book moves. 
        // @param key Zobrist key
        // @param minimum_weight Minimum weight of book moves to be returned (default 0)
        // @return Vector with the book entries (move, weight, learn)
        BookEntries SearchBook(uint64_t key, uint16_t minimum_weight=0) {
            EntryStruct *entry;
            uint16_t move;
            BookMove book_move;
            underlying u;
            BookEntry book_entry;
            BookEntries bookEntries;
            for (entry=entries; entry<entries+num_entries; entry++) {
                if (u.endian_swap_u64(entry->key) == key && u.endian_swap_u16(entry->weight) >= minimum_weight) {
                    move = u.endian_swap_u16(entry->move);
                    book_move.fromFile = ((move>>6) & 7);
                    book_move.fromRow = ((move>>9) & 7);    
                    book_move.toFile = ((move>>0) & 7);
                    book_move.toRow = ((move>>3) & 7);  
                    book_move.promotion = ((move>>12) & 7); 
                    book_entry.move = book_move;
                    book_entry.weight = u.endian_swap_u16(entry->weight);
                    book_entry.learn = u.endian_swap_u32(entry->learn);
                    bookEntries.push_back(book_entry);
                }
            }
            return bookEntries;
        }  
        
        // @brief Clear book from memory
        void Clear() {
            if (entries) {
                std::free(entries);
                entries = nullptr;
                num_entries = 0;
            }
        } 
    };
}

#endif
