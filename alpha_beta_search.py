
# simple implementation of Alpha-Beta pruning algorithm
# just for learning how it works

class Node:
    def __init__(self, value, children):
        self.value = value
        self.children = children

def evaluate(node):
    return node.value

def game_over(node): # TODO: implement this
    # check for checkmate, stalemate, or insufficient material
    if not node.children:
        return True
    else:
        return False

# default is that you are the maximizing player
def minimax(depth, node, maximizing_player=True):
    if depth == 0 or game_over(node):
        return evaluate(node)
    if maximizing_player:
        max_eval = float('-inf')
        for child in node.children:
            eval = minimax(depth-1,child, False)
            max_eval = max(max_eval, eval)
        return max_eval
    else:
        min_eval = float('inf')
        for child in node.children:
            eval = minimax(depth-1, child, True)
            min_eval = min(min_eval, eval)  
        return min_eval




Node1 = Node(3, None)
Node2 = Node(4, None)
Node3 = Node(5, None)
Node4 = Node(-4, None)
Node5 = Node(-5, None)
Node6 = Node(6, None)
Node7 = Node(0, None)
Node8 = Node(-2, None)

Node9 = Node(7, [Node1, Node2])
Node10 = Node(-4, [Node3, Node4])
Node11 = Node(0, [Node5, Node6])
Node12 = Node(2, [Node7, Node8])    

Node13 = Node(3, [Node9, Node10])
Node14 = Node(-1, [Node11, Node12])

Node15 = Node(5, [Node13, Node14])


minimax(5, Node15, True)