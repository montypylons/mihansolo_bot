cmake_minimum_required(VERSION 3.14)
project(mihansolo_bot LANGUAGES CXX)

# -------------------------------
# C++ Standard
# -------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC AND CMAKE_BUILD_TYPE STREQUAL "Release")

    # Compile-time optimizations for speed
    add_compile_options(
            /Ox        # Full optimization
            /Ot        # Favor fast code
            /Ob2       # Inline anything suitable
            /Oi        # Use intrinsics
            /Oy        # Omit frame pointer
            /GL        # Whole program optimization
            /fp:fast   # Fast floating-point math
            /Gy        # Function-level linking
    )

    # Link-time optimizations
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LTCG /OPT:REF /OPT:ICF")
endif ()

# -------------------------------
# Dependencies
# -------------------------------
include(FetchContent)

# GoogleTest setup
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# -------------------------------
# Source Files
# -------------------------------
file(GLOB ENGINE_SOURCES CONFIGURE_DEPENDS src/*.cpp)
list(REMOVE_ITEM ENGINE_SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp")

# -------------------------------
# Engine Core Library
# -------------------------------
add_library(engine_lib ${ENGINE_SOURCES}
        src/tt.cpp
        src/timemanagement.cpp
        include/timemanagement.hpp)
target_include_directories(engine_lib PUBLIC include)

# -------------------------------
# Executable: engine (UCI main)
# -------------------------------
add_executable(engine src/main.cpp
        src/tt.cpp
        src/timemanagement.cpp
        include/timemanagement.hpp)
target_link_libraries(engine PRIVATE engine_lib)
install(TARGETS engine DESTINATION .)

# -------------------------------
# Test Targets
# -------------------------------
enable_testing()

# Evaluation Tests
add_executable(evaluation_tests tests/evaluation_tests.cc
        src/tt.cpp
        src/timemanagement.cpp
        include/timemanagement.hpp)
target_include_directories(evaluation_tests PRIVATE include)
target_link_libraries(evaluation_tests PRIVATE engine_lib GTest::gtest_main)
add_test(NAME evaluation_tests COMMAND evaluation_tests)

# Engine Tests
add_executable(engine_tests tests/engine_tests.cc
        src/tt.cpp
        src/timemanagement.cpp
        include/timemanagement.hpp)
target_include_directories(engine_tests PRIVATE include)
target_link_libraries(engine_tests PRIVATE engine_lib GTest::gtest_main)
add_test(NAME engine_tests COMMAND engine_tests)

