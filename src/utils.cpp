#include "chess.hpp"
#include "utils.hpp"
#include <vector>
#include <array>

/**
 * Contains various helper functions
 */
namespace utils
{
    /**
     *
     * @param board The board to generate bitboards for
     * @return This is very convoluted ... but it returns a tuple of two arrays (one for us, one for the enemy)
     * which contain 6 bitboards each, one for each piece type
     */
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

    /**
     *
     * @param board Current board state
     * @param move Move to be evaluated in the context of board
     * @return The MVV-LAA (Most Valuable Victim - Least Valuble Aggressor)
     * value for that move, used as a key for ordering capture moves. For example,
     * it would reward PxQ over QxQ or QxP since you would lose less material to a
     * recapture then.
     */
    int MVV_LAA_helper(const chess::Board& board, const chess::Move& move)
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

    /**
     *
     * @param history The history heuristic array, indexed by [color (2)][from_square (64)][to_square (64)]
     * @param PV_Move Current principal variation move, to be placed first in the sorted list
     * @param moves The list of moves to sort
     * @param board The board BEFORE any of the aforementioned moved are made on it
     */
    void order_moves(const int (&history)[2][64][64], const chess::Move& PV_Move, chess::Movelist& moves,
                     const chess::Board& board)
    {
        std::sort(moves.begin(), moves.end(), [board, &history](const chess::Move& m1, const chess::Move& m2)-> bool
        {
            const bool m1_capture = board.isCapture(m1);
            const bool m2_capture = board.isCapture(m2);

            if (m1_capture && !m2_capture)
            {
                return true;
            }
            if (!m1_capture && m2_capture)
            {
                return false;
            }
            if (m1_capture && m2_capture)
            {
                return MVV_LAA_helper(board, m1) > MVV_LAA_helper(board, m2);
            }
            return history_heuristic_helper(history, board, m1) < history_heuristic_helper(history, board, m2);
        });

        if (const auto PV_pos = moves.find(PV_Move); PV_pos > 0) // NOLINT
        {
            std::swap(moves[0], moves[PV_pos]);
        }
    }

    /**
     *
     * @param moves A list of capture moves to be sorted
     * @param board The board BEFORE any of the aforementioned moves are made
     */
    void order_capture_moves(chess::Movelist& moves, const chess::Board& board)
    {
        std::sort(moves.begin(), moves.end(), [board](const chess::Move& m1, const chess::Move& m2)-> bool
        {
            return MVV_LAA_helper(board, m1) > MVV_LAA_helper(board, m2);
        });
    }
}
