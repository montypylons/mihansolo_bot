# MihanSolo

[![GitHub stars](https://img.shields.io/github/stars/montypylons/mihansolo_bot?style=social)](https://github.com/YOUR_USERNAME/mihansolo_bot)
[![Lichess](https://img.shields.io/badge/Play%20on-Lichess-green?logo=lichess)](https://lichess.org/@/MihanSolo)

---

## About mihansolo

**MihanSolo** is my first chess engine (written in C++); it uses an HCE (hand-crafted evaluation) and Negamax search with alpha/beta and quiescence. I can only add new features occasionally now that school starts soon :(, but its ok as it is. Around 1700 bullet and blitz on [Lichess](https://lichess.org/). Uses Disservin's chess-lib for movegen, checkmate detection, all the nitty-gritty details.

---

## Play 

- [Play vs @MihanSolo (latest build)](https://lichess.org/@/MihanSolo)
   [Play vs @MihanSolo2, which is a older version than MihanSolo, used for testing](https://lichess.org/@/MihanSolo2)
- Use one of the releases, most contain prebuilt binaries and source code

---

## Features

# Evaluation
- Piece-square tables
- Material eval
- Middlegame/endgame eval changes (currently only for kings and pawns)
# Search
- Quiescence search
- Delta pruning
- Alpha/beta pruning
- Stand pat pruning
- Transposition table (currently hard-set at 2^23 entries)
- Evaluation hash table (also hard coded at 2^23 entries)
# UCI
- Partial UCI support, just enough to get it working on Lichess. :D
  

## Acknowledgements
- Disservin's [chess-lib](https://github.com/Disservin/chess-library)
- [Cutechess](https://github.com/cutechess/cutechess)
- [Hack Club](hackclub.com) For giving me the motivation to build this with their excellent Summer Of Making program
- [Chess Programming Wiki](https://www.chessprogramming.org/Main_Page)
- [Engine Programming Discord](https://discord.com/invite/F6W6mMsTGN)
- [Stockfish Discord](https://discord.com/invite/GWDRS3kU6R)
- [Lichess](https://lichess.org)
  
