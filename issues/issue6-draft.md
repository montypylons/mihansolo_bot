# Reproducing the bug: 

![alt text](image-5.png)
![alt text](image-6.png)
```bash
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

