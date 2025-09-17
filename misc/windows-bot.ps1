
# Get current date in M_d_yyyy format
$currentDate = Get-Date -Format "M_d_yyyy"

# Define log file name
$logFile = "$currentDate.log"
cd ../lichess-bot
python lichess-bot.py -v --config ../config/windows-accept-bot.yml | Tee-Object -FilePath ../logs/windows/$logFile -Append
