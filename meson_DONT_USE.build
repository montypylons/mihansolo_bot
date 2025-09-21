project('mihansolo_bot', 'cpp',
        default_options : ['cpp_std=c++20'])

# Compiler flags for release build
if get_option('buildtype') == 'release'
    add_project_arguments(
        '/Ox', '/Ot', '/Ob2', '/Oi', '/Oy', '/GL', '/fp:fast', '/Gy',
        language : 'cpp'
    )
    add_project_link_arguments('/LTCG', language : 'cpp')

endif

# Directories
src_dir = 'src'
inc_dir = 'include'

common_sources = files(
    'src/engine.cpp',
    'src/evaluation.cpp',
    'src/timemanagement.cpp',
    'src/tt.cpp',
    'src/utils.cpp',
)

# Main executable
executable('engine',
           common_sources + files('src/main.cpp'),
           include_directories : include_directories(inc_dir),
           install : true)

# Experiments executable
executable('experiments',
           common_sources + files('src/experiments.cpp'),
           include_directories : include_directories(inc_dir))

# --- Tests ---
gtest_proj = subproject('gtest')

gtest_dep = gtest_proj.get_variable('gtest_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')
gtest_main_dep = gtest_proj.get_variable('gtest_main_dep')

engine_test = files('tests/engine_tests.cc')
evaluation_test = files('tests/evaluation_tests.cc')

engine_tests = executable('engine_tests',
                          engine_test + common_sources,
                          dependencies : [
                              gtest_dep,
                              gmock_dep,
                              gtest_main_dep],
                          include_directories : include_directories(inc_dir))
evaluation_tests = executable('evaluation_tests',
                              evaluation_test + common_sources,
                              dependencies : [
                                  gtest_dep,
                                  gmock_dep,
                                  gtest_main_dep],
                              include_directories : include_directories(inc_dir))
test('engine_tests', engine_tests)
test('evaluation_tests', evaluation_tests)
