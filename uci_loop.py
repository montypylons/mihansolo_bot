import sys
import chess
import contextlib
import io
from core import search


@contextlib.contextmanager
def suppress_output():
    saved_stdout = sys.stdout
    try:
        sys.stdout = io.StringIO()
        yield
    finally:
        sys.stdout = saved_stdout


class UCIEngine:
    def __init__(self, search_function):
        self.board = chess.Board()
        self.search = (
            search_function  # expects: search(board: chess.Board) -> chess.PlayResult
        )

    def parse_position(self, args):
        if not args:
            return
        idx = 0
        if args[idx] == "startpos":
            self.board.reset()
            idx += 1
        elif args[idx] == "fen":
            fen = " ".join(args[idx + 1 : idx + 7])
            self.board.set_fen(fen)
            idx += 7
        else:
            return

        if idx < len(args) and args[idx] == "moves":
            idx += 1
            while idx < len(args):
                try:
                    self.board.push_uci(args[idx])
                except ValueError:
                    pass
                idx += 1

    def parse_go(self, _args):
        with suppress_output():
            result = self.search(self.board)

        if result.move:
            print(f"bestmove {result.move.uci()}")
        else:
            print(
                "bestmove 0000"
            )  # Indicates no legal moves (e.g., checkmate or stalemate)

    def handle_command(self, line: str):
        if not line.strip():
            return
        tokens = line.strip().split()
        command = tokens[0]

        if command == "uci":
            print("id name MyEngine")
            print("id author YourName")
            print("uciok")
        elif command == "isready":
            print("readyok")
        elif command == "ucinewgame":
            self.board.reset()
        elif command == "position":
            self.parse_position(tokens[1:])
        elif command == "go":
            self.parse_go(tokens[1:])
        elif command == "quit":
            sys.exit(0)
        else:
            pass  # Ignore unknown commands

    def loop(self):
        while True:
            try:
                line = input().strip()
                self.handle_command(line)
            except EOFError:
                break


if __name__ == "__main__":
    engine = UCIEngine(search)

    if len(sys.argv) > 1:
        # Run from command line args for quick testing
        for arg in sys.argv[1:]:
            engine.handle_command(arg)
    else:
        # Run UCI loop mode (stdin-based)
        engine.loop()
