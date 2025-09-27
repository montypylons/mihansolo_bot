cmake_minimum_required(VERSION 3.15)
project(mihansolo_bot VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Common include ---
add_library(common_includes INTERFACE)
target_include_directories(common_includes INTERFACE ${CMAKE_SOURCE_DIR}/include)

# --- Common source library ---
add_library(engine_core STATIC
        src/engine.cpp
        src/evaluation.cpp
        src/timemanagement.cpp
        src/tt.cpp
        src/utils.cpp
)
target_link_libraries(engine_core PUBLIC common_includes)

# --- Main executables ---
add_executable(engine src/main.cpp)
target_link_libraries(engine PRIVATE engine_core)

add_executable(experiments src/experiments.cpp)
target_link_libraries(experiments PRIVATE engine_core)

# --- MSVC Release Optimizations ---
if (MSVC)
    # Compiler flags applied only in Release
    target_compile_options(engine PRIVATE
            $<$<CONFIG:Release>:/Ox /Ot /Ob2 /Oi /Oy /GL /fp:fast /Gy /GF /Gw /arch:AVX2 /favor:INTEL64 /GS- /permissive->
    )
    target_compile_options(experiments PRIVATE
            $<$<CONFIG:Release>:/Ox /Ot /Ob2 /Oi /Oy /GL /fp:fast /Gy /GF /Gw /arch:AVX2 /favor:INTEL64 /GS- /permissive->
    )
    target_compile_options(engine_core PRIVATE
            $<$<CONFIG:Release>:/Ox /Ot /Ob2 /Oi /Oy /GL /fp:fast /Gy /GF /Gw /arch:AVX2 /favor:INTEL64 /GS- /permissive->
    )

    # Linker flags applied only in Release
    target_link_options(engine PRIVATE $<$<CONFIG:Release>:/LTCG /INCREMENTAL:NO /OPT:REF /OPT:ICF /DEBUG:NONE>)
    target_link_options(experiments PRIVATE $<$<CONFIG:Release>:/LTCG /INCREMENTAL:NO /OPT:REF /OPT:ICF /DEBUG:NONE>)
endif ()

# --- Tests ---
enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(engine_tests tests/engine_tests.cc)
target_link_libraries(engine_tests PRIVATE engine_core gtest gmock gtest_main)

add_executable(evaluation_tests tests/evaluation_tests.cc)
target_link_libraries(evaluation_tests PRIVATE engine_core gtest gmock gtest_main)

add_test(NAME engine_tests COMMAND engine_tests)
add_test(NAME evaluation_tests COMMAND evaluation_tests)
