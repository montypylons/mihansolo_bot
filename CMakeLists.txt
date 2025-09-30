cmake_minimum_required(VERSION 3.15)
project(mihansolo_bot VERSION 1.0 LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    if (MSVC)
        # MSVC optimizations
        add_compile_options(/O2 /Ot /Ob2 /Oi /Oy /GL /fp:fast /Gy)
        add_link_options(/LTCG)
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        # GCC/Clang optimizations
        add_compile_options(
                -O3             # highest general optimization
                -march=native   # optimize for host CPU
                -funroll-loops  # aggressive loop unrolling
                -ffast-math     # unsafe but faster math
        )
        add_link_options(
                -flto           # enable link-time optimization
        )
    endif ()
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    if (MSVC)
        add_link_options(/PROFILE)
    endif ()
endif ()


# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Common sources
set(COMMON_SOURCES
        src/engine.cpp
        src/evaluation.cpp
        src/timemanagement.cpp
        src/tt.cpp
        src/utils.cpp
        src/polyglot.cpp
)

# Main executable: engine
add_executable(engine
        ${COMMON_SOURCES}
        src/main.cpp
)

target_include_directories(engine PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Experiments executable
add_executable(experiments
        ${COMMON_SOURCES}
        src/experiments.cpp
)

target_include_directories(experiments PRIVATE ${CMAKE_SOURCE_DIR}/include)

# --- Tests ---

# Enable testing
enable_testing()

# GoogleTest setup via FetchContent
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test sources
set(ENGINE_TEST_SOURCES
        tests/engine_tests.cc
        ${COMMON_SOURCES}
)
set(EVALUATION_TEST_SOURCES
        tests/evaluation_tests.cc
        ${COMMON_SOURCES}
)

# Engine tests executable
add_executable(engine_tests ${ENGINE_TEST_SOURCES})
target_include_directories(engine_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(engine_tests PRIVATE gtest gmock gtest_main)


# Evaluation tests executable
add_executable(evaluation_tests ${EVALUATION_TEST_SOURCES})
target_include_directories(evaluation_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(evaluation_tests PRIVATE gtest gmock gtest_main)

# Add tests to CTest
add_test(NAME engine_tests COMMAND engine_tests)
add_test(NAME evaluation_tests COMMAND evaluation_tests)
