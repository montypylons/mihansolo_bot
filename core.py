import chess
from chess.engine import PlayResult
import chess.polyglot
import random

knight_value_map = {}
rook_value_map = {}
bishop_value_map = {}
pawn_value_map = {}
king_value_map = {}
queen_value_map = {}

# TODO: add standing pat eval
# TODO: add logging
# TODO: MVV_LAA ordering
# TODO: reduce scope of variables by putting inside else clause
# TODO: add unit tests
# TODO: fill in the piece value maps with {square: value} pairs
# TODO: add penalty for undeveloping pieces, less than 1 point
# TODO: Add iterative deepening





def order_moves(moves: list) -> list:
    pass


def is_quiet(board: chess.Board) -> bool:

    if any(board.is_capture(move) for move in board.legal_moves):
        return False

    return True


def quiescence_search(  # not using right now, fixing core functions first
    board: chess.Board, alpha: float, beta: float, qdepth: int = 8
) -> (
    int
):
    print(f"QS depth: {qdepth}, fen: {board.fen()}")
    best_move = None
    non_quiescent = False
    if is_quiet(board) or board.is_game_over() or qdepth == 0:
        return evaluate(board), best_move
    else:
        best_eval = float("-inf")
        for move in board.legal_moves:
            if board.is_capture(move):  # or board.gives_check(move):
                non_quiescent = True
                board.push(move)
                eval, _ = quiescence_search(board, -beta, -alpha, qdepth - 1)
                eval = -eval  # Negamax algo, same as negamax(impler to implement
                board.pop()
                if eval > best_eval:
                    best_eval = eval
                    best_move = move
                alpha = max(alpha, eval)
                if beta <= alpha:
                    break
        if not non_quiescent:
            return evaluate(board), None
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
            return -999999  # white gets mated
        else:
            return 999999  # black gets mated

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


def search(board: chess.Board):  
    book_move = find_book_move(board)
    if book_move:
        print(f"Book move: {book_move}")
        return PlayResult(book_move, None)
    depth = 5

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

    for move in board.legal_moves:
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


def parse_uci():
    pass  # add UCI support for SPRT testing later
