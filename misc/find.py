import re

target_text: str = """
INFO     move: 1                                                                              lichess_bot.py:818
                    INFO     Searching for time 10 seconds for game n6wtAbkq                                   engine_wrapper.py:700
                    DEBUG    <UciProtocol (pid=6928)>: << ucinewgame                                                   engine.py:950
                    DEBUG    <UciProtocol (pid=6928)>: << isready                                                      engine.py:950
                    DEBUG    <UciProtocol (pid=6928)>: >> info string unknown command: ucinewgame                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> readyok                                                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos                                            engine.py:950
                    DEBUG    <UciProtocol (pid=6928)>: << go movetime 10000                                            engine.py:950
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove c2c4                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/c2c4?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'chatLine', 'room': 'player', 'username': 'MihanSolo', 'text':  lichess_bot.py:826
                             "Hi! I'm MihanSolo. I hope you Type !help for a list of commands I can respond to."}                   
                    INFO     *** https://lichess.org/n6wtAbkq/white [player] MihanSolo: Hi! I'm MihanSolo. I hope conversation.py:57
                             you Type !help for a list of commands I can respond to.                                                
                    DEBUG    Game state: {'type': 'chatLine', 'room': 'spectator', 'username': 'MihanSolo',       lichess_bot.py:826
                             'text': "Hi! I'm MihanSolo. Type !help for a list of commands I can respond to."}                      
                    INFO     *** https://lichess.org/n6wtAbkq/white [spectator] MihanSolo: Hi! I'm MihanSolo.     conversation.py:57
                             Type !help for a list of commands I can respond to.                                                    
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4', 'wtime': 60000, 'btime': 60000,   lichess_bot.py:826
                             'winc': 2000, 'binc': 2000, 'status': 'started'}                                                       
                    DEBUG    Game state: {'type': 'chatLine', 'room': 'player', 'username': 'mochi_bot', 'text':  lichess_bot.py:826
                             "Hi! I'm mochi_bot v. 20250722_1000. Good luck!"}                                                      
                    INFO     *** https://lichess.org/n6wtAbkq/white [player] mochi_bot: Hi! I'm mochi_bot v.      conversation.py:57
                             20250722_1000. Good luck!                                                                              
                    DEBUG    Game state: {'type': 'chatLine', 'room': 'spectator', 'username': 'mochi_bot',       lichess_bot.py:826
                             'text': "Hi! I'm mochi_bot v. 20250722_1000."}                                                         
                    INFO     *** https://lichess.org/n6wtAbkq/white [spectator] mochi_bot: Hi! I'm mochi_bot v.   conversation.py:57
                             20250722_1000.                                                                                         
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5', 'wtime': 60000, 'btime':     lichess_bot.py:826
                             60000, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                                
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 2                                                                              lichess_bot.py:818
                    INFO     Searching for wtime 58000 btime 60000 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << setoption name Ponder value true                             engine.py:950
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5                            engine.py:950
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 58000 btime 60000 winc 2000 binc 2000               engine.py:950
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove g1f3                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/g1f3?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3', 'wtime': 61890,         lichess_bot.py:826
                             'btime': 60000, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                       
[09/12/25 20:26:21] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4', 'wtime': 61890,    lichess_bot.py:826
                             'btime': 58060, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                       
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 3                                                                              lichess_bot.py:818
                    INFO     Searching for wtime 59890 btime 58060 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4                  engine.py:950
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 59890 btime 58060 winc 2000 binc 2000               engine.py:950
[09/12/25 20:26:25] DEBUG    <UciProtocol (pid=6928)>: >> info depth 7 nodes 8006526 score cp -65                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove f3d4                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.65                                                                 engine_wrapper.py:332
                    INFO     Depth: 7                                                                          engine_wrapper.py:332
                    INFO     Nodes: 8.0M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/f3d4?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4', 'wtime':      lichess_bot.py:826
                             59790, 'btime': 58060, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                
[09/12/25 20:26:29] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6', 'wtime': lichess_bot.py:826
                             59790, 'btime': 55470, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 4                                                                              lichess_bot.py:818
                    INFO     Searching for wtime 57790 btime 55470 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6        engine.py:950
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 57790 btime 55470 winc 2000 binc 2000               engine.py:950
[09/12/25 20:26:33] DEBUG    <UciProtocol (pid=6928)>: >> info depth 6 nodes 6312958 score cp -25                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove b1c3                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.25                                                                 engine_wrapper.py:332
                    INFO     Depth: 6                                                                          engine_wrapper.py:332
                    INFO     Nodes: 6.3M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/b1c3?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3',     lichess_bot.py:826
                             'wtime': 57800, 'btime': 55470, 'winc': 2000, 'binc': 2000, 'status': 'started'}                       
[09/12/25 20:26:37] DEBUG    Event: {'type': 'correspondence_ping'}                                               lichess_bot.py:447
[09/12/25 20:26:38] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3       lichess_bot.py:826
                             b8c6', 'wtime': 57800, 'btime': 53010, 'winc': 2000, 'binc': 2000, 'status':                           
                             'started'}                                                                                             
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 5                                                                              lichess_bot.py:818
                    INFO     Searching for wtime 55800 btime 53010 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6                                                                                                   
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 55800 btime 53010 winc 2000 binc 2000               engine.py:950
[09/12/25 20:26:42] DEBUG    <UciProtocol (pid=6928)>: >> info depth 7 nodes 5605009 score cp -30                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove e2e3                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.3                                                                  engine_wrapper.py:332
                    INFO     Depth: 7                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.6M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/e2e3?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3', 'wtime': 55900, 'btime': 53010, 'winc': 2000, 'binc': 2000, 'status':                           
                             'started'}                                                                                             
[09/12/25 20:26:45] DEBUG    Game state: {'type': 'chatLine', 'room': 'spectator', 'username': 'mapofdragons',    lichess_bot.py:826
                             'text': 'I eill destroy mochi'}                                                                        
                    INFO     *** https://lichess.org/n6wtAbkq/white [spectator] mapofdragons: I eill destroy      conversation.py:57
                             mochi                                                                                                  
[09/12/25 20:26:46] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4', 'wtime': 55900, 'btime': 50680, 'winc': 2000, 'binc': 2000, 'status':                      
                             'started'}                                                                                             
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 6                                                                              lichess_bot.py:818
                    INFO     Searching for wtime 53900 btime 50680 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4                                                                                         
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 53900 btime 50680 winc 2000 binc 2000               engine.py:950
[09/12/25 20:26:50] DEBUG    <UciProtocol (pid=6928)>: >> info depth 8 nodes 5740562 score cp -15                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove c3d5                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.15                                                                 engine_wrapper.py:332
                    INFO     Depth: 8                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.7M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/c3d5?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5', 'wtime': 54100, 'btime': 50680, 'winc': 2000, 'binc': 2000,                           
                             'status': 'started'}                                                                                   
[09/12/25 20:26:54] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5', 'wtime': 54100, 'btime': 48470, 'winc': 2000, 'binc': 2000,                      
                             'status': 'started'}                                                                                   
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 7                                                                              lichess_bot.py:818
                    INFO     Searching for wtime 52100 btime 48470 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5                                                                               
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 52100 btime 48470 winc 2000 binc 2000               engine.py:950
[09/12/25 20:26:58] DEBUG    <UciProtocol (pid=6928)>: >> info depth 8 nodes 6681885 score cp -15                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove c4d5                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.15                                                                 engine_wrapper.py:332
                    INFO     Depth: 8                                                                          engine_wrapper.py:332
                    INFO     Nodes: 6.7M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/c4d5?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5', 'wtime': 52390, 'btime': 48470, 'winc': 2000, 'binc':                       
                             2000, 'status': 'started'}                                                                             
[09/12/25 20:27:01] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4', 'wtime': 52390, 'btime': 47290, 'winc': 2000,                          
                             'binc': 2000, 'status': 'started'}                                                                     
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 8                                                                              lichess_bot.py:818
                    INFO     Searching for wtime 50390 btime 47290 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4                                                                     
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 50390 btime 47290 winc 2000 binc 2000               engine.py:950
[09/12/25 20:27:05] DEBUG    <UciProtocol (pid=6928)>: >> info depth 7 nodes 6414576 score cp -45                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove e3d4                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.45                                                                 engine_wrapper.py:332
                    INFO     Depth: 7                                                                          engine_wrapper.py:332
                    INFO     Nodes: 6.4M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/e3d4?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4', 'wtime': 50760, 'btime': 47290, 'winc': 2000,                     
                             'binc': 2000, 'status': 'started'}                                                                     
[09/12/25 20:27:09] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8', 'wtime': 50760, 'btime': 45240, 'winc':                      
                             2000, 'binc': 2000, 'status': 'started'}                                                               
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 9                                                                              lichess_bot.py:818
                    INFO     Searching for wtime 48760 btime 45240 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8                                                           
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 48760 btime 45240 winc 2000 binc 2000               engine.py:950
[09/12/25 20:27:12] DEBUG    <UciProtocol (pid=6928)>: >> info depth 6 nodes 5782492 score cp -5                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove a2a3                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.05                                                                 engine_wrapper.py:332
                    INFO     Depth: 6                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.8M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/a2a3?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3', 'wtime': 49210, 'btime': 45240,                         
                             'winc': 2000, 'binc': 2000, 'status': 'started'}                                                       
[09/12/25 20:27:15] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5', 'wtime': 49210, 'btime': 44240,                    
                             'winc': 2000, 'binc': 2000, 'status': 'started'}                                                       
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 10                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 47210 btime 44240 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5                                                 
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 47210 btime 44240 winc 2000 binc 2000               engine.py:950
[09/12/25 20:27:19] DEBUG    <UciProtocol (pid=6928)>: >> info depth 6 nodes 5623752 score cp 0                        engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove d1a4                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.0                                                                   engine_wrapper.py:332
                    INFO     Depth: 6                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.6M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/d1a4?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4', 'wtime': 47740, 'btime':                      
                             44240, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                                
[09/12/25 20:27:22] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6', 'wtime': 47740,                          
                             'btime': 42860, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                       
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 11                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 45740 btime 42860 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6                                       
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 45740 btime 42860 winc 2000 binc 2000               engine.py:950
[09/12/25 20:27:25] DEBUG    <UciProtocol (pid=6928)>: >> info depth 7 nodes 5232714 score cp -5                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove d5d6                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.05                                                                 engine_wrapper.py:332
                    INFO     Depth: 7                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.2M                                                                       engine_wrapper.py:332
[09/12/25 20:27:26] DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/d5d6?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6', 'wtime': 46270,                     
                             'btime': 42860, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                       
[09/12/25 20:27:29] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5', 'wtime':                       
                             46270, 'btime': 41030, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 12                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 44270 btime 41030 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5                             
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 44270 btime 41030 winc 2000 binc 2000               engine.py:950
[09/12/25 20:27:33] DEBUG    <UciProtocol (pid=6928)>: >> info depth 7 nodes 5079810 score cp 0                        engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove a4c2                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.0                                                                   engine_wrapper.py:332
                    INFO     Depth: 7                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.1M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/a4c2?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2',                           
                             'wtime': 44950, 'btime': 41030, 'winc': 2000, 'binc': 2000, 'status': 'started'}                       
[09/12/25 20:27:34] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8',                      
                             'wtime': 44950, 'btime': 42150, 'winc': 2000, 'binc': 2000, 'status': 'started'}                       
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 13                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 42950 btime 42150 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8                   
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 42950 btime 42150 winc 2000 binc 2000               engine.py:950
[09/12/25 20:27:37] DEBUG    <UciProtocol (pid=6928)>: >> info depth 6 nodes 4700653 score cp -15                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove a3a4                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.15                                                                 engine_wrapper.py:332
                    INFO     Depth: 6                                                                          engine_wrapper.py:332
                    INFO     Nodes: 4.7M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/a3a4?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8                        
                             a3a4', 'wtime': 43700, 'btime': 42150, 'winc': 2000, 'binc': 2000, 'status':                           
                             'started'}                                                                                             
[09/12/25 20:27:40] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4', 'wtime': 43700, 'btime': 40860, 'winc': 2000, 'binc': 2000, 'status':                           
                             'started'}                                                                                             
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 14                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 41700 btime 40860 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4                                                                                                   
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 41700 btime 40860 winc 2000 binc 2000               engine.py:950
[09/12/25 20:27:43] DEBUG    <UciProtocol (pid=6928)>: >> info depth 7 nodes 4961316 score cp -10                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove g2g3                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.1                                                                  engine_wrapper.py:332
                    INFO     Depth: 7                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.0M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/g2g3?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3', 'wtime': 42510, 'btime': 40860, 'winc': 2000, 'binc': 2000, 'status':                      
                             'started'}                                                                                             
[09/12/25 20:27:47] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3', 'wtime': 42510, 'btime': 39540, 'winc': 2000, 'binc': 2000,                           
                             'status': 'started'}                                                                                   
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 15                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 40510 btime 39540 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3                                                                                         
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 40510 btime 39540 winc 2000 binc 2000               engine.py:950
[09/12/25 20:27:50] DEBUG    <UciProtocol (pid=6928)>: >> info depth 9 nodes 5096049 score cp -35                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove f2e3                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.35                                                                 engine_wrapper.py:332
                    INFO     Depth: 9                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.1M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/f2e3?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3', 'wtime': 41380, 'btime': 39540, 'winc': 2000, 'binc': 2000,                      
                             'status': 'started'}                                                                                   
[09/12/25 20:27:53] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3', 'wtime': 41380, 'btime': 37880, 'winc': 2000, 'binc':                       
                             2000, 'status': 'started'}                                                                             
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 16                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 39379 btime 37880 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3                                                                               
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 39379 btime 37880 winc 2000 binc 2000               engine.py:950
[09/12/25 20:27:56] DEBUG    <UciProtocol (pid=6928)>: >> info depth 9 nodes 5000733 score cp -10                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove e1f2                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.1                                                                  engine_wrapper.py:332
                    INFO     Depth: 9                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.0M                                                                       engine_wrapper.py:332
[09/12/25 20:27:57] DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/e1f2?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2', 'wtime': 40290, 'btime': 37880, 'winc': 2000,                          
                             'binc': 2000, 'status': 'started'}                                                                     
[09/12/25 20:27:59] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3', 'wtime': 40290, 'btime': 37390, 'winc': 2000,                     
                             'binc': 2000, 'status': 'started'}                                                                     
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 17                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 38290 btime 37390 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3                                                                     
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 38290 btime 37390 winc 2000 binc 2000               engine.py:950
[09/12/25 20:28:02] DEBUG    <UciProtocol (pid=6928)>: >> info depth 8 nodes 4876096 score cp -35                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove h2g3                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.35                                                                 engine_wrapper.py:332
                    INFO     Depth: 8                                                                          engine_wrapper.py:332
                    INFO     Nodes: 4.9M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/h2g3?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3', 'wtime': 39260, 'btime': 37390, 'winc':                      
                             2000, 'binc': 2000, 'status': 'started'}                                                               
[09/12/25 20:28:05] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1', 'wtime': 39260, 'btime': 36400,                         
                             'winc': 2000, 'binc': 2000, 'status': 'started'}                                                       
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 18                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 37260 btime 36400 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1                                                           
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 37260 btime 36400 winc 2000 binc 2000               engine.py:950
[09/12/25 20:28:08] DEBUG    <UciProtocol (pid=6928)>: >> info depth 8 nodes 5117674 score cp -35                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove f1g2                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.35                                                                 engine_wrapper.py:332
                    INFO     Depth: 8                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.1M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/f1g2?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2', 'wtime': 38290, 'btime': 36400,                    
                             'winc': 2000, 'binc': 2000, 'status': 'started'}                                                       
[09/12/25 20:28:11] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5', 'wtime': 38290, 'btime':                      
                             35900, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                                
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 19                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 36290 btime 35900 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5                                                 
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 36290 btime 35900 winc 2000 binc 2000               engine.py:950
[09/12/25 20:28:13] DEBUG    <UciProtocol (pid=6928)>: >> info depth 7 nodes 5638574 score cp -20                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove a4b5                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.2                                                                  engine_wrapper.py:332
                    INFO     Depth: 7                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.6M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/a4b5?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5', 'wtime': 37370,                          
                             'btime': 35900, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                       
[09/12/25 20:28:15] DEBUG    Event: {'type': 'challenge', 'challenge': {'id': 'K5y2r3kp', 'url':                  lichess_bot.py:447
                             'https://lichess.org/K5y2r3kp', 'status': 'created', 'challenger': {'id':                              
                             'untrained4406', 'name': 'untrained4406', 'rating': 1563, 'title': 'BOT', 'flair':                     
                             'food-drink.spaghetti', 'online': True}, 'destUser': {'id': 'mihansolo', 'name':                       
                             'MihanSolo', 'rating': 1639, 'title': 'BOT', 'flair': 'nature.dragon-face',                            
                             'online': True}, 'variant': {'key': 'standard', 'name': 'Standard', 'short': 'Std'},                   
                             'rated': True, 'speed': 'bullet', 'timeControl': {'type': 'clock', 'limit': 60,                        
                             'increment': 2, 'show': '1+2'}, 'color': 'random', 'finalColor': 'white', 'perf':                      
                             {'icon': '\ue032', 'name': 'Bullet'}}, 'compat': {'bot': True, 'board': False}}                        
                    DEBUG    Resetting dropped connection: lichess.org                                         connectionpool.py:291
[09/12/25 20:28:16] DEBUG    https://lichess.org:443 "GET /api/account/playing HTTP/11" 200 None               connectionpool.py:546
                    DEBUG    https://lichess.org:443 "POST /api/challenge/K5y2r3kp/decline HTTP/11" 200 11     connectionpool.py:546
                    DEBUG    Event: {'type': 'challengeDeclined', 'challenge': {'id': 'K5y2r3kp', 'url':          lichess_bot.py:447
                             'https://lichess.org/K5y2r3kp', 'status': 'declined', 'challenger': {'id':                             
                             'untrained4406', 'name': 'untrained4406', 'rating': 1563, 'title': 'BOT', 'flair':                     
                             'food-drink.spaghetti', 'online': True}, 'destUser': {'id': 'mihansolo', 'name':                       
                             'MihanSolo', 'rating': 1639, 'title': 'BOT', 'flair': 'nature.dragon-face',                            
                             'online': True}, 'variant': {'key': 'standard', 'name': 'Standard', 'short': 'Std'},                   
                             'rated': True, 'speed': 'bullet', 'timeControl': {'type': 'clock', 'limit': 60,                        
                             'increment': 2, 'show': '1+2'}, 'color': 'random', 'finalColor': 'white', 'perf':                      
                             {'icon': '\ue032', 'name': 'Bullet'}, 'declineReason': "I'm not accepting challenges                   
                             from bots.", 'declineReasonKey': 'nobot'}}                                                             
                    INFO     BOT MihanSolo (1639) declined Bullet rated challenge from BOT untrained4406 (1563)   matchmaking.py:336
                             (K5y2r3kp): I'm not accepting challenges from bots.                                                    
[09/12/25 20:28:17] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5', 'wtime': 37370,                     
                             'btime': 34650, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                       
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 20                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 35370 btime 34650 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5                                       
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 35370 btime 34650 winc 2000 binc 2000               engine.py:950
[09/12/25 20:28:19] DEBUG    <UciProtocol (pid=6928)>: >> info depth 7 nodes 4807860 score cp -20                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove c2c5                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: -0.2                                                                  engine_wrapper.py:332
                    INFO     Depth: 7                                                                          engine_wrapper.py:332
                    INFO     Nodes: 4.8M                                                                       engine_wrapper.py:332
[09/12/25 20:28:20] DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/c2c5?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5', 'wtime':                       
                             36490, 'btime': 34650, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                
[09/12/25 20:28:22] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5',                           
                             'wtime': 36490, 'btime': 34120, 'winc': 2000, 'binc': 2000, 'status': 'started'}                       
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 21                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 34490 btime 34120 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5                             
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 34490 btime 34120 winc 2000 binc 2000               engine.py:950
[09/12/25 20:28:25] DEBUG    <UciProtocol (pid=6928)>: >> info depth 9 nodes 6430766 score cp 15                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove d4c5                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.15                                                                  engine_wrapper.py:332
                    INFO     Depth: 9                                                                          engine_wrapper.py:332
                    INFO     Nodes: 6.4M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/d4c5?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5',                      
                             'wtime': 35650, 'btime': 34120, 'winc': 2000, 'binc': 2000, 'status': 'started'}                       
[09/12/25 20:28:28] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5                        
                             a5d8', 'wtime': 35650, 'btime': 32720, 'winc': 2000, 'binc': 2000, 'status':                           
                             'started'}                                                                                             
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 22                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 33650 btime 32720 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 33650 btime 32720 winc 2000 binc 2000               engine.py:950
[09/12/25 20:28:31] DEBUG    <UciProtocol (pid=6928)>: >> info depth 7 nodes 7422961 score cp 15                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove d2d4                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.15                                                                  engine_wrapper.py:332
                    INFO     Depth: 7                                                                          engine_wrapper.py:332
                    INFO     Nodes: 7.4M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/d2d4?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4', 'wtime': 34850, 'btime': 32720, 'winc': 2000, 'binc': 2000, 'status':                           
                             'started'}                                                                                             
[09/12/25 20:28:34] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5', 'wtime': 34850, 'btime': 31400, 'winc': 2000, 'binc': 2000, 'status':                      
                             'started'}                                                                                             
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 23                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 32850 btime 31400 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5                                                                                                   
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 32850 btime 31400 winc 2000 binc 2000               engine.py:950
[09/12/25 20:28:37] DEBUG    <UciProtocol (pid=6928)>: >> info depth 7 nodes 5460385 score cp 35                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove f2f3                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.35                                                                  engine_wrapper.py:332
                    INFO     Depth: 7                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.5M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/f2f3?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3', 'wtime': 34100, 'btime': 31400, 'winc': 2000, 'binc': 2000,                           
                             'status': 'started'}                                                                                   
[09/12/25 20:28:39] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8', 'wtime': 34100, 'btime': 31430, 'winc': 2000, 'binc': 2000,                      
                             'status': 'started'}                                                                                   
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 24                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 32100 btime 31430 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8                                                                                         
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 32100 btime 31430 winc 2000 binc 2000               engine.py:950
[09/12/25 20:28:42] DEBUG    <UciProtocol (pid=6928)>: >> info depth 8 nodes 6063645 score cp 40                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove f3e4                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.4                                                                   engine_wrapper.py:332
                    INFO     Depth: 8                                                                          engine_wrapper.py:332
                    INFO     Nodes: 6.1M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/f3e4?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4', 'wtime': 33380, 'btime': 31430, 'winc': 2000, 'binc':                       
                             2000, 'status': 'started'}                                                                             
[09/12/25 20:28:45] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4', 'wtime': 33380, 'btime': 30800, 'winc': 2000,                          
                             'binc': 2000, 'status': 'started'}                                                                     
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 25                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 31380 btime 30800 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4                                                                               
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 31380 btime 30800 winc 2000 binc 2000               engine.py:950
[09/12/25 20:28:47] DEBUG    <UciProtocol (pid=6928)>: >> info depth 7 nodes 5948416 score cp 40                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove a1b1                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.4                                                                   engine_wrapper.py:332
                    INFO     Depth: 7                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.9M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/a1b1?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1', 'wtime': 32700, 'btime': 30800, 'winc': 2000,                     
                             'binc': 2000, 'status': 'started'}                                                                     
[09/12/25 20:28:50] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6', 'wtime': 32700, 'btime': 29580, 'winc':                      
                             2000, 'binc': 2000, 'status': 'started'}                                                               
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 26                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 30700 btime 29580 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6                                                                     
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 30700 btime 29580 winc 2000 binc 2000               engine.py:950
[09/12/25 20:28:53] DEBUG    <UciProtocol (pid=6928)>: >> info depth 8 nodes 5296519 score cp 15                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove c1e3                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.15                                                                  engine_wrapper.py:332
                    INFO     Depth: 8                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.3M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/c1e3?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3', 'wtime': 32060, 'btime': 29580,                         
                             'winc': 2000, 'binc': 2000, 'status': 'started'}                                                       
[09/12/25 20:28:56] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4', 'wtime': 32060, 'btime': 28420,                    
                             'winc': 2000, 'binc': 2000, 'status': 'started'}                                                       
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 27                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 30060 btime 28420 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4                                                           
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 30060 btime 28420 winc 2000 binc 2000               engine.py:950
[09/12/25 20:28:59] DEBUG    <UciProtocol (pid=6928)>: >> info depth 7 nodes 5483009 score cp 15                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove b1a1                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.15                                                                  engine_wrapper.py:332
                    INFO     Depth: 7                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.5M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/b1a1?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1', 'wtime': 31450, 'btime':                      
                             28420, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                                
[09/12/25 20:29:02] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2', 'wtime': 31450,                          
                             'btime': 27320, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                       
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 28                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 29449 btime 27320 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2                                                 
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 29449 btime 27320 winc 2000 binc 2000               engine.py:950
[09/12/25 20:29:04] DEBUG    <UciProtocol (pid=6928)>: >> info depth 8 nodes 5234694 score cp 25                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove a1a4                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.25                                                                  engine_wrapper.py:332
                    INFO     Depth: 8                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.2M                                                                       engine_wrapper.py:332
[09/12/25 20:29:05] DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/a1a4?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4', 'wtime': 30860,                     
                             'btime': 27320, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                       
[09/12/25 20:29:06] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2', 'wtime':                       
                             30860, 'btime': 27850, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 29                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 28859 btime 27850 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2                                       
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 28859 btime 27850 winc 2000 binc 2000               engine.py:950
[09/12/25 20:29:08] DEBUG    <UciProtocol (pid=6928)>: >> info depth 10 nodes 6363818 score cp 40                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove a4a8                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.4                                                                   engine_wrapper.py:332
                    INFO     Depth: 10                                                                         engine_wrapper.py:332
                    INFO     Nodes: 6.4M                                                                       engine_wrapper.py:332
[09/12/25 20:29:09] DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/a4a8?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8',                           
                             'wtime': 30300, 'btime': 27850, 'winc': 2000, 'binc': 2000, 'status': 'started'}                       
[09/12/25 20:29:11] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6',                      
                             'wtime': 30300, 'btime': 27300, 'winc': 2000, 'binc': 2000, 'status': 'started'}                       
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 30                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 28300 btime 27300 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6                             
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 28300 btime 27300 winc 2000 binc 2000               engine.py:950
[09/12/25 20:29:14] DEBUG    <UciProtocol (pid=6928)>: >> info depth 10 nodes 6006517 score cp 85                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove a8c8                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.85                                                                  engine_wrapper.py:332
                    INFO     Depth: 10                                                                         engine_wrapper.py:332
                    INFO     Nodes: 6.0M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/a8c8?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6                        
                             a8c8', 'wtime': 29780, 'btime': 27300, 'winc': 2000, 'binc': 2000, 'status':                           
                             'started'}                                                                                             
[09/12/25 20:29:17] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7', 'wtime': 29780, 'btime': 26330, 'winc': 2000, 'binc': 2000, 'status':                           
                             'started'}                                                                                             
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 31                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 27780 btime 26330 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8 g8h7                   
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 27780 btime 26330 winc 2000 binc 2000               engine.py:950
[09/12/25 20:29:19] DEBUG    <UciProtocol (pid=6928)>: >> info depth 9 nodes 5893815 score cp 65                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove c8c7                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.65                                                                  engine_wrapper.py:332
                    INFO     Depth: 9                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.9M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/c8c7?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7', 'wtime': 29280, 'btime': 26330, 'winc': 2000, 'binc': 2000, 'status':                      
                             'started'}                                                                                             
[09/12/25 20:29:22] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3', 'wtime': 29280, 'btime': 25330, 'winc': 2000, 'binc': 2000,                           
                             'status': 'started'}                                                                                   
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 32                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 27280 btime 25330 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8 g8h7 c8c7              
                             g2g3                                                                                                   
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 27280 btime 25330 winc 2000 binc 2000               engine.py:950
[09/12/25 20:29:24] DEBUG    <UciProtocol (pid=6928)>: >> info depth 9 nodes 5713779 score cp 55                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove c7d7                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.55                                                                  engine_wrapper.py:332
                    INFO     Depth: 9                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.7M                                                                       engine_wrapper.py:332
[09/12/25 20:29:25] DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/c7d7?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7', 'wtime': 28810, 'btime': 25330, 'winc': 2000, 'binc': 2000,                      
                             'status': 'started'}                                                                                   
[09/12/25 20:29:27] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4', 'wtime': 28810, 'btime': 24380, 'winc': 2000, 'binc':                       
                             2000, 'status': 'started'}                                                                             
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 33                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 26810 btime 24380 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8 g8h7 c8c7              
                             g2g3 c7d7 g3g4                                                                                         
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 26810 btime 24380 winc 2000 binc 2000               engine.py:950
[09/12/25 20:29:30] DEBUG    <UciProtocol (pid=6928)>: >> info depth 10 nodes 5817915 score cp 45                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove e4d3                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.45                                                                  engine_wrapper.py:332
                    INFO     Depth: 10                                                                         engine_wrapper.py:332
                    INFO     Nodes: 5.8M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/e4d3?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3', 'wtime': 28370, 'btime': 24380, 'winc': 2000,                          
                             'binc': 2000, 'status': 'started'}                                                                     
[09/12/25 20:29:33] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6', 'wtime': 28370, 'btime': 23480, 'winc': 2000,                     
                             'binc': 2000, 'status': 'started'}                                                                     
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 34                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 26370 btime 23480 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8 g8h7 c8c7              
                             g2g3 c7d7 g3g4 e4d3 h7g6                                                                               
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 26370 btime 23480 winc 2000 binc 2000               engine.py:950
[09/12/25 20:29:35] DEBUG    <UciProtocol (pid=6928)>: >> info depth 9 nodes 5591323 score cp 35                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove d7c7                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.35                                                                  engine_wrapper.py:332
                    INFO     Depth: 9                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.6M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/d7c7?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7', 'wtime': 27890, 'btime': 23480, 'winc':                      
                             2000, 'binc': 2000, 'status': 'started'}                                                               
[09/12/25 20:29:36] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3', 'wtime': 27890, 'btime': 24380,                         
                             'winc': 2000, 'binc': 2000, 'status': 'started'}                                                       
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 35                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 25890 btime 24380 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8 g8h7 c8c7              
                             g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3                                                                     
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 25890 btime 24380 winc 2000 binc 2000               engine.py:950
[09/12/25 20:29:39] DEBUG    <UciProtocol (pid=6928)>: >> info depth 8 nodes 5755467 score cp 5                        engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove d3e2                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.05                                                                  engine_wrapper.py:332
                    INFO     Depth: 8                                                                          engine_wrapper.py:332
                    INFO     Nodes: 5.8M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/d3e2?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2', 'wtime': 27490, 'btime': 24380,                    
                             'winc': 2000, 'binc': 2000, 'status': 'started'}                                                       
[09/12/25 20:29:42] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5', 'wtime': 27490, 'btime':                      
                             23480, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                                
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 36                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 25490 btime 23480 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8 g8h7 c8c7              
                             g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5                                                           
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 25490 btime 23480 winc 2000 binc 2000               engine.py:950
[09/12/25 20:29:44] DEBUG    <UciProtocol (pid=6928)>: >> info depth 9 nodes 7623792 score cp 45                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove e3g5                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.45                                                                  engine_wrapper.py:332
                    INFO     Depth: 9                                                                          engine_wrapper.py:332
                    INFO     Nodes: 7.6M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/e3g5?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5', 'wtime': 27110,                          
                             'btime': 23480, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                       
[09/12/25 20:29:47] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5', 'wtime': 27110,                     
                             'btime': 22620, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                       
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 37                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 25110 btime 22620 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8 g8h7 c8c7              
                             g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5                                                 
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 25110 btime 22620 winc 2000 binc 2000               engine.py:950
[09/12/25 20:29:49] DEBUG    <UciProtocol (pid=6928)>: >> info depth 9 nodes 7768140 score cp 55                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove c7c6                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.55                                                                  engine_wrapper.py:332
                    INFO     Depth: 9                                                                          engine_wrapper.py:332
                    INFO     Nodes: 7.8M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/c7c6?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6', 'wtime':                       
                             26750, 'btime': 22620, 'winc': 2000, 'binc': 2000, 'status': 'started'}                                
[09/12/25 20:29:50] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6',                           
                             'wtime': 26750, 'btime': 23660, 'winc': 2000, 'binc': 2000, 'status': 'started'}                       
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 38                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 24750 btime 23660 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8 g8h7 c8c7              
                             g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6                                       
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 24750 btime 23660 winc 2000 binc 2000               engine.py:950
[09/12/25 20:29:53] DEBUG    <UciProtocol (pid=6928)>: >> info depth 10 nodes 7901703 score cp 125                     engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove d6d7                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 1.25                                                                  engine_wrapper.py:332
                    INFO     Depth: 10                                                                         engine_wrapper.py:332
                    INFO     Nodes: 7.9M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/d6d7?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7',                      
                             'wtime': 26410, 'btime': 23660, 'winc': 2000, 'binc': 2000, 'status': 'started'}                       
[09/12/25 20:29:55] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7                        
                             f6e7', 'wtime': 26410, 'btime': 22790, 'winc': 2000, 'binc': 2000, 'status':                           
                             'started'}                                                                                             
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 39                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 24409 btime 22790 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8 g8h7 c8c7              
                             g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7                             
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 24409 btime 22790 winc 2000 binc 2000               engine.py:950
[09/12/25 20:29:58] DEBUG    <UciProtocol (pid=6928)>: >> info depth 9 nodes 7696236 score cp 95                       engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove c6d6                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.95                                                                  engine_wrapper.py:332
                    INFO     Depth: 9                                                                          engine_wrapper.py:332
                    INFO     Nodes: 7.7M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/c6d6?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7                   
                             c6d6', 'wtime': 26080, 'btime': 22790, 'winc': 2000, 'binc': 2000, 'status':                           
                             'started'}                                                                                             
[09/12/25 20:29:59] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7                   
                             c6d6 e7d8', 'wtime': 26080, 'btime': 23190, 'winc': 2000, 'binc': 2000, 'status':                      
                             'started'}                                                                                             
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 40                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 24080 btime 23190 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8 g8h7 c8c7              
                             g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7 c6d6 e7d8                   
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 24080 btime 23190 winc 2000 binc 2000               engine.py:950
[09/12/25 20:30:02] DEBUG    <UciProtocol (pid=6928)>: >> info depth 9 nodes 7050046 score cp 120                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove c5c6                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 1.2                                                                   engine_wrapper.py:332
                    INFO     Depth: 9                                                                          engine_wrapper.py:332
                    INFO     Nodes: 7.1M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/c5c6?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7                   
                             c6d6 e7d8 c5c6', 'wtime': 25770, 'btime': 23190, 'winc': 2000, 'binc': 2000,                           
                             'status': 'started'}                                                                                   
[09/12/25 20:30:03] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7                   
                             c6d6 e7d8 c5c6 g5g2', 'wtime': 25770, 'btime': 23800, 'winc': 2000, 'binc': 2000,                      
                             'status': 'started'}                                                                                   
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 41                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 23770 btime 23800 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8 g8h7 c8c7              
                             g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7 c6d6 e7d8 c5c6              
                             g5g2                                                                                                   
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 23770 btime 23800 winc 2000 binc 2000               engine.py:950
[09/12/25 20:30:05] DEBUG    <UciProtocol (pid=6928)>: >> info depth 9 nodes 7027332 score cp 630                      engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove e2d3                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 6.3                                                                   engine_wrapper.py:332
                    INFO     Depth: 9                                                                          engine_wrapper.py:332
                    INFO     Nodes: 7.0M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/e2d3?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7                   
                             c6d6 e7d8 c5c6 g5g2 e2d3', 'wtime': 25460, 'btime': 23800, 'winc': 2000, 'binc':                       
                             2000, 'status': 'started'}                                                                             
[09/12/25 20:30:08] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7                   
                             c6d6 e7d8 c5c6 g5g2 e2d3 g2b2', 'wtime': 25460, 'btime': 23030, 'winc': 2000,                          
                             'binc': 2000, 'status': 'started'}                                                                     
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 42                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 23460 btime 23030 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8 g8h7 c8c7              
                             g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7 c6d6 e7d8 c5c6              
                             g5g2 e2d3 g2b2                                                                                         
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 23460 btime 23030 winc 2000 binc 2000               engine.py:950
[09/12/25 20:30:10] DEBUG    <UciProtocol (pid=6928)>: >> info depth 10 nodes 7287376 score cp 800                     engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove c6c7                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 8.0                                                                   engine_wrapper.py:332
                    INFO     Depth: 10                                                                         engine_wrapper.py:332
                    INFO     Nodes: 7.3M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/c6c7?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7                   
                             c6d6 e7d8 c5c6 g5g2 e2d3 g2b2 c6c7', 'wtime': 25180, 'btime': 23030, 'winc': 2000,                     
                             'binc': 2000, 'status': 'started'}                                                                     
[09/12/25 20:30:13] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7                   
                             c6d6 e7d8 c5c6 g5g2 e2d3 g2b2 c6c7 d8c7', 'wtime': 25180, 'btime': 22690, 'winc':                      
                             2000, 'binc': 2000, 'status': 'started'}                                                               
                    INFO                                                                                          lichess_bot.py:817
                    INFO     move: 43                                                                             lichess_bot.py:818
                    INFO     Searching for wtime 23180 btime 22690 for game n6wtAbkq                           engine_wrapper.py:722
                    DEBUG    <UciProtocol (pid=6928)>: << position startpos moves c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3   engine.py:950
                             b8c6 e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4              
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3                                                                                h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8 d2d4              
                             a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8 g8h7 c8c7              
                             g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7 c6d6 e7d8 c5c6              
                             g5g2 e2d3 g2b2 c6c7 d8c7
                    DEBUG    <UciProtocol (pid=6928)>: << go wtime 23180 btime 22690 winc 2000 binc 2000               engine.py:950
[09/12/25 20:30:15] DEBUG    <UciProtocol (pid=6928)>: >> info depth 9 nodes 8097373 score cp 0                        engine.py:976
                    DEBUG    <UciProtocol (pid=6928)>: >> bestmove d6d5                                                engine.py:976
                    INFO     Source: Engine                                                                    engine_wrapper.py:332
                    INFO     Evaluation: 0.0                                                                   engine_wrapper.py:332
                    INFO     Depth: 9                                                                          engine_wrapper.py:332
                    INFO     Nodes: 8.1M                                                                       engine_wrapper.py:332
                    DEBUG    https://lichess.org:443 "POST /api/bot/game/n6wtAbkq/move/d6d5?offeringDraw=false connectionpool.py:546
                             HTTP/11" 200 11                                                                                        
                    DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7                   
                             c6d6 e7d8 c5c6 g5g2 e2d3 g2b2 c6c7 d8c7 d6d5', 'wtime': 24910, 'btime': 22690,                         
                             'winc': 2000, 'binc': 2000, 'status': 'started'}                                                       
[09/12/25 20:30:18] DEBUG    Game state: {'type': 'gameState', 'moves': 'c2c4 e7e5 g1f3 e5e4 f3d4 g8f6 b1c3 b8c6  lichess_bot.py:826
                             e2e3 f8b4 c3d5 f6d5 c4d5 c6d4 e3d4 e8g8 a2a3 b4a5 d1a4 c7c6 d5d6 b7b5 a4c2 f8e8 a3a4                   
                             d8h4 g2g3 e4e3 f2e3 e8e3 e1f2 e3g3 h2g3 h4h1 f1g2 h1h5 a4b5 h5b5 c2c5 b5c5 d4c5 a5d8                   
                             d2d4 a7a5 f2f3 a8b8 f3e4 b8b4 a1b1 d8f6 c1e3 a5a4 b1a1 b4b2 a1a4 b2g2 a4a8 h7h6 a8c8                   
                             g8h7 c8c7 g2g3 c7d7 g3g4 e4d3 h7g6 d7c7 g4g3 d3e2 f6g5 e3g5 g3g5 c7c6 g6f6 d6d7 f6e7                   
                             c6d6 e7d8 c5c6 g5g2 e2d3 g2b2 c6c7 d8c7 d6d5 c7d8', 'wtime': 24910, 'btime': 21870,                    
                             'winc': 2000, 'binc': 2000, 'status': 'started'}                                                       
                    INFO                                                                                          lichess_bot.py:817
                    """


# Regex to match blocks after '<<' and before the next DEBUG or INFO
pattern = re.compile(
    r"<<([\s\S]*?)(?=\n\s*(?:DEBUG|INFO))"
)
timestamp_regex = re.compile(r"\[\d{2}/\d{2}/\d{2} \d{2}:\d{2}:\d{2}\]")

def extract_UCI(text):
    text = re.sub(timestamp_regex, "", text)
    matches = pattern.findall(text)
    cleaned = []
    for match in matches:
        match = match.replace("engine.py:950","")
        match = match.replace("engine.py:976","")

        cleaned.append(match)
    return cleaned

if __name__ == "__main__":
    for match in extract_UCI(target_text):
        print(match)