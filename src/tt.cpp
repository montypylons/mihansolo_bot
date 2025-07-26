#include <cstdint>
#include "chess.hpp"
#include "tt.hpp"

enum class NodeType: uint8_t
{
    EXACT,
    UPPERBOUND,
    LOWERBOUND
};

struct TTEntry // TODO: implement transposition table
{
    uint64_t zobrist_key;
    chess::Move best_move;
    int depth;
    int score;
    NodeType node_type;
    int age;
};

class TranspositionTable
{
    int address_calc(uint64_t key);

};
