import chess
import chess.engine
from scratch import piece_map
import sys
sys.path.append(r"C:\Users\DELL\Documents\mihansolo_bot\build\Debug")
import engine # type: ignore 
# pylint doesnt like C++ extensions

PIECE_VALUES = {
    chess.PAWN: 1,
    chess.KNIGHT: 3,
    chess.BISHOP: 3,
    chess.ROOK: 5,
    chess.QUEEN: 9,
    chess.KING: 0,
}

# TODO: add logging
# TODO: MVV_LAA ordering
# TODO: reduce scope of variables by putting inside else clause
# TODO: add unit tests
# TODO: fill in the piece value maps with {square: value} pairs
# TODO: add penalty for undeveloping pieces, less than 1 point
# TODO: Add iterative deepening
# TODO: add NNUE eval


def mvv_laa(board: chess.Board, move: chess.Move) -> tuple[int, int, int]: # TODO: Move to C++
    if board.is_capture(move):
        if board.is_en_passant(move):
            return (1, 1, -1)
        victim_value = PIECE_VALUES[board.piece_type_at(move.to_square)]
        attacker_value = PIECE_VALUES[board.piece_type_at(move.from_square)]
        return (2, victim_value, -attacker_value)
    if board.gives_check(move):
        return (1,0,0)
    return (0, 0, 0)


def is_quiet(board: chess.Board) -> bool: # TODO: Move to C++
    if any(board.is_capture(move) for move in board.legal_moves):
        return False
    return True


def quiescence_search( # Deal with this later
    board: chess.Board, alpha: float, beta: float, qdepth: int = 4, ply = 0
) -> tuple[int, chess.Move]:
    global counter
    counter = counter + 1
    static_eval = engine.evaluate(board, ply)
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
            ):
                board.push(move)
                score, _ = quiescence_search(board, -beta, -alpha, qdepth - 1)
                score = -score  # Negamax algo, same as minimax (impler to implement)
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
def find_book_move() -> chess.Move | None: # Move to C++
    try:
        move = engine.book_move()
        if move:
            return move
    except:
        return None

def search(fen: str=None) -> chess.engine.PlayResult:
    if fen:
        engine.position_set(fen)
    book_move = find_book_move()
    if book_move:
        return chess.engine.PlayResult(book_move, None)
    depth = 2
    _, best_move = negamax(float("-inf"), float("inf"), None, depth)
    if best_move:
        return chess.engine.PlayResult(best_move, None)
    else:
        raise TypeError("negamax returned a None value, something went wrong")


def game_over(board: chess.Board) -> bool: # Move to C++
    if engine.game_over():
        return True
    return False


def negamax(
    alpha: float, beta: float, last_move: chess.Move, depth: int, ply: int=0
) -> tuple[float, chess.Move | None]:
    if depth == 0 or engine.game_over():
        return engine.evaluate(ply), last_move
    best_move = None
    best_eval = float("-inf")
    # legal_moves = sorted(
      #   engine.get_legal_moves(), key=lambda move: mvv_laa(move), reverse=True
    # ) # Move movegen to C++
    legal_moves = engine.get_legal_moves()
    for move in legal_moves:
        engine.make_move(move)
        score, _ = negamax(-beta, -alpha, move, depth - 1, ply + 1)
        score = -score  
        engine.unmake_move(move)
        if score > best_eval:
            best_eval = score
            best_move = move
        alpha = max(alpha, score)
        if beta <= alpha:
            break
    return best_eval, best_move
