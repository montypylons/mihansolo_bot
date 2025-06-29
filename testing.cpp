#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "chess.hpp"

// Don't include engine.cpp — just reference its globals and functions.
extern chess::Board board;

void init_book();
int evaluate(int ply = 0);
std::string search(const std::string&);

// Evaluation test
void test_eval() {
    std::vector<std::pair<std::string, int>> tests = {
        {"8/8/8/8/8/8/8/8 w - - 0 1", 0},
        {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", 0},
        {"rnbqkbnr/pppppppp/8/8/4Q3/8/PPPPPPPP/RNB1KBNR b KQkq - 0 1", 900},
    };

    for (auto& [fen, expected] : tests) {
        board.setFen(fen);
        int eval = evaluate();
        std::cout << "FEN: " << fen << "\nEval: " << eval << " (Expected ~" << expected << ")\n\n";
    }
}

// Movegen sanity
void test_moves() {
    board.setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    chess::Movelist moves;
    chess::movegen::legalmoves(moves, board);
    std::cout << "Moves from start: " << moves.size() << "\n";
    assert(!moves.empty());
}

// Search logic
void test_search() {
    std::vector<std::string> fens = {
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "6k1/5ppp/8/8/8/8/5PPP/6KQ w - - 0 1", // mate in 1
        "7k/5K2/6Q1/8/8/8/8/8 b - - 0 1"      // stalemate
    };

    for (std::string fen : fens) {
        board.setFen(fen);
        std::string best = search("0");
        std::cout << "FEN: " << fen << "\nBest move: " << best << "\n\n";
    }
}

int main() {
    init_book();
    std::cout << "\n[TEST] Eval\n";       test_eval();
    std::cout << "\n[TEST] Movegen\n";    test_moves();
    std::cout << "\n[TEST] Search\n";     test_search();
    return 0;
}
