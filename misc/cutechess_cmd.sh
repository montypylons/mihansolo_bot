#!/bin/bash

date_time=$(date +"%Y_%m_%d_%H__%M__%S")

cutechess-cli \
  -engine cmd="../build/engine" name=mihan1 \
  -engine cmd="../build/engine" name=mihan2 \
  -each proto=uci tc=200/60 \
  -rounds 40 -games 1 \
  -pgnout "../logs/cutechess/tournament_${date_time}.pgn" \
  -debug | tee "../logs/cutechess/debug_${date_time}.log"
