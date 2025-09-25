cmake_minimum_required(VERSION 3.15)
project(mihansolo_bot VERSION 1.0 LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags for Release build
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    if (MSVC)
        # MSVC specific optimization flags
        add_compile_options(/Ox /Ot /Ob2 /Oi /Oy /GL /fp:fast /Gy)
        add_link_options(/LTCG)
    else ()
        # GCC/Clang release flags (optional, you can adjust as needed)
        add_compile_options(-O3 -march=native -flto)
        add_link_options(-flto)
    endif ()
endif ()

add_subdirectory(${CMAKE_SOURCE_DIR}/spdlog)

find_package(spdlog)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Common sources
set(COMMON_SOURCES
        src/engine.cpp
        src/evaluation.cpp
        src/timemanagement.cpp
        src/tt.cpp
        src/utils.cpp
)

# Main executable: engine
add_executable(engine
        ${COMMON_SOURCES}
        src/main.cpp
)
target_link_libraries(engine PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)

target_include_directories(engine PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Experiments executable
add_executable(experiments
        ${COMMON_SOURCES}
        src/experiments.cpp
)
target_link_libraries(experiments PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)

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
target_link_libraries(engine_tests PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)


# Evaluation tests executable
add_executable(evaluation_tests ${EVALUATION_TEST_SOURCES})
target_include_directories(evaluation_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(evaluation_tests PRIVATE gtest gmock gtest_main)
target_link_libraries(evaluation_tests PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)

# Add tests to CTest
add_test(NAME engine_tests COMMAND engine_tests)
add_test(NAME evaluation_tests COMMAND evaluation_tests)
