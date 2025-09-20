$currentDate = Get-Date -Format "yyyy-MM-dd_HH__mm__ss"
cutechess-cli -debug all -engine cmd="../cmake-build-release/engine.exe" name=mihan1 -engine cmd="../cmake-build-release/engine.exe" name=mihan2 -each proto=uci tc=200/60 -rounds 20 -games 2 -pgnout "../logs/cutechess/tournament_${currentDate}.pgn"  | Tee-Object -FilePath "../logs/cutechess/debug_${currentDate}.log" -Append
