import cProfile
import core
import core2
import chess

board = chess.Board("rnbqkbnr/pppppppp/8/8/8/2N2N2/PPPPPPPP/R1BQKB1R w KQkq - 0 1")

cProfile.run('core2.search(board=board)',sort='cumulative')
print("="*100)
#print("core VERSION 1")
#cProfile.run('core.search(board=board)')