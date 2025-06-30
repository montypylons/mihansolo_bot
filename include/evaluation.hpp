#include "chess.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>


using namespace chess;

int material_eval(Board board);

int piece_square_eval(Board board);

int game_over_eval(Board board, int ply = 0);

int main_eval(Board board);