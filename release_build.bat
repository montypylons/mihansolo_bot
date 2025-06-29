@echo off
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cd ..
cmake --build build --config Release --target engine
cd build/release
