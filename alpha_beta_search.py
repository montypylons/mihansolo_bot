# example from GeeksforGeeks

class Node:
    def __init__(self, name, children=None, value=None):
        self.name = name
        self.children = children if children is not None else []
        self.value = value

    def evaluate(node):
        return node.value
    
    def is_terminal(node):
        return node.value is not None
    
    def get_children(node):
        return node.children
    
    def alpha_beta_pruning(node, depth, alpha, beta, maximizing_player):
        if depth == 0 or node.is_terminal():
            return node.evaluate()
        if maximizing_player:
            max_eval = float('inf')
            for child in node.get_children():
                eval = alpha_beta_pruning(child, depth - 1, alpha, beta, False)
                max_eval = max(max_eval, eval)
                alpha = max(alpha, eval)
                if beta <= alpha:
                    break
            return max_eval
        else:
            min_eval = float('inf')
            for child in node.get_children():
                eval = alpha_beta_pruning(child, depth - 1, alpha, beta, True)
                min_eval = min(min_eval, eval)
                beta = min(beta, eval)
                if beta <= alpha:
                    break
                return min_eval
            
D= Node('D',value=3)
E= Node('E',value=12)
F= Node('F',value=8)
G= Node('G',value=2)
H= Node('H',value=6)
I = Node('I',value=14)
B = Node('B', [D, E,F], value=5)
C = Node('C', [G, H, I], value=4)
A = Node('A', children=[B,C])

maximizing_player = True
initial_alpha = float('-inf')
initial_beta = float('inf')
depth = 3  # Maximum depth of the tree

optimal_value = alpha_beta_pruning(A, depth, initial_alpha, initial_beta, maximizing_player)
print(f"The optimal value is: {optimal_value}")