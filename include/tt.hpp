#pragma once

enum class NodeType: uint8_t
{
    EXACT,
    UPPERBOUND,
    LOWERBOUND
};

struct TTEntry // TODO: get tests for TT
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
public:
    TranspositionTable() = default;

    void put(uint64_t zobrist_key,
             const chess::Move& best_move,
             int depth,
             int score,
             NodeType node_type,
             int age);


    [[nodiscard]] std::optional<TTEntry> get(uint64_t zobrist_key) const;

private:
    [[nodiscard]] bool find(uint64_t zobrist_key) const;

    [[nodiscard]] int address_calc(uint64_t key) const;

    std::array<TTEntry, 1000000> table;
};
