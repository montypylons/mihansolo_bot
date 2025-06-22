from core import search
import core2
import chess


def test_eval():
    board3 = chess.Board("8/8/B4R2/7R/3pk3/P7/P1PPPP1P/2BQK3 w - - 11 37")
    print(core2.search(board3).move)


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


def test(searcher=False) -> str:
    board1 = chess.Board("8/8/BR6/7R/3pk3/P7/P1PPPP1P/2BQK3 w - - 7 35")
    board3 = chess.Board("8/8/B4R2/7R/3pk3/P7/P1PPPP1P/2BQK3 w - - 11 37")
    boards = [board1, board3]
    if not searcher:
        print("evaluations")
        print(core2.evaluate(board1), core2.evaluate(board3))
    searched_moves = []
    searched_moves.append(core2.search(board1).move)
    searched_moves.append(core2.search(board3).move)
    for i in range(2):
        if boards[i] is not None and searched_moves[i] is not None:
            boards[i].push(searched_moves[i])
            if boards[i].is_checkmate():
                boards[i].pop()
                print("Test number", i, "attempt: ", searched_moves[i])
                print("[PASS] Test Passed")
            else:
                boards[i].pop()
                print("Test number", i, "attempt: ", searched_moves[i])
                print("[FAIL] Test Failed")


if __name__ == "__main__":
    # main()
    print(test())
