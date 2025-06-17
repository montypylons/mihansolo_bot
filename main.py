import chess

# variables to represent piece values
# helps to evaluate position
king = 0
rook = 5
pawn = 1
knight = 3
bishop = 3
queen = 9

# simple implementation of Alpha-Beta pruning algorithm
# just for learning how it works

# chess functions

def evaluate(node):
    return node.value

def best_move(fen):
    pass


# minimax algos
class Node:
    def __init__(self, value, children):
        self.value = value
        self.children = children

def game_over(node): # TODO: implement this
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
        max_eval = float('-inf')
        for child in node.children:
            eval = minimax(alpha,beta,depth-1,child, False)
            max_eval = max(max_eval, eval)
            alpha = max(alpha, eval)
            if beta <= alpha:
                break
        return max_eval
    
    else:
        min_eval = float('inf')
        for child in node.children:
            eval = minimax(alpha, beta, depth-1, child, True)
            min_eval = min(min_eval, eval)  
            beta = min(beta, eval)
            if beta <= alpha:
                break
        return min_eval

def main():
    board = chess.Board()
    white = input("enter y if you want to be white")
    if white.lower() == 'y':
        white = True
        board.push_san(input('What is your move - dont include # or + symbol'))
    else:
        white = False
        board.push_san(best_move(board.fen()))
    
    while not board.is_game_over():
        

    

# TODO: make it work
# TODO: learn basic chess heuristics
