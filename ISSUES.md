# Issues

## [Game uPddlrCS](https://lichess.org/uPddlrCS)

### Relevant section of lichess-bot logs

``` INFO     move: 49
INFO     Searching for wtime 125250 btime 15019 for game uPddlrCS
DEBUG    <UciProtocol (pid=21188)>: << position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7 d8c8 d7d5 g5e6 d5d7 a8a7 c1d1
a7c7 d7c7 c8c7 d1d6 g8f8 d6a6 c7c3 a6a8 f8e7 a8a7 e7f6 a7a6 f6e5 a6a5 e5e4 a5a4 e4e5 a4a5
go wtime 125250 btime 15019 winc 1000 binc 1000
DEBUG    <UciProtocol (pid=21188)>: >> bestmove 0000 ```

### What is the issue?

- Engine returning bestmove 0000 and consequently timing out

<details>
  <summary>How to reproduce</summary>

```ucinewgame
isready
position startpos moves c2c4
go movetime 10000

setoption name Ponder value true
position startpos moves c2c4 e7e5 d2d3
go wtime 90950 btime 88000 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3
go wtime 91860 btime 84000 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
go wtime 92810 btime 80189 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4
go wtime 93620 btime 76580 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4
go wtime 94460 btime 73149 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3
go wtime 95300 btime 69890 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2
go wtime 96130 btime 66790 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1
go wtime 96950 btime 63840 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2
go wtime 97750 btime 61039 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2
go wtime 98560 btime 58390 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1
go wtime 99380 btime 55870 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
go wtime 100150 btime 53469 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3
go wtime 100910 btime 51189 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3
go wtime 101710 btime 49030 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2
go wtime 102510 btime 46980 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1
go wtime 103280 btime 45030 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3
go wtime 104090 btime 43169 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4
go wtime 104840 btime 41409 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2
go wtime 105610 btime 39739 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2
go wtime 106370 btime 38149 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
go wtime 107150 btime 36639 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3
go wtime 107900 btime 35199 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1
go wtime 108670 btime 33839 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2
go wtime 109410 btime 32540 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4
go wtime 110130 btime 31310 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3
go wtime 110880 btime 30140 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2
go wtime 111590 btime 29030 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5
go wtime 112330 btime 27969 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6
go wtime 112970 btime 26879 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
go wtime 113710 btime 25929 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1
go wtime 114410 btime 25019 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7
go wtime 115130 btime 24159 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7
go wtime 115830 btime 23339 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7
go wtime 116490 btime 22569 winc 1000 binc 1000
position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7
go wtime 117180 btime 21839 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7
go wtime 117870 btime 21139 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7 d8c8 d7d5
go wtime 118490 btime 20470 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7 d8c8 d7d5 g5e6 d5d7
go wtime 119060 btime 19840 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7 d8c8 d7d5 g5e6 d5d7 a8a7 c1d1
go wtime 119730 btime 19239 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7 d8c8 d7d5 g5e6 d5d7 a8a7 c1d1
a7c7 d7c7
go wtime 120370 btime 18670 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7 d8c8 d7d5 g5e6 d5d7 a8a7 c1d1
a7c7 d7c7 c8c7 d1d6
go wtime 121030 btime 18130 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7 d8c8 d7d5 g5e6 d5d7 a8a7 c1d1
a7c7 d7c7 c8c7 d1d6 g8f8 d6a6
go wtime 121680 btime 17609 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7 d8c8 d7d5 g5e6 d5d7 a8a7 c1d1
a7c7 d7c7 c8c7 d1d6 g8f8 d6a6 c7c3 a6a8
go wtime 122290 btime 17119 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7 d8c8 d7d5 g5e6 d5d7 a8a7 c1d1
a7c7 d7c7 c8c7 d1d6 g8f8 d6a6 c7c3 a6a8 f8e7 a8a7
go wtime 122870 btime 16660 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7 d8c8 d7d5 g5e6 d5d7 a8a7 c1d1
a7c7 d7c7 c8c7 d1d6 g8f8 d6a6 c7c3 a6a8 f8e7 a8a7 e7f6 a7a6
go wtime 123500 btime 16220 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7 d8c8 d7d5 g5e6 d5d7 a8a7 c1d1
a7c7 d7c7 c8c7 d1d6 g8f8 d6a6 c7c3 a6a8 f8e7 a8a7 e7f6 a7a6 f6e5 a6a5
go wtime 124060 btime 15800 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7 d8c8 d7d5 g5e6 d5d7 a8a7 c1d1
a7c7 d7c7 c8c7 d1d6 g8f8 d6a6 c7c3 a6a8 f8e7 a8a7 e7f6 a7a6 f6e5 a6a5 e5e4 a5a4
go wtime 124650 btime 15400 winc 1000 binc 1000

position startpos moves c2c4 e7e5 d2d3 b8c6 g1f3 g8f6 a2a3
f8c5 b2b4 c5d4 f3d4 e5d4 g2g3 d7d5 f1g2 c8f5 e1g1 e8g8 b1d2 f8e8 c1b2 f5g4 f1e1 d8d6 c4c5
d6e5 d2f3 g4f3 g2f3 e5f5 f3g2 f6g4 e1f1 f5h5 h2h3 g4f6 g3g4 h5e5 d1d2 e5e2 d2e2 e8e2 a1b1
a8d8 g2f3 e2d2 f1d1 c6e5 f3g2 d2d3 b2d4 e5f3 g2f3 d3f3 g1g2 f3a3 b4b5 f6e4 c5c6 b7c6 b5c6
a3a6 d1c1 a6a4 d4a7 a4a7 b1b7 a7a2 b7c7 a2a8 c7d7 e4g5 c6c7 d8c8 d7d5 g5e6 d5d7 a8a7 c1d1
a7c7 d7c7 c8c7 d1d6 g8f8 d6a6 c7c3 a6a8 f8e7 a8a7 e7f6 a7a6 f6e5 a6a5 e5e4 a5a4 e4e5 a4a5
go wtime 125250 btime 15019 winc 1000 binc 1000```


</details>
