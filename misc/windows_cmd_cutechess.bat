rem Get current date and time
for /f "tokens=1-4 delims=/- " %%a in ('date /t') do set currentDate=%%d-%%b-%%c
set currentTime=%time: =0%
set currentTime=%currentTime::=-%
set currentDateTime=%currentDate%_%currentTime%

rem Run cutechess-cli with formatted date and time
cutechess-cli -engine cmd="../cmake-build-release/engine.exe" name=mihan1 -engine cmd="../cmake-build-release/engine.exe" name=mihan2 -each proto=uci tc=200/60 -rounds 20 -games 2 -pgnout "../logs/cutechess/tournament_%currentDateTime%.pgn" >> "../logs/cutechess/debug_%currentDateTime%.log"
