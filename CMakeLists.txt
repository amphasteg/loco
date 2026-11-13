cmake_minimum_required(VERSION 4.4)
project(loco)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(BUILD_TESTS "Build test executables" ON)

add_library(loco
  src/hostname.c)

target_sources(loco
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      include
    FILES
      include/loco.h
)

add_subdirectory(./src)

if (WIN32)
  target_link_libraries(loco wsock32 ws2_32)
endif()

if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(./testing_framework)
endif()
