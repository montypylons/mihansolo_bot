import chess

# chess functions


def evaluate(node, White=True):
    """Naive evaluation function which only takes into mind the
    material on the board and whether or not it is checkmate."""
    # TODO: add more heuristics to the evaluation
    board = chess.Board(node.position_fen)
    value = 0
    if White == True:
        value = value + len(board.pieces(chess.PAWN, chess.WHITE))
        value = value + len(board.pieces(chess.KNIGHT, chess.WHITE)) * 3
        value = value + len(board.pieces(chess.BISHOP, chess.WHITE)) * 3
        value = value + len(board.pieces(chess.ROOK, chess.WHITE)) * 5
        value = value + len(board.pieces(chess.QUEEN, chess.WHITE)) * 9
        if board.is_checkmate():
            value = float("-inf")
    return value


def build_tree(last_move, fen, depth=3):
    """Builds a tree of nodes from the given FEN string."""
    board = chess.Board(fen)
    if depth == 0 or board.is_game_over():
        return Node(fen, [], last_move)

    children = []
    for move in board.legal_moves:
        board.push(move)
        child_node = build_tree(move, board.fen(), depth - 1)
        children.append(child_node)
        board.pop()

    return Node(fen, children, last_move)


def search(fen):  # TODO: add function to get all legal moves a
    # TODO: and search for the best one using a alpha/beta pruned minimax tree
    board = chess.Board(fen)
    legal_moves = list(board.legal_moves)
    best_move = None
    tree = build_tree(None, fen, 3)  # build the tree with depth 3
    best_move = minimax(float("-inf"), float("inf"), 3, tree, True)
    if best_move:
        return best_move
    else:
        raise TypeError("Minimax returned a None value, which is not expected.")


# minimax algos
class Node:
    def __init__(self, position_fen, children, last_move):
        self.position_fen = position_fen
        self.children = children
        self.last_move = last_move


def game_over(node):  # TODO: implement this
    # check for checkmate, stalemate, or insufficient material
    return False  # placeholder, always returns False


# default is that you are the maximizing player
def minimax(alpha, beta, depth, node, maximizing_player=True):
    best_move = None
    if depth == 0 or game_over(node):
        return evaluate(node), node.last_move
    if maximizing_player:
        max_eval = float("-inf")
        for child in node.children:
            eval = (
                minimax(alpha, beta, depth - 1, child, False)[1]
                if isinstance(minimax(alpha, beta, depth - 1, child, False)[1], int)
                else minimax(alpha, beta, depth - 1, child, False)[0]
            )
            max_eval = max(max_eval, eval[1])
            best_move = child.last_move
            alpha = max(alpha, eval[1])
            if beta <= alpha:
                break
        return best_move, max_eval

    else:
        min_eval = float("inf")
        for child in node.children:
            eval = minimax(alpha, beta, depth - 1, child, True)
            min_eval = min(min_eval, eval[1])
            beta = min(beta, eval[1])
            best_move = child.last_move
            if beta <= alpha:
                break
        return best_move, min_eval


def main():
    board = chess.Board()
    white = input("enter y if you want to be white, n if not")
    if white.lower() == "y":
        white = True
        while not board.is_game_over():
            board.push(
                board.parse_san(input("What is your move - dont include # or + symbol"))
            )
            board.push(search(board.fen()))
        print("Game over, GG WP")
    elif white.lower() == "n":
        white = False
        while not board.is_game_over():
            board.push(search(board.fen()))
            board.push(
                board.parse_san(input("What is your move - dont include # or + symbol"))
            )
        print("Game over, GG WP")
    else:
        print("enter a y or n")


main()
# TODO: make it work
# TODO: learn basic chess heuristics
