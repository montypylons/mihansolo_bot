#include "chess.hpp"
#include "utils.hpp"
#include <vector>
namespace utils
{

    int piece_square[7][64] = {
        // piece_square[piece][square] (piece -> 0,1,2,3,4)

        {
            0, 0, 0, 0, 0, 0, 0, 0,         // rank 1 (a1-h1)
            5, 10, 10, -20, -20, 10, 10, 5, // rank 2 (a2-h2) - the -20 row
            5, -5, -10, 0, 0, -10, -5, 5,   // rank 3 (a3-h3)
            0, 0, 0, 20, 20, 0, 0, 0,       // rank 4 (a4-h4)
            5, 5, 10, 25, 25, 10, 5, 5,     // rank 5 (a5-h5)
            10, 10, 20, 30, 30, 20, 10, 10, // rank 6 (a6-h6)
            50, 50, 50, 50, 50, 50, 50, 50, // rank 7 (a7-h7)
            0, 0, 0, 0, 0, 0, 0, 0          // rank 8 (a8-h8)
        },

        {-50, -40, -30, -30, -30, -30, -40, -50, // knight
         -40, -20, 0, 0, 0, 0, -20, -40,
         -30, 0, 10, 15, 15, 10, 0, -30,
         -30, 5, 15, 20, 20, 15, 5, -30,
         -30, 0, 15, 20, 20, 15, 0, -30,
         -30, 5, 10, 15, 15, 10, 5, -30,
         -40, -20, 0, 5, 5, 0, -20, -40,
         -50, -40, -30, -30, -30, -30, -40, -50},

        {
            -20, -10, -10, -10, -10, -10, -10, -20, // bishop rank 1 (a1-h1)
            -10, 5, 0, 0, 0, 0, 5, -10,             // bishop rank 2 (a2-h2)
            -10, 10, 10, 10, 10, 10, 10, -10,       // bishop rank 3 (a3-h3)
            -10, 0, 10, 10, 10, 10, 0, -10,         // bishop rank 4 (a4-h4)
            -10, 5, 5, 10, 10, 5, 5, -10,           // bishop rank 5 (a5-h5)
            -10, 0, 5, 10, 10, 5, 0, -10,           // bishop rank 6 (a6-h6)
            -10, 0, 0, 0, 0, 0, 0, -10,             // bishop rank 7 (a7-h7)
            -20, -10, -10, -10, -10, -10, -10, -20  // bishop rank 8 (a8-h8)
        },
        {
            0, 0, 0, 5, 5, 0, 0, 0,       // rook rank 1 (a1-h1)
            -5, 0, 0, 0, 0, 0, 0, -5,     // rook rank 2 (a2-h2)
            -5, 0, 0, 0, 0, 0, 0, -5,     // rook rank 3 (a3-h3)
            -5, 0, 0, 0, 0, 0, 0, -5,     // rook rank 4 (a4-h4)
            -5, 0, 0, 0, 0, 0, 0, -5,     // rook rank 5 (a5-h5)
            -5, 0, 0, 0, 0, 0, 0, -5,     // rook rank 6 (a6-h6)
            5, 10, 10, 10, 10, 10, 10, 5, // rook rank 7 (a7-h7)
            0, 0, 0, 0, 0, 0, 0, 0        // rook rank 8 (a8-h8)
        },

        {
            -20, -10, -10, -5, -5, -10, -10, -20, // queen rank 1 (a1-h1)
            -10, 0, 5, 0, 0, 0, 0, -10,           // queen rank 2 (a2-h2)
            -10, 5, 5, 5, 5, 5, 0, -10,           // queen rank 3 (a3-h3)
            0, 0, 5, 5, 5, 5, 0, -5,              // queen rank 4 (a4-h4)
            -5, 0, 5, 5, 5, 5, 0, -5,             // queen rank 5 (a5-h5)
            -10, 0, 5, 5, 5, 5, 0, -10,           // queen rank 6 (a6-h6)
            -10, 0, 0, 0, 0, 0, 0, -10,           // queen rank 7 (a7-h7)
            -20, -10, -10, -5, -5, -10, -10, -20  // queen rank 8 (a8-h8)
        },
        {
            20, 30, 10, 0, 0, 10, 30, 20,           // king middle game rank 1 (a1-h1)
            20, 20, 0, 0, 0, 0, 20, 20,             // king middle game rank 2 (a2-h2)
            -10, -20, -20, -20, -20, -20, -20, -10, // king middle game rank 3 (a3-h3)
            -20, -30, -30, -40, -40, -30, -30, -20, // king middle game rank 4 (a4-h4)
            -30, -40, -40, -50, -50, -40, -40, -30, // king middle game rank 5 (a5-h5)
            -30, -40, -40, -50, -50, -40, -40, -30, // king middle game rank 6 (a6-h6)
            -30, -40, -40, -50, -50, -40, -40, -30, // king middle game rank 7 (a7-h7)
            -30, -40, -40, -50, -50, -40, -40, -30  // king middle game rank 8 (a8-h8)
        },
        {
            -50, -30, -30, -30, -30, -30, -30, -50, // king end game rank 1 (a1-h1)
            -30, -30, 0, 0, 0, 0, -30, -30,         // king end game rank 2 (a2-h2)
            -30, -10, 20, 30, 30, 20, -10, -30,     // king end game rank 3 (a3-h3)
            -30, -10, 30, 40, 40, 30, -10, -30,     // king end game rank 4 (a4-h4)
            -30, -10, 30, 40, 40, 30, -10, -30,     // king end game rank 5 (a5-h5)
            -30, -10, 20, 30, 30, 20, -10, -30,     // king end game rank 6 (a6-h6)
            -30, -20, -10, 0, 0, -10, -20, -30,     // king end game rank 7 (a7-h7)
            -50, -40, -30, -20, -20, -30, -40, -50  // king end game rank 8 (a8-h8)
        },
    };

    // should all return from POV of side to move & int

    std::tuple<std::vector<chess::Bitboard>, std::vector<chess::Bitboard>> generate_bitboards(const chess::Board& board) // move functions like this to utils.cpp later
    {
        const chess::Color side_to_move = board.sideToMove();

        const chess::Bitboard pawns = board.pieces(chess::PieceType::PAWN, side_to_move);
        const chess::Bitboard knights = board.pieces(chess::PieceType::KNIGHT, side_to_move);
        const chess::Bitboard bishops = board.pieces(chess::PieceType::BISHOP, side_to_move);
        const chess::Bitboard rooks = board.pieces(chess::PieceType::ROOK, side_to_move);
        const chess::Bitboard queens = board.pieces(chess::PieceType::QUEEN, side_to_move);

        const chess::Bitboard enemy_pawns = board.pieces(chess::PieceType::PAWN, !side_to_move);
        const chess::Bitboard enemy_knights = board.pieces(chess::PieceType::KNIGHT, !side_to_move);
        const chess::Bitboard enemy_bishops = board.pieces(chess::PieceType::BISHOP, !side_to_move);
        const chess::Bitboard enemy_rooks = board.pieces(chess::PieceType::ROOK, !side_to_move);
        const chess::Bitboard enemy_queens = board.pieces(chess::PieceType::QUEEN, !side_to_move);

        return std::make_tuple(
            std::vector{pawns, knights, bishops, rooks, queens},
            std::vector{enemy_pawns, enemy_knights, enemy_bishops, enemy_rooks, enemy_queens});
    }
}