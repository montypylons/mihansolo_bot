**Describe the bug**
It misses mate in one twice then proceeds to lose.

<img width="1318" height="463" alt="Image" src="https://github.com/user-attachments/assets/6d49769d-0c8c-405b-afdd-d779e8df0728" />

**To Reproduce**
Steps to reproduce the behavior:


<details>
<summary>Run the following UCI commands</summary>

```powershell
.\engine.exe
ucinewgame
isready
position startpos moves e2e3
go movetime 10000
setoption name Ponder value true
position startpos moves e2e3 b8c6 b1c3
go wtime 60470 btime 57999 winc 1000 binc 1000
position startpos moves e2e3 b8c6 b1c3 e7e5 d1g4
go wtime 61290 btime 55489 winc 1000 binc 1000
position startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4
go wtime 62100 btime 53109 winc 1000 binc 1000
position startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4 d7d5 c4a4
go wtime 62910 btime 50849 winc 1000 binc 1000
position startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4 d7d5 c4a4 d5d4 c3d1
go wtime 63710 btime 48699 winc 1000 binc 1000
position startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4 d7d5 c4a4 d5d4 c3d1 f8c5 g1f3
go wtime 64520 btime 46659 winc 1000 binc 1000
position startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4 d7d5 c4a4 d5d4 c3d1 f8c5 g1f3 e8g8 b2b3
go wtime 65330 btime 44719 winc 1000 binc 1000
position startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4 d7d5 c4a4 d5d4 c3d1 f8c5 g1f3 e8g8 b2b3 c6b4 c2c3
go wtime 66130 btime 42879 winc 1000 binc 1000
position startpos moves e2e3 b8c6 b1c3 e7e5 d1g4 g8f6 g4c4 d7d5 c4a4 d5d4 c3d1 f8c5 g1f3 e8g8 b2b3 c6b4 c2c3 b4c2 e1e2
go wtime 66950 btime 41129 winc 1000 binc 1000
```

</details> 


**Expected behavior**
For the engine to find the mate in 1, `d4d3`.

**Desktop (please complete the following information):**

- OS: Windows 22H2
- C++ Version: C++ 17
- Terminal: Powershell

**Additional context**
Maybe transposition table issue, because when we give the rest of the UCI commands (not just the one for move 10), 