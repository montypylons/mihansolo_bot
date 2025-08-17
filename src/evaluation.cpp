#include "chess.hpp"
#include "utils.hpp"
#include "evaluation.hpp"
#include "engine.hpp"
#include <array>


namespace evaluation
{
    EvaluationHashTable hash_table;

    std::tuple<std::array<chess::Bitboard, 6>, std::array<chess::Bitboard, 6>> initialize_bitboards(
        const chess::Board& board)
    {
        // Gets bitboards for each piece from the chess::Board
        // pawns, knights, bishops, rooks, queens, then same but black_pawns, etc.
        auto generated_bitboards = utils::generate_bitboards(board);
        return generated_bitboards;
    }

    bool is_endgame(const chess::Board& board)
    {
        return board.pieces(chess::PieceType::KNIGHT).count()
            + board.pieces(chess::PieceType::BISHOP).count()
            + board.pieces(chess::PieceType::ROOK).count() < 8
            && board.pieces(chess::PieceType::QUEEN).count() == 0;
    }

    int material_eval(const chess::Bitboard& pawns, const chess::Bitboard& knights,
                      const chess::Bitboard& bishops, const chess::Bitboard& rooks, const chess::Bitboard& queens,
                      const chess::Bitboard& black_pawns, const chess::Bitboard& black_knights,
                      const chess::Bitboard& black_bishops,
                      const chess::Bitboard& black_rooks, const chess::Bitboard& black_queens)
    {
        // initialize score
        int material_score = 0;

        // basic material counting
        const int p_count = pawns.count();
        const int n_count = knights.count();
        const int b_count = bishops.count();
        const int r_count = rooks.count();
        const int q_count = queens.count();

        const int p_count_black = black_pawns.count();
        const int n_count_black = black_knights.count();
        const int b_count_black = black_bishops.count();
        const int r_count_black = black_rooks.count();
        const int q_count_black = black_queens.count();
        // add to score
        material_score += p_count * 100 * 1;
        material_score += n_count * 300 * 1;
        material_score += b_count * 300 * 1;
        material_score += r_count * 500 * 1;
        material_score += q_count * 900 * 1;

        // subtract opposite side's piece values
        material_score -= p_count_black * 100;
        material_score -= n_count_black * 300;
        material_score -= b_count_black * 300;
        material_score -= r_count_black * 500;
        material_score -= q_count_black * 900;

        // give material imbalance FROM POV of side to move
        return material_score;
    }

    int king_psqt_eval(const chess::Board& board, const std::array<chess::Bitboard, 6>& pieces,
                       const std::array<chess::Bitboard, 6>& enemy_pieces)
    {
        int positional_score = 0;
        auto kings_bitboard = pieces[5];
        int kings_square = kings_bitboard.pop();
        kings_square = board.at(chess::Square(kings_square)).color() == chess::Color::WHITE
                           ? kings_square
                           : kings_square ^ 56;

        if (is_endgame(board))
        {
            positional_score += utils::piece_square[6][kings_square];
        }
        else
        {
            positional_score += utils::piece_square[5][kings_square];
        }

        auto enemy_kings_bitboard = enemy_pieces[5];
        int enemy_kings_square = enemy_kings_bitboard.pop();
        enemy_kings_square = board.at(chess::Square(enemy_kings_square)).color() == chess::Color::WHITE
                                 ? enemy_kings_square
                                 : enemy_kings_square ^ 56;


        if (is_endgame(board))
        {
            positional_score -= utils::piece_square[6][enemy_kings_square];
        }
        else
        {
            positional_score -= utils::piece_square[5][enemy_kings_square];
        }
        return positional_score;
    }


    int piece_square_eval(const chess::Board& board, const std::array<chess::Bitboard, 6>& pieces,
                          const std::array<chess::Bitboard, 6>& enemy_pieces)
    {
        // initialize variables
        int positional_score = 0;
        // our pieces
        for (size_t i = 0; i + 1 < pieces.size(); i++)
        {
            auto bitboard = pieces[i];
            while (bitboard)
            {
                int square = bitboard.pop();

                auto piece = board.at(chess::Square(square));

                const int piece_index = piece.type();

                square = piece.color() == chess::Color::WHITE ? square : square ^ 56;

                const int psqt_value = utils::piece_square[piece_index][square];

                positional_score += psqt_value;
            }
        }
        // enemy pieces
        for (size_t i = 0; i + 1 < enemy_pieces.size(); i++)
        {
            auto bitboard = enemy_pieces[i];
            while (bitboard)
            {
                int square = bitboard.pop();

                auto piece = board.at(chess::Square(square));

                const int piece_index = piece.type();

                square = board.at(chess::Square(square)).color() == chess::Color::WHITE ? square : square ^ 56;

                const int psqt_value = utils::piece_square[piece_index][square];

                positional_score -= psqt_value;
            }
        }
        positional_score = positional_score + king_psqt_eval(board, pieces, enemy_pieces);


        return positional_score;
    }

    std::optional<int> game_over_eval(const chess::Board& board, const int& ply)
    {
        if (board.isInsufficientMaterial() || board.isHalfMoveDraw() || board.isRepetition())
        {
            return 0;
        }

        chess::Movelist moves;
        chess::movegen::legalmoves(moves, board);

        if (moves.empty())
        {
            if (const bool check = board.inCheck();
                check)
            {
                return -10000 + ply;
            }
            return 0;
        }

        return std::nullopt;
    }


