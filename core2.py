import chess
from chess.engine import PlayResult
import chess.polyglot
import random

global counter
counter = 1

PIECE_VALUES = {
    chess.PAWN: 1,
    chess.KNIGHT: 3,
    chess.BISHOP: 3,
    chess.ROOK: 5,
    chess.QUEEN: 9,
    chess.KING: 0,
}

# TODO: add standing pat eval
# TODO: add logging
# TODO: MVV_LAA ordering
# TODO: reduce scope of variables by putting inside else clause
# TODO: add unit tests
# TODO: fill in the piece value maps with {square: value} pairs
# TODO: add penalty for undeveloping pieces, less than 1 point
# TODO: Add iterative deepening
# TODO: add NNUE eval


def mvv_laa(board: chess.Board, move: chess.Move) -> tuple[int, int, int]:

    if board.is_capture(move):
        if board.is_en_passant(move):
            return (1, 1, -1)
        victim_value = PIECE_VALUES[board.piece_type_at(move.to_square)]
        attacker_value = PIECE_VALUES[board.piece_type_at(move.from_square)]
        return (1, victim_value, -attacker_value)

    return (0, 0, 0)


def is_quiet(board: chess.Board) -> bool:

    if any(board.is_capture(move) for move in board.legal_moves):
        return False

    return True


def quiescence_search(
    board: chess.Board, alpha: float, beta: float, qdepth: int = 4
) -> tuple[int, chess.Move]:
    global counter
    counter = counter + 1
    print(
        f"QS depth: {qdepth}, fen: {board.fen()}",
        "Search number: ",
        counter,
        "alpha: ",
        alpha,
        "beta: ",
        beta,
    )
    static_eval = evaluate(board)

    if static_eval >= beta:  # standing pat evaluation, new feature
        return static_eval, None

    if static_eval > alpha:
        alpha = static_eval

    if is_quiet(board) or board.is_game_over() or qdepth == 0:
        return (
            static_eval,
            None,
        )  # best_move at this point is none since search hasn't started yet

    else:
        best_eval = float("-inf")
        best_move = None

        for move in board.legal_moves:
            if not board.is_capture(move):
                continue
            captured_piece_type = board.piece_type_at(move.to_square)
            attacker_piece_type = board.piece_type_at(move.from_square)
            if (
                PIECE_VALUES[captured_piece_type] >= PIECE_VALUES[attacker_piece_type]
            ):  # or board.gives_check(move):
                board.push(move)
                print("searching move: ", move, "in position: ", board)
                score, _ = quiescence_search(board, -beta, -alpha, qdepth - 1)
                score = -score  # Negamax algo, same as minimax (impler to implement
                board.pop()
                if score >= beta:
                    return score, move
                if score > best_eval:
                    best_eval = score
                if score > alpha:
                    alpha = score
                    best_move = move
    return best_eval, best_move


# chess functions
def find_book_move(board: chess.Board) -> chess.Move | None:
    try:
        with chess.polyglot.open_reader("gm2600.bin") as reader:
            result = random.choice(list(reader.find_all(board))).move
            if result:
                print(f"Found book move: {result}")
                return result
    except Exception as e:
        return None  # did not work, book doesn't have move for that position


def evaluate(board: chess.Board) -> int:
    value = 0

    if board.is_checkmate():
        if board.turn:
            return -(10**3)  # white gets mated
        else:
            return 10**3  # black gets mated

    if (
        board.is_stalemate()
        or board.is_insufficient_material()
        or board.is_repetition()
    ):
        return 0  # draw

    value = value + len(board.pieces(chess.PAWN, chess.WHITE))
    value = value + len(board.pieces(chess.KNIGHT, chess.WHITE)) * 3
    value = value + len(board.pieces(chess.BISHOP, chess.WHITE)) * 3
    value = value + len(board.pieces(chess.ROOK, chess.WHITE)) * 5
    value = value + len(board.pieces(chess.QUEEN, chess.WHITE)) * 9

    value = value - len(board.pieces(chess.PAWN, chess.BLACK))
    value = value - len(board.pieces(chess.KNIGHT, chess.BLACK)) * 3
    value = value - len(board.pieces(chess.BISHOP, chess.BLACK)) * 3
    value = value - len(board.pieces(chess.ROOK, chess.BLACK)) * 5
    value = value - len(board.pieces(chess.QUEEN, chess.BLACK)) * 9
    # These show the material imbalance of how many more points of white material there is
    # since winning material is usually better than development except in the opening.

    return (
        value if board.turn else -value
    )  # should always return from the POV of side to move


def search(board: chess.Board) -> PlayResult:
    book_move = find_book_move(board)
    if book_move:
        print(f"Book move: {book_move}")
        return PlayResult(book_move, None)
    depth = 6

    _, best_move = negamax(float("-inf"), float("inf"), None, depth, board)

    if best_move:
        return PlayResult(best_move, None)
    else:
        raise TypeError("negamax returned a None value, something went wrong")


def game_over(board: chess.Board) -> bool:
    if board.is_checkmate() or board.is_stalemate() or board.is_insufficient_material():
        return True
    return False


def negamax(
    alpha: float, beta: float, last_move: chess.Move, depth: int, board: chess.Board
) -> tuple[float, chess.Move | None]:

    if depth == 0 or game_over(board):
        # return quiescence_search(board, alpha, beta)[0], last_move
        return evaluate(board), last_move

    best_move = None
    best_eval = float("-inf")
    legal_moves = sorted(
        list(board.legal_moves), key=lambda move: mvv_laa(board, move), reverse=True
    )

    for move in legal_moves:
        board.push(move)
        score, _ = negamax(-beta, -alpha, move, depth - 1, board)
        score = -score
        board.pop()
        if score > best_eval:
            best_eval = score
            best_move = move
        alpha = max(alpha, score)
        if beta <= alpha:
            break
    return best_eval, best_move
