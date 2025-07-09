@echo off
setlocal

REM ========================================
REM Clean previous build
REM ========================================
if exist build (
    echo Removing old build directory...
    rd /s /q build
)

REM ========================================
REM Create and enter new build directory
REM ========================================
echo Creating new build directory...
mkdir build
cd build

REM ========================================
REM Configure CMake with vcpkg toolchain
REM ========================================
echo Configuring project with CMake...
cmake .. ^
    -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake ^
    -DCMAKE_BUILD_TYPE=Debug
if %errorlevel% neq 0 (
    echo [ERROR] CMake configuration failed.
    pause
    exit /b 1
)

REM ========================================
REM Build project
REM ========================================
echo Building project...
cmake --build . --config Debug
if %errorlevel% neq 0 (
    echo [ERROR] Build failed.
    pause
    exit /b 1
)

REM ========================================
REM Run tests
REM ========================================
echo Running tests...
ctest -C Debug --output-on-failure
if %errorlevel% neq 0 (
    echo [WARNING] Some tests failed.
)

REM ========================================
REM Done
REM ========================================
echo Build and test complete.
pause
endlocal
