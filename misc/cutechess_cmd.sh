cutechess-cli.exe `
  -engine cmd="C:\Users\DELL\Documents\mihansolo_bot\cmake-build-release\engine.exe" name=mihan `
  -engine cmd="C:\Users\DELL\Documents\mihansolo_bot\cmake-build-release\engine.exe" name=Komodo `
  -each proto=uci tc=1+2 `
  -rounds 10 -games 2 `
  -pgnout tourney_9_18_2025.pgn `
  -debug
