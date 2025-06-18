import chess
from chess.engine import PlayResult
import chess.polyglot

# chess functions
def book_move(board: chess.Board, book_path: str = "Titans.bin") -> PlayResult:
    try:
        with chess.polyglot.open_reader("data/polyglot/performance.bin") as reader:
            reader.find_all(board)[1]
    except:
        return None # did not work, book doesn't have move for that position

def evaluate(board, White=True):
    """Naive evaluation function which only takes into mind the
    material on the board and whether or not it is checkmate."""
    # TODO: add more heuristics to the evaluation
    value = 0
    if board.is_checkmate():
        if board.turn:
            return -999999
        else:
            return 999999

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
    else:
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

    return value


def search(board):  # TODO: add function to get all legal moves
    if book_move(board):
        return book_move(board)
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
        return evaluate(board, White=board.turn), last_move
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


# TODO: learn basic chess heuristics
# TODO: add NNUE eval function
