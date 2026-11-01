add_library(test_lib
  testing_functions.c
  terminal_color.c
  testing_mocks.c)

target_sources(test_lib
PUBLIC
  FILE_SET HEADERS
  FILES
    tests.h
PRIVATE
  FILE_SET private_headers
  TYPE HEADERS
  FILES
    test_macros.h
    testing_functions.h
    terminal_color.h
)

add_executable(test_runner test_runner.c)
target_link_libraries(test_runner PRIVATE loco test_lib)
target_sources(test_runner
  PRIVATE
  FILE_SET private_headers
  TYPE HEADERS
  BASE_DIRS
    ../src
  FILES
    ../src/loco_internal.h
)

target_sources(test_runner
  PRIVATE
  FILE_SET tests
  TYPE SOURCES
  BASE_DIRS
    ../tests
  FILES
    ../tests/hostname_test.c

)