    int mobility_eval(const chess::Board& board)
    {
        int mobility_eval = 0;

        const chess::Color side_to_move = board.sideToMove();
        chess::Movelist moves_for_piece;

        if (side_to_move)
        {
            chess::movegen::legalmoves(
                moves_for_piece, board, chess::PieceGenType::BISHOP);
            mobility_eval += moves_for_piece.size() * utils::BISHOP_MOBILITY_FACTOR;
            moves_for_piece.clear();

            chess::movegen::legalmoves(
                moves_for_piece, board, chess::PieceGenType::KNIGHT);
            mobility_eval += moves_for_piece.size() * utils::KNIGHT_MOBILITY_FACTOR;
            moves_for_piece.clear();

            chess::movegen::legalmoves(
                moves_for_piece, board, chess::PieceGenType::ROOK);
            mobility_eval += moves_for_piece.size() * utils::ROOK_MOBILITY_FACTOR;
            moves_for_piece.clear();

            chess::movegen::legalmoves(
                moves_for_piece, board, chess::PieceGenType::QUEEN);
            mobility_eval += moves_for_piece.size() * utils::QUEEN_MOBILITY_FACTOR;
            moves_for_piece.clear();


            chess::movegen::legalmoves<chess::Color::BLACK, chess::movegen::MoveGenType::ALL>(
                moves_for_piece, board, chess::PieceGenType::BISHOP);
            mobility_eval -= moves_for_piece.size() * utils::BISHOP_MOBILITY_FACTOR;
            moves_for_piece.clear();

            chess::movegen::legalmoves<chess::Color::BLACK, chess::movegen::MoveGenType::ALL>(
                moves_for_piece, board, chess::PieceGenType::KNIGHT);
            mobility_eval -= moves_for_piece.size() * utils::KNIGHT_MOBILITY_FACTOR;
            moves_for_piece.clear();

            chess::movegen::legalmoves<chess::Color::BLACK, chess::movegen::MoveGenType::ALL>(
                moves_for_piece, board, chess::PieceGenType::ROOK);
            mobility_eval -= moves_for_piece.size() * utils::ROOK_MOBILITY_FACTOR;
            moves_for_piece.clear();

            chess::movegen::legalmoves<chess::Color::BLACK, chess::movegen::MoveGenType::ALL>(
                moves_for_piece, board, chess::PieceGenType::QUEEN);
            mobility_eval -= moves_for_piece.size() * utils::QUEEN_MOBILITY_FACTOR;

            return mobility_eval;
        }

        chess::movegen::legalmoves(
            moves_for_piece, board, chess::PieceGenType::BISHOP);
        mobility_eval += moves_for_piece.size() * utils::BISHOP_MOBILITY_FACTOR;
        moves_for_piece.clear();

        chess::movegen::legalmoves(
            moves_for_piece, board, chess::PieceGenType::KNIGHT);
        mobility_eval += moves_for_piece.size() * utils::KNIGHT_MOBILITY_FACTOR;
        moves_for_piece.clear();

        chess::movegen::legalmoves(
            moves_for_piece, board, chess::PieceGenType::ROOK);
        mobility_eval += moves_for_piece.size() * utils::ROOK_MOBILITY_FACTOR;
        moves_for_piece.clear();

        chess::movegen::legalmoves(
            moves_for_piece, board, chess::PieceGenType::QUEEN);
        mobility_eval += moves_for_piece.size() * utils::QUEEN_MOBILITY_FACTOR;
        moves_for_piece.clear();


        chess::movegen::legalmoves<chess::Color::WHITE, chess::movegen::MoveGenType::ALL>(
            moves_for_piece, board, chess::PieceGenType::BISHOP);
        mobility_eval -= moves_for_piece.size() * utils::BISHOP_MOBILITY_FACTOR;
        moves_for_piece.clear();

        chess::movegen::legalmoves<chess::Color::WHITE, chess::movegen::MoveGenType::ALL>(
            moves_for_piece, board, chess::PieceGenType::KNIGHT);
        mobility_eval -= moves_for_piece.size() * utils::KNIGHT_MOBILITY_FACTOR;
        moves_for_piece.clear();

        chess::movegen::legalmoves<chess::Color::WHITE, chess::movegen::MoveGenType::ALL>(
            moves_for_piece, board, chess::PieceGenType::ROOK);
        mobility_eval -= moves_for_piece.size() * utils::ROOK_MOBILITY_FACTOR;
        moves_for_piece.clear();

        chess::movegen::legalmoves<chess::Color::WHITE, chess::movegen::MoveGenType::ALL>(
            moves_for_piece, board, chess::PieceGenType::QUEEN);
        mobility_eval -= moves_for_piece.size() * utils::QUEEN_MOBILITY_FACTOR;

        return mobility_eval;
    }

    int main_eval(const chess::Board& board, const int& ply)
    {
        const auto zobrist = board.hash();
        if (const auto hash_entry = hash_table.get(zobrist); hash_entry.has_value())
        {
            return hash_entry.value().score;
        }

        if (const std::optional<int> result = game_over_eval(board, ply); result != std::nullopt)
        {
            return result.value();
        }

        int score = 0;

        const auto& generated_bitboards = initialize_bitboards(board);

        const auto& our_pieces = std::get<0>(generated_bitboards);
        const auto& enemy_pieces = std::get<1>(generated_bitboards);

        score += material_eval(our_pieces[0], our_pieces[1], our_pieces[2], our_pieces[3], our_pieces[4],
                               enemy_pieces[0], enemy_pieces[1], enemy_pieces[2],
                               enemy_pieces[3], enemy_pieces[4]);
        // pawns, knights, bishops, rooks, queens
        score += piece_square_eval(board, our_pieces, enemy_pieces);

        score += mobility_eval(board);

        hash_table.put(zobrist, score); // this put here to clear cache
        return score;
    }
} // namespace evaluation
