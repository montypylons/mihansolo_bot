
rd /s /q build

mkdir build
cd build

cmake .. ^
    -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake ^
    -DCMAKE_BUILD_TYPE=Debug

cmake --build . --config Debug
