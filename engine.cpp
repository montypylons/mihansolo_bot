#include "chess.hpp"
#include <tuple>
#include <string>

using namespace chess;

std::tuple<int, std::string, bool> evaluate(chess::Board board) {
    chess::Position chess_position = chess::Position();
    std::string name = "Alice";
    bool active = true;
    return std::make_tuple(id, name, active);
}

