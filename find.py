#!/usr/bin/env python3
import re
import sys

def extract_move_block(log: str, gameid: str, move_number: int):
    pattern = re.compile(
        rf'^[^\n]*INFO move: {move_number}\n'               
        rf'(?:[^\n]*\n)*?'                                   
        rf'[^\n]*INFO Searching for .*?for game {re.escape(gameid)}\n' 
        rf'(?:[^\n]*\n)*?'                                
        rf'[^\n]*>> bestmove [^\n]*',                        
        re.M
    )
    match = pattern.search(log)
    return match.group(0) if match else None

def extract_all_UCI_blocks_upto_move(log: str, gameid: str, move_number: int):
    for i in range(1, move_number + 1):
        block = extract_move_block(log, gameid, i)
        if block:
            extract_UCI(block)
        else:
            print(f"(No block found for game {gameid}, move {i})")

def extract_UCI(block: str):
    pattern = r"DEBUG <UciProtocol \(pid=\d+\)>: <<\s(.*)"
    matches = re.findall(pattern, block)
    for match in matches:
        print(match)

def main():
    if len(sys.argv) < 4:
        print(f"Usage: {sys.argv[0]} <logfile> <gameid> <move_number> [--all]")
        sys.exit(1)

    logfile = sys.argv[1]
    gameid = sys.argv[2]
    move_number = int(sys.argv[3])
    get_all = '--all' in sys.argv[4:]

    with open(logfile, "r", encoding="utf-8") as f:
        log = f.read()

    if get_all:
        extract_all_UCI_blocks_upto_move(log, gameid, move_number)
    else:
        block = extract_move_block(log, gameid, move_number)
        if block:
            extract_UCI(block)
        else:
            print(f"(No block found for game {gameid}, move {move_number})")

if __name__ == "__main__":
    main()
