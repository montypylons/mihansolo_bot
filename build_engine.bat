@echo off
cd build
cmake ..
cd ..
cmake --build build --target engine
cd build/debug
.\engine.exe