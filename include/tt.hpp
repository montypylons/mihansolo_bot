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

struct TTEntry_eval
{
    uint64_t zobrist_key;
    int score;
};

int scoreFromTT(int score, int ply);
int scoreToTT(int score, int ply);


class TranspositionTable
{
public:
    TranspositionTable() = default;

    void put(uint64_t zobrist_key,
             const chess::Move& best_move,
             int depth,
             int score,
             NodeType node_type, int ply);

    [[nodiscard]] std::optional<std::tuple<int, chess::Move>> find_usable_entry(
        const int original_alpha,
        const int beta, const int depth,
        const uint64_t zobrist_key, const int ply)
    {
        if (auto ttEntry = get(zobrist_key, ply); ttEntry.has_value() && ttEntry->depth >= depth)
        {
            if (ttEntry->node_type == NodeType::EXACT || (ttEntry->node_type == NodeType::LOWERBOUND && ttEntry->score
                >= beta) || (ttEntry->node_type == NodeType::UPPERBOUND && ttEntry->score <= original_alpha))
            {
                return std::make_tuple(ttEntry->score, ttEntry->best_move);
            }
        }
        return std::nullopt;
    }

    [[nodiscard]] std::optional<TTEntry> get(uint64_t zobrist_key, int ply) const;
    [[nodiscard]] bool find(uint64_t zobrist_key) const;

private:
    static int address_calc(uint64_t key);

    std::vector<TTEntry> table = std::vector<TTEntry>(8'388'608);
};

class EvaluationHashTable
{
public:
    EvaluationHashTable() = default;

    void put(uint64_t zobrist_key, int score);

    [[nodiscard]] std::optional<TTEntry_eval> get(uint64_t zobrist_key) const;
    [[nodiscard]] bool find(uint64_t zobrist_key) const;

private:
    static int address_calc(uint64_t key);
    std::vector<TTEntry_eval> table = std::vector<TTEntry_eval>(8'388'608);
};
