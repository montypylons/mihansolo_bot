from core import search
import chess


def main():
    board = chess.Board()
    print("initializing match of engine vs engine, thanks for watching!")
    while not board.is_game_over():
        print("Current state of board: ", board)
        white_move= search(board)
        print("White move: ", white_move.move)
        board.push(white_move.move)
        black_move = search(board)
        print("Black move: ", black_move.move)
        board.push(black_move.move)
    print("Game result: ", board.result())

if __name__ == '__main__':
    main()