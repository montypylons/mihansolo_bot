project('mihansolo_bot', 'cpp',
        default_options : ['cpp_std=c++20']
)

if get_option('buildtype') == 'release'
    add_project_arguments(
        '/Ox', '/Ot', '/Ob2', '/Oi', '/Oy', '/GL', '/fp:fast', '/Gy',
        language : 'cpp'
    )
endif

# Directories
src_dir = 'src'
inc_dir = meson.current_source_dir()

common_sources = files(
    'src/engine.cpp',
    'src/evaluation.cpp',
    'src/timemanagement.cpp',
    'src/tt.cpp',
    'src/utils.cpp',
)

executable('mihansolo_bot',
           common_sources + files('src/main.cpp'),
           include_directories : include_directories(inc_dir),
           install : true
)

executable('experiments',
           common_sources + files('src/experiments.cpp'),
           include_directories : include_directories(inc_dir)
)

# --- Tests ---
gtest = dependency('gtest', main : true, required : true)

test_sources = files(
    'tests/engine_tests.cc',
    'tests/evaluation_tests.cc'
)

test_exe = executable('tests',
                      common_sources + test_sources,
                      dependencies : [gtest],
                      include_directories : include_directories(inc_dir)
)

test('unit tests', test_exe)
