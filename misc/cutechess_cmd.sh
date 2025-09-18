#!/bin/bash

date_time = $(date +"%Y-%m-%d_%H:%M:%S")

cutechess-cli \
  -engine cmd="../build/engine" name=mihan1 \
  -engine cmd="../build/engine" name=mihan2 \
  -each proto=uci tc=1+2 \
  -rounds 10 -games 2 \
  -pgnout ../logs/cutechess/tournament_$(date_time).pgn \
  -debug > ../logs/cutechess/debug_$(date_time).log
