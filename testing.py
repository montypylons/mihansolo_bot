from core import search
import core2
import chess
import engine
# TODO: add unit testing, not this stuff

def test_eval_lite():
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
    # board3 = chess.Board("8/8/B4R2/7R/3pk3/P7/P1PPPP1P/2BQK3 w - - 11 37")
    # win_queen_puzzle = chess.Board("r5kr/p4ppp/5n2/3p4/8/1NQ3PP/qP3P1K/7R w - - 0 37")
    boards = [board1]# , board3]
    if not searcher:
        print("evaluations")
        print(core2.evaluate(board1))# , core2.evaluate(board3))
    searched_moves = []
    searched_moves.append(core2.search(board1).move)
    # searched_moves.append(core2.search(board3).move)
    print(searched_moves)
    # searched_moves.append(core2.search(win_queen_puzzle))
    '''if searched_moves[2] == chess.Move.from_uci("h1a1"):
        print("test [PASS]")
    else:
        print("---------------------------TEST FAILED--------------------------")
        print(f"attempt:{searched_moves[2].move}. correct move: h1a1 ")'''

    for i in range(1):
        if boards[i] is not None and searched_moves[i] is not None:
            boards[i].push(searched_moves[i])
            if boards[i].is_checkmate():
                boards[i].pop()
                print("Test number", i, "attempt: ", searched_moves[i])
                print("-------------------------TEST PASSED---------------------------")
            else:
                boards[i].pop()
                print("Test number", i, "attempt: ", searched_moves[i])
                print("-------------------------TEST FAILED---------------------------")

def test_eval():
    fen_strings = ['1k6/ppp5/8/8/8/2Q5/1QQQQQ2/1QQQ2K1 b - - 0 1', '8/8/8/8/8/1k6/1q6/1K6 w - - 0 1', '2kqqq2/3qqq2/3qqq2/8/8/PPPP4/1KP5/8 w - - 0 1', '1k6/ppp5/8/8/8/2Q5/1QQQQQ2/1QQQ2K1 w - - 0 1']
    for fen_string in fen_strings:
        print("="*100)
        print(core2.evaluate(chess.Board(fen_string)))
        print(engine.evaluate(fen_string,0))
        print("="*100)

if __name__ == "__main__":
    print(test())
