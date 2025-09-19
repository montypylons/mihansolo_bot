# Reproducing the bug: 

![alt text](image-5.png)
![alt text](image-6.png)

## Commands without annotations (in a cpp compatible format): 
```cpp
constexpr auto uci_commands = "position startpos moves e2e4\n"
"isready\n"
"go wtime 296248 btime 303000 winc 3000 binc 3000\n"
"position startpos moves e2e4 g7g6 g1f3\n"
"go wtime 286448 btime 306000 winc 3000 binc 3000\n"
"position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4\n"
"go wtime 286448 btime 309000 winc 3000 binc 3000\n"
"position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4 f8g7 f1d3\n"
"go wtime 333 btime 312000 winc 3000 binc 3000\n"
"position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4 f8g7 f1d3 g8f6 e1g1\n"
"go wtime 99 btime 298000 winc 3000 binc 3000\n"
"position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4 f8g7 f1d3 g8f6 e1g1 e8g8 c1e3\n"
"go wtime 99 btime 301000 winc 3000 binc 3000\n"
"position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4 f8g7 f1d3 g8f6 e1g1 e8g8 c1e3 b8d7 b1c3\n"
"go wtime 99 btime 287000 winc 3000 binc 3000\n"
"position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4 f8g7 f1d3 g8f6 e1g1 e8g8 c1e3 b8d7 b1c3 e7e5 a2a3\n"
"go wtime 99 btime 274000 winc 3000 binc 3000\n"
"position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4 f8g7 f1d3 g8f6 e1g1 e8g8 c1e3 b8d7 b1c3 e7e5 a2a3 e5d4 e3d4\n"
"go wtime 99 btime 262000 winc 3000 binc 3000";

```
## With annotations: 
```powershell
position startpos moves e2e4
isready
readyok
go wtime 296248 btime 303000 winc 3000 binc 3000
[ bestmove g7g6 ]
position startpos moves e2e4 g7g6 g1f3
go wtime 286448 btime 306000 winc 3000 binc 3000
[ bestmove d7d6 ]
position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4
go wtime 286448 btime 309000 winc 3000 binc 3000
[ bestmove f8g7 ]
position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4 f8g7 f1d3
go wtime 333 btime 312000 winc 3000 binc 3000 
[ bestmove g8f6 ]
[ took 17 000 ms ]
position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4 f8g7 f1d3 g8f6 e1g1
go wtime 99 btime 298000 winc 3000 binc 3000
[ bestmove e8g8 ]
[ took 0 ms ]
position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4 f8g7 f1d3 g8f6 e1g1 e8g8 c1e3
go wtime 99 btime 301000 winc 3000 binc 3000
[ bestmove b8d7 ] 
[ took 17 000 ms]
position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4 f8g7 f1d3 g8f6 e1g1 e8g8 c1e3 b8d7 b1c3
go wtime 99 btime 287000 winc 3000 binc 3000
[ bestmove e7e5 ]
[ took 16 000 ms]
position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4 f8g7 f1d3 g8f6 e1g1 e8g8 c1e3 b8d7 b1c3 e7e5 a2a3
go wtime 99 btime 274000 winc 3000 binc 3000 

position startpos moves e2e4 g7g6 g1f3 d7d6 d2d4 f8g7 f1d3 g8f6 e1g1 e8g8 c1e3 b8d7 b1c3 e7e5 a2a3 e5d4 e3d4
go wtime 99 btime 262000 winc 3000 binc 3000
```