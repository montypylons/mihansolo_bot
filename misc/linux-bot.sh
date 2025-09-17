#!/bin/bash

current_date=$(date +"%m_%d_%Y")

echo "Starting lichess-bot"

cd ../lichess-bot
python lichess-bot.py -v --config ../config/linux-config.yml > "../logs/linux/${current_date}.log"