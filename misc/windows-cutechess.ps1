
$currentDate = Get-Date -Format "yyyy-MM-dd_HH:mm:ss"
cutechess-cli -engine cmd="../cmake-build-release/engine.exe" name=mihan1 -engine cmd="../cmake-build-release/engine.exe" name=mihan2 -each proto=uci tc=200/60 -rounds 20 -games 2 -pgnout "../logs/cutechess/tournament_${currentDate}.pgn" -debug | Tee-Object -FilePath "../logs/cutechess/debug_${currentDate}.log" -Append
