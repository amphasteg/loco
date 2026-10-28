cmake_minimum_required(VERSION 3.31)
project(loco)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(BUILD_TESTS "Build test executables" ON)

add_library(loco
  src/hostname.c)

target_sources(loco
  PRIVATE
  FILE_SET private_headers
    TYPE HEADERS
    BASE_DIRS
      src
    FILES
      src/loco_internal.h
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      include
    FILES
      include/loco.h
)

if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
