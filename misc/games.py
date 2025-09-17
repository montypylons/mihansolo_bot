#!/usr/bin/env python3
import re
import sys

if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} <log_file>")
    sys.exit(1)

log_file = sys.argv[1]

# Pattern to match 8-char game ID
pattern = re.compile(r"IDs: \{'([A-Za-z0-9]{8})'\}")

def find_gameids(log: str, game_ids) -> list:
    with open(log, "r", encoding="utf-16") as f:
            log_content = f.read()    
            matches = pattern.findall(log_content)
            for match in matches:
                if match not in game_ids:
                    game_ids.append(match)

game_ids = []
find_gameids(log_file, game_ids)

for game_id in game_ids:
    print(f"https://lichess.org/{game_id}")
