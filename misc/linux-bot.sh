#!/bin/bash


current_date=$(date +"%m_%d_%Y")

echo "Starting lichess-bot"

python ../lichess-bot/lichess-bot.py --config ../config/linux-config.yml > "${current_date}.log"