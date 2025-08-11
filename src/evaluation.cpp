#include "chess.hpp"
#include "utils.hpp"
#include "evaluation.hpp"
#include "engine.hpp"
#include <array>
#include <thread>
#include <future>


namespace evaluation
{
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
        bool queens = false;
        bool under_seven_men = false;

        if (board.pieces(chess::PieceType::KING).count() + board.pieces(chess::PieceType::KNIGHT).count() + board.
            pieces(chess::PieceType::BISHOP).count() + board.pieces(chess::PieceType::ROOK).count() < 8)
        {
            under_seven_men = true;
        }
        if (board.pieces(chess::PieceType::QUEEN).count() == 0)
        {
            queens = true;
        }
        return under_seven_men && queens;
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

                square = board.at(chess::Square(square)).color() == chess::Color::WHITE ? square : square ^ 56;

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
        const bool check = board.inCheck();

        chess::Movelist moves;
        chess::movegen::legalmoves(moves, board);

        const bool no_moves = moves.empty();

        if (check && no_moves)
        {
            return -10000 + ply;
        }
        if (board.isInsufficientMaterial() || board.isRepetition() || (!check && no_moves))
        {
            return 0;
        }
        return std::nullopt;
    }


    int mobility_eval_threaded(const chess::Board& board)
    {
        auto calculate_mobility = [](std::promise<int>& eval, const chess::Board& board1,
                                     const chess::PieceGenType gen_type,
                                     const int mobility_factor) -> void
        {
            int mobility_eval = 0;

            chess::Movelist moves_for_piece;

            chess::movegen::legalmoves(moves_for_piece, board1, gen_type);
            mobility_eval -= moves_for_piece.size() * mobility_factor;

            eval.set_value(mobility_eval);
        };
        auto calculate_mobility_enemy = [](std::promise<int>& eval, const chess::Board& board1,
                                           const chess::PieceGenType gen_type,
                                           const int mobility_factor) -> void
        {
            chess::Board temp_board = board1;
            int mobility_eval = 0;
            chess::Movelist moves_for_piece;

            temp_board.makeNullMove();
            chess::movegen::legalmoves(moves_for_piece, temp_board, gen_type);
            mobility_eval -= moves_for_piece.size() * mobility_factor;
            temp_board.unmakeNullMove();

            eval.set_value(mobility_eval);
        };

        std::promise<int> eval_our_bishops;
        std::promise<int> eval_our_knights;
        std::promise<int> eval_our_rooks;
        std::promise<int> eval_our_queens;
        std::promise<int> eval_their_bishops;
        std::promise<int> eval_their_knights;
        std::promise<int> eval_their_rooks;
        std::promise<int> eval_their_queens;


        auto t1 = std::thread(calculate_mobility, std::ref(eval_our_bishops), std::cref(board),
                              chess::PieceGenType::BISHOP,
                              utils::BISHOP_MOBILITY_FACTOR);
        auto t2 = std::thread(calculate_mobility, std::ref(eval_our_knights), std::cref(board),
                              chess::PieceGenType::KNIGHT,
                              utils::KNIGHT_MOBILITY_FACTOR);
        auto t3 = std::thread(calculate_mobility, std::ref(eval_our_rooks), std::cref(board),
                              chess::PieceGenType::ROOK,
                              utils::ROOK_MOBILITY_FACTOR);
        auto t4 = std::thread(calculate_mobility, std::ref(eval_our_queens), std::cref(board),
                              chess::PieceGenType::QUEEN,
                              utils::QUEEN_MOBILITY_FACTOR);

        auto t5 = std::thread(calculate_mobility_enemy, std::ref(eval_their_bishops), std::cref(board),
                              chess::PieceGenType::BISHOP,
                              utils::BISHOP_MOBILITY_FACTOR);
        auto t6 = std::thread(calculate_mobility_enemy, std::ref(eval_their_knights), std::cref(board),
                              chess::PieceGenType::KNIGHT,
                              utils::KNIGHT_MOBILITY_FACTOR);
        auto t7 = std::thread(calculate_mobility_enemy, std::ref(eval_their_rooks), std::cref(board),
                              chess::PieceGenType::ROOK,
                              utils::ROOK_MOBILITY_FACTOR);
        auto t8 = std::thread(calculate_mobility_enemy, std::ref(eval_their_queens), std::cref(board),
                              chess::PieceGenType::QUEEN,
                              utils::QUEEN_MOBILITY_FACTOR);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();
        t8.join();

        return eval_our_bishops.get_future().get() + eval_our_knights.get_future().get() + eval_our_rooks.get_future().
            get() + eval_our_queens.get_future().get() + eval_their_bishops.get_future().get() + eval_their_knights.
            get_future().get() + eval_their_rooks.get_future().get() +
            eval_their_queens.get_future().get();
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
        int score = 0;

        if (const std::optional<int> result = game_over_eval(board, ply); result != std::nullopt)
        {
            return result.value();
        }

        const auto& generated_bitboards = initialize_bitboards(board);

        const auto& our_pieces = std::get<0>(generated_bitboards);
        const auto& enemy_pieces = std::get<1>(generated_bitboards);

        score += material_eval(our_pieces[0], our_pieces[1], our_pieces[2], our_pieces[3], our_pieces[4],
                               enemy_pieces[0], enemy_pieces[1], enemy_pieces[2],
                               enemy_pieces[3], enemy_pieces[4]);
        // pawns, knights, bishops, rooks, queens
        score += piece_square_eval(board, our_pieces, enemy_pieces);

        score += mobility_eval(board);

        return score;
    }
} // namespace evaluation
