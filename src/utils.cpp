#include "chess.hpp"
#include "utils.hpp"
#include <vector>
#include <array>

namespace utils
{
    // should all return from POV of side to move & int

    std::tuple<std::array<chess::Bitboard, 6>, std::array<chess::Bitboard, 6>> generate_bitboards(
        const chess::Board& board)
    {
        const chess::Color side_to_move = board.sideToMove();

        const chess::Bitboard pawns = board.pieces(chess::PieceType::PAWN, side_to_move);
        const chess::Bitboard knights = board.pieces(chess::PieceType::KNIGHT, side_to_move);
        const chess::Bitboard bishops = board.pieces(chess::PieceType::BISHOP, side_to_move);
        const chess::Bitboard rooks = board.pieces(chess::PieceType::ROOK, side_to_move);
        const chess::Bitboard queens = board.pieces(chess::PieceType::QUEEN, side_to_move);
        const chess::Bitboard kings = board.pieces(chess::PieceType::KING, side_to_move);

        const chess::Bitboard enemy_pawns = board.pieces(chess::PieceType::PAWN, !side_to_move);
        const chess::Bitboard enemy_knights = board.pieces(chess::PieceType::KNIGHT, !side_to_move);
        const chess::Bitboard enemy_bishops = board.pieces(chess::PieceType::BISHOP, !side_to_move);
        const chess::Bitboard enemy_rooks = board.pieces(chess::PieceType::ROOK, !side_to_move);
        const chess::Bitboard enemy_queens = board.pieces(chess::PieceType::QUEEN, !side_to_move);
        const chess::Bitboard enemy_kings = board.pieces(chess::PieceType::KING, !side_to_move);

        return std::make_tuple(
            std::array<chess::Bitboard, 6>{pawns, knights, bishops, rooks, queens, kings},
            std::array<chess::Bitboard, 6>{
                enemy_pawns, enemy_knights, enemy_bishops, enemy_rooks, enemy_queens, enemy_kings
            });
    }

    int MVV_LAA_helper(const chess::Board& board, const chess::Move& move)
    // Most Valuable Victim - Least Valuable Aggressor

    {
        // TODO: Add tests

        const int from_score = piece_values[board.at(move.from()).type()];
        const int to_score = piece_values[board.at(move.to()).type()];
        const int move_score = to_score - from_score;
        return move_score;
    }

    inline int history_heuristic_helper(const int (&history)[2][64][64], const chess::Board& board,
                                        const chess::Move& move)
    {
        return history[board.sideToMove()][move.from().index()][move.to().index()];
    }

    chess::Movelist order_moves(const int (&history)[2][64][64], const chess::Move& PV_Move, chess::Movelist& moves,
                                const chess::Board& board)
    {
        std::sort(moves.begin(), moves.end(), [board, &history](const chess::Move& m1, const chess::Move& m2)-> bool
        {
            if (board.isCapture(m1)) // do not use move ordering this for castling or en-passant
            {
                return MVV_LAA_helper(board, m1) > MVV_LAA_helper(board, m2);
            }
            return history_heuristic_helper(history, board, m1) < history_heuristic_helper(history, board, m2);
        });

        if (const auto PV_pos = moves.find(PV_Move); PV_pos > 0) // NOLINT
        {
            std::swap(moves[0], moves[PV_pos]);
        }

        return moves;
    }
}
