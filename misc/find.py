import re


# Regex to match blocks after '<<' and before the next DEBUG or INFO
pattern = re.compile(
    r"<<([\s\S]*?)(?=\n\s*(?:DEBUG|INFO))"
)
timestamp_regex = re.compile(r"\[\d{2}/\d{2}/\d{2} \d{2}:\d{2}:\d{2}\]")
moves_regexes = [re.compile("move: ."), re.compile("move: .."), re.compile("move: ...")]
game_regex = r""

searching_regex = r"Searching for wtime (?<=\s)\d+(?=\s) btime "
wtime_btime_regex = re.compile(pattern = r"(?<=\s)\d+(?=\s)")


def get_game_text_for_moves(file_path, game_id: str, starting_move: str, end_move: str) -> str:
    with open(file_path, "r") as f:
        content = f.read()


def extract_UCI(file_path: str) -> list:
    with open(file_path,"r") as f:
        content = f.read()
        content = re.sub(timestamp_regex, "", content)
        matches = pattern.findall(content)
        cleaned = []
        for match in matches:
            match = match.replace("engine.py:950","")
            match = match.replace("engine.py:976","")

            cleaned.append(match)
        return cleaned

if __name__ == "__main__":
    for match in extract_UCI(target_text):
        print(match)