# MihanSolo Engine

[![GitHub stars](https://img.shields.io/github/stars/YOUR_USERNAME/mihansolo_bot?style=social)](https://github.com/YOUR_USERNAME/mihansolo_bot)
[![Lichess Bot](https://img.shields.io/badge/Play%20on-Lichess-green?logo=lichess)](https://lichess.org/@/MihanSolo)

---

## 🧠 About

**MihanSolo** is a indie chess engine written in C++, using Negamax at depth 5 as well as quiescence search, PSQT, and MVV-LAA. (I know, its pretty bad right now) Around 1700 bullet and blitz on [Lichess](https://lichess.org/). Relies on magic_enum and Disservin's chess-lib.

---

## Play me

- 🔗 [Play vs @MihanSolo (latest build)](https://lichess.org/@/MihanSolo)
- 🔗 [Play vs @MihanSolo2, which is a older version than MihanSolo, used for testing](https://lichess.org/@/MihanSolo2)
- Use one of the releases, most contain prebuilt binaries and source code

---

## Features

- ⏱️ Written in C++ for speed
- 🚀 Quiescence search
- 🧮 PSQT and material eval
- 📦 UCI support
- 📊 Decently optimized
- ♜ Opening book (gm2600.bin)
  

---

## Build & Run

```bash
git clone https://github.com/montypylons/mihansolo_bot.git
cd mihansolo_bot
cmake -DCMAKE_BUILD_TYPE=Release -B build
cmake --build build --parallel
./build/engine
