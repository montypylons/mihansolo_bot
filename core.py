import chess
from chess.engine import PlayResult
import chess.polyglot
import random

# todo list
# TODO: add standing pat eval
# TODO: MVV_LAA ordering
# TODO: refactor loops
# TODO: use quiet instead of quiescent
# TODO: reduce scope of variables by putting inside else clause
# TODO: add Negamax instead of minimax
# TODO: add unit tests.

def order_moves(moves: list) -> list:  # makes alpha/beta search more effective
    pass


def is_quiescent(board: chess.Board) -> bool:

    if any(board.is_capture(move) for move in board.legal_moves):
        return False
    # if any(board.gives_check(move) for move in board.legal_moves):
    # return False

    return True


def quiescence_search(
    board: chess.Board, alpha: float, beta: float, qdepth=8
):  # TODO: need to add standing pat evaluation in order to stop the search from going on the the current 1 mil+ positions on the first move.
    print(f"QS depth: {qdepth}, fen: {board.fen()}")
    best_move = None
    non_quiescent = False
    if is_quiescent(board) or board.is_game_over() or qdepth == 0:
        return evaluate(board), best_move
    else:
        max_eval = float("-inf")
        for move in board.legal_moves:
            if board.is_capture(move):  # or board.gives_check(move):
                non_quiescent = True
                board.push(move)
                eval, _ = quiescence_search(board, -beta, -alpha, qdepth - 1)
                eval = -eval  # Negamax algo, same as minimax just simpler to implement
                board.pop()
                if eval > max_eval:
                    max_eval = eval
                    best_move = move
                alpha = max(alpha, eval)
                if beta <= alpha:
                    break
        if not non_quiescent:
            return evaluate(board), None
        return max_eval, best_move


# chess functions
def book_move(board: chess.Board) -> chess.Move | None:
    try:
        with chess.polyglot.open_reader("gm2600.bin") as reader:
            if reader.find_all(board):
                return random.choice(list(reader.find_all(board))).move
    except Exception as e:
        return None  # did not work, book doesn't have move for that position


def evaluate(board):  
    value = 0
    White = True
    if board.is_checkmate():
        if board.turn:
            return -999999
        else:
            return 999999

    if (
        board.is_stalemate()
        or board.is_insufficient_material()
        or board.is_repetition()
    ):
        return 0

    if White == True:
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
        return value
    """else:
        value = value - len(board.pieces(chess.PAWN, chess.WHITE))
        value = value - len(board.pieces(chess.KNIGHT, chess.WHITE)) * 3
        value = value - len(board.pieces(chess.BISHOP, chess.WHITE)) * 3
        value = value - len(board.pieces(chess.ROOK, chess.WHITE)) * 5
        value = value - len(board.pieces(chess.QUEEN, chess.WHITE)) * 9

        value = value + len(board.pieces(chess.PAWN, chess.BLACK))
        value = value + len(board.pieces(chess.KNIGHT, chess.BLACK)) * 3
        value = value + len(board.pieces(chess.BISHOP, chess.BLACK)) * 3
        value = value + len(board.pieces(chess.ROOK, chess.BLACK)) * 5
        value = value + len(board.pieces(chess.QUEEN, chess.BLACK)) * 9

    return value"""


def search(board):  # TODO: add quiescence search and iterative deepening
    _book_move = book_move(board)
    if _book_move:
        print(f"Book move: {_book_move}")
        return PlayResult(_book_move, None)
    depth = 5
    _, best_move = minimax(float("-inf"), float("inf"), None, depth, board, board.turn)

    if best_move:
        return PlayResult(best_move, None)
        # return best_move
    else:
        raise TypeError("Minimax returned a None value, which is bad.")


# minimax algos
def game_over(board):  # TODO: implement this
    # check for checkmate, stalemate, or insufficient material
    if board.is_checkmate() or board.is_stalemate() or board.is_insufficient_material():
        return True
    return False  # placeholder, always returns False


# default is that you are the maximizing player
def minimax(alpha, beta, last_move, depth, board, maximizing_player=True):
    best_move = None
    if depth == 0 or game_over(board):
        return quiescence_search(board, alpha, beta)[0], last_move
    if maximizing_player:
        max_eval = float("-inf")
        for move in board.legal_moves:
            board.push(move)
            eval, _ = minimax(alpha, beta, move, depth - 1, board, False)
            board.pop()
            if eval > max_eval:
                max_eval = eval
                best_move = move

            alpha = max(alpha, eval)
            if beta <= alpha:
                break
        return max_eval, best_move

    else:
        min_eval = float("inf")
        for move in board.legal_moves:
            board.push(move)

            eval, _ = minimax(alpha, beta, move, depth - 1, board, True)
            board.pop()
            if eval < min_eval:
                min_eval = eval
                best_move = move
            beta = min(beta, eval)

            if beta <= alpha:
                break
        return min_eval, best_move


def test():
    board = chess.Board()
    for i in range(10):
        result = search(board)
        if result:
            board.push(result.move)
            print(f"Best move: {result.move}", "move number", i + 1)
        print(board)


test()
# TODO: learn basic chess heuristics
# TODO: add NNUE eval function
