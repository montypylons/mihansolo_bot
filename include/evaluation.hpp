#pragma once

#include "chess.hpp"
#include "utils.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

namespace evaluation
{

    int material_eval(chess::Board board);

    int piece_square_eval(chess::Board board);

    int game_over_eval(chess::Board board, int ply = 0);

    int main_eval(chess::Board board);
}