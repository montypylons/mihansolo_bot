#include <cstdint>
#include "chess.hpp"
#include "tt.hpp"


struct TTEntry; // TODO: get tests for TT

constexpr int MATE_EVAL = 10'000;
constexpr int MAX_PLY = 512;
constexpr int MATE_THRESHOLD = MATE_EVAL - MAX_PLY;

int scoreFromTT(const int score, const int ply)
{
    if (score >= MATE_THRESHOLD) return score - ply;
    if (score <= -MATE_THRESHOLD) return score + ply;
    return score;
}

int scoreToTT(const int score, const int ply)
{
    if (score >= MATE_THRESHOLD) return score + ply;
    if (score <= -MATE_THRESHOLD) return score - ply;
    return score;
}


/**
 *
 * @param zobrist_key Zobrist hash of current board
 * @param best_move Believed best move for the current board
 * @param depth Current search depth
 * @param score Believed score of current board (from the side-to-move's POV)
 * @param node_type What type of node this is - NodeType::LOWERBOUND, NodeType::UPPERBOUND, or NodeType::EXACT
 * @param ply
 */
void TranspositionTable::put(const uint64_t zobrist_key,
                             const chess::Move& best_move,
                             const int depth,
                             const int score,
                             const NodeType node_type, const int ply)
{
    if (const int index = address_calc(zobrist_key); !find(zobrist_key) || depth >= table[index].depth)
    {
        std::cout << "Putting TTEntry at index " << index;
        std::cout << "Best move: " << chess::uci::moveToUci(best_move) <<std::endl;
        std::cout << "Score: " << score << std::endl;
        std::cout << "Zobrist key: " << zobrist_key << std::endl;
        table[index] = TTEntry{zobrist_key, best_move, depth, scoreToTT(score, ply), node_type};
    }
}

[[nodiscard]] std::optional<TTEntry> TranspositionTable::get(const uint64_t zobrist_key, const int ply) const
{
    if (auto found_entry = table[address_calc(zobrist_key)]; found_entry.zobrist_key == zobrist_key)
    {
        found_entry.score = scoreFromTT(found_entry.score, ply);
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
    return key & 8'388'607; // NOLINT
}

void EvaluationHashTable::put(const uint64_t zobrist_key,
                              const int score)
{
    table[address_calc(zobrist_key)] = TTEntry_eval{zobrist_key, score};
}

[[nodiscard]] std::optional<TTEntry_eval> EvaluationHashTable::get(const uint64_t zobrist_key) const
{
    if (auto found_entry = table[address_calc(zobrist_key)]; found_entry.zobrist_key == zobrist_key)
    {
        return found_entry;
    }
    return std::nullopt;
}


[[nodiscard]] bool EvaluationHashTable::find(const uint64_t zobrist_key) const
{
    return table[address_calc(zobrist_key)].zobrist_key == zobrist_key;
}

[[nodiscard]] int EvaluationHashTable::address_calc(const uint64_t key)
{
    return key & 8'388'607; // NOLINT
}
