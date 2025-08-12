#include <cstdint>
#include "chess.hpp"
#include "tt.hpp"


struct TTEntry; // TODO: get tests for TT


void TranspositionTable::put(const uint64_t zobrist_key,
                             const chess::Move& best_move,
                             const int depth,
                             const int score,
                             const NodeType node_type)
{
    if (const int index = address_calc(zobrist_key); !find(zobrist_key) || depth >= table[index].depth)
    {
        table[index] = TTEntry{zobrist_key, best_move, depth, score, node_type};
    }
    else
    {
        // Do nothing, leave the existing entry as it is
    }
}

[[nodiscard]] std::optional<TTEntry> TranspositionTable::get(const uint64_t zobrist_key) const
{
    if (auto found_entry = table[address_calc(zobrist_key)]; found_entry.zobrist_key == zobrist_key)
    {
        return found_entry;
    }
    return std::nullopt;
}


[[nodiscard]] bool TranspositionTable::find(const uint64_t zobrist_key) const
{
    return table[address_calc(zobrist_key)].zobrist_key == zobrist_key;
}

[[nodiscard]] int TranspositionTable::address_calc(const uint64_t key)
{
    return key & 8'388'607;
}
