import cProfile
import core
import core2
import chess

board = chess.Board("8/8/B4R2/7R/3pk3/P7/P1PPPP1P/2BQK3 w - - 11 37")

cProfile.run('core2.search(board=board)')
print("="*100)
print("core VERSION 1")
cProfile.run('core.search(board=board)')