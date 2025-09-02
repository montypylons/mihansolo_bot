#!/usr/bin/env python3
import re
import sys

if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} <log_file>")
    sys.exit(1)

log_file = sys.argv[1]

seen = set()
lichess_urls = []

try:
    with open(log_file, "r") as f:
        for line in f:
            match = re.search(r'/game/([A-Za-z0-9]+)/move/', line)
            if match:
                game_id = match.group(1)
                if game_id not in seen:
                    seen.add(game_id)
                    lichess_urls.append(f"https://lichess.org/{game_id}")
except FileNotFoundError:
    print(f"File not found: {log_file}")
    sys.exit(1)

# Print each URL on its own line
for url in lichess_urls:
    print(url)
