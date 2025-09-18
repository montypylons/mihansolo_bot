#!/bin/bash

date_time=$(date +"%Y-%m-%d_%H:%M:%S")

cutechess-cli \
  -engine cmd="../build/engine" name=mihan1 \
  -engine cmd="../build/engine" name=mihan2 \
  -concurrency 3 \
  -each proto=uci tc=1+1 \
  -rounds 20 -games 2 \
  -pgnout "../logs/cutechess/tournament_${date_time}.pgn" \
  -debug > "../logs/cutechess/debug_${date_time}.log"
