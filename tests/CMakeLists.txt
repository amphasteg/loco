function(create_test test_name test_file)
  add_executable(${test_name} ${test_file})

  target_sources(${test_name}
  PRIVATE
    FILE_SET private_headers
    TYPE HEADERS
    BASE_DIRS
      ../src
    FILES
      ../src/loco_internal.h
)

  target_link_libraries(${test_name} PUBLIC loco PRIVATE test_lib)

  add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

add_library(test_lib testing_functions.c terminal_color.c)

target_sources(test_lib
PUBLIC
  FILE_SET HEADERS
  BASE_DIRS
    .
  FILES
    tests.h
    terminal_color.h
PRIVATE
  FILE_SET private_headers
  TYPE HEADERS
  BASE_DIRS
    .
  FILES
    test_macros.h
    testing_functions.h
)

create_test(hostname_tests hostname_test.c ../src/hostname.c)
