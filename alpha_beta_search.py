class Node:
    def __init__(self, name, children=None, value=None):
        self.name = name
        self.children = children if children is not None else []
        self.value = value

    def evaluate(node):
        return node.value
    def is_terminal(node):
        return node.value is not None