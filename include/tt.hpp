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
};

class TranspositionTable
{
public:
    TranspositionTable() = default;

    void put(uint64_t zobrist_key,
             const chess::Move& best_move,
             int depth,
             int score,
             NodeType node_type);


    [[nodiscard]] std::optional<TTEntry> get(uint64_t zobrist_key) const;
    [[nodiscard]] bool find(uint64_t zobrist_key) const;

private:
    [[nodiscard]] int address_calc(uint64_t key) const;

    std::vector<TTEntry> table = std::vector<TTEntry>(1'000'000); // TODO: add tests for this stuff
    // im so behind on tests
    // if this stuff keeps failing i will ...
};
