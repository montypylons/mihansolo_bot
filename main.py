import chess

# chess functions


def evaluate(node: chess.Board, White=True):
    """Naive evaluation function which only takes into mind the
    material on the board and whether or not it is checkmate."""
    # TODO: add more heuristics to the evaluation
    value = 0
    if White == True:
        value = value + len(node.pieces(chess.PAWN, chess.WHITE))
        value = value + len(node.pieces(chess.KNIGHT, chess.WHITE)) * 3
        value = value + len(node.pieces(chess.BISHOP, chess.WHITE)) * 3
        value = value + len(node.pieces(chess.ROOK, chess.WHITE)) * 5
        value = value + len(node.pieces(chess.QUEEN, chess.WHITE)) * 9
        if node.is_checkmate():
            value = float("-inf")
    return value


def search(fen):  # TODO: add function to get all legal moves a
    # TODO: and search for the best one using a alpha/beta pruned minimax tree
    pass


# minimax algos
class Node:
    def __init__(self, value, children):
        self.value = value
        self.children = children


def game_over(node):  # TODO: implement this
    # check for checkmate, stalemate, or insufficient material
    if not node.children:
        return True
    else:
        return False


# default is that you are the maximizing player
def minimax(alpha, beta, depth, node, maximizing_player=True):
    if depth == 0 or game_over(node):
        return evaluate(node)
    if maximizing_player:
        max_eval = float("-inf")
        for child in node.children:
            eval = minimax(alpha, beta, depth - 1, child, False)
            max_eval = max(max_eval, eval)
            alpha = max(alpha, eval)
            if beta <= alpha:
                break
        return max_eval

    else:
        min_eval = float("inf")
        for child in node.children:
            eval = minimax(alpha, beta, depth - 1, child, True)
            min_eval = min(min_eval, eval)
            beta = min(beta, eval)
            if beta <= alpha:
                break
        return min_eval


def main():
    board = chess.Board()
    white = input("enter y if you want to be white, n if not")
    if white.lower() == "y":
        white = True
        while not board.is_game_over():
            board.push_san(input("What is your move - dont include # or + symbol"))
            board.push_san(search(board.fen()))
        print("Game over, GG WP")
    elif white.lower() == "n":
        white = False
        while not board.is_game_over():
            board.push_san(search(board.fen()))
            board.push_san(input("What is your move - dont include # or + symbol"))
        print("Game over, GG WP")
    else:
        print("enter a y or n")


# TODO: make it work
# TODO: learn basic chess heuristics
