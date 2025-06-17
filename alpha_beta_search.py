
# simple implementation of Alpha-Beta pruning algorithm
# just for learning how it works

class Node:
    def __init__(self):
        pass

def evaluate(node):
    pass

def game_over(node):
    pass

# default is that you are the maximizing player
def alpha_beta(depth, node, maximizing_player=True):
    if depth == 0 or game_over(node):
        return evaluate(node)
    if maximizing_player:
        max_eval = float('-inf')
        for child in node.children:
            eval = alpha_beta(depth-1,child, False)
            max_eval = max(max_eval, eval)
        return max_eval
    else:
        min_eval = float('inf')
        for child in node.children:
            eval = alpha_beta(depth-1, child, True)
            min_eval = min(min_eval, eval)  
        return min_eval




Node1 = Node()
alpha_beta(3, Node1, True)