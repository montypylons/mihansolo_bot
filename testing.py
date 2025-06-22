from core import search
import core2
import chess


def main():
    board = chess.Board()
    print("initializing match of engine vs engine, thanks for watching!")
    while not board.is_game_over():
        print("Current state of board: ", board)
        white_move = core2.search(board)
        print("White move: ", white_move.move)
        board.push(white_move.move)
        black_move = core2.search(board)
        print("Black move: ", black_move.move)
        board.push(black_move.move)
    print("Game result: ", board.result())

def test():
    board = chess.Board("r7/8/1k6/8/8/8/6q1/1K5R b - - 0 1")
    return core2.search(board)

if __name__ == "__main__":
    # main()
    test()
