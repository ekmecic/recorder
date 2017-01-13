cmake_minimum_required(VERSION 2.8)

project(recorder)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBRARIES OFF)
set(CMAKE_EXE_LINKER_FLAGS "-pie")

# set(CMAKE_C_COMPILER "/usr/bin/clang")
# SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(TARGET ${CMAKE_PROJECT_NAME})
set(CMAKE_C_FLAGS "-Wall -Wextra -fPIE")

# Pick up all of the header and source files recursively
file(GLOB_RECURSE SOURCES
  ${CMAKE_SOURCE_DIR}/src/*.h
  ${CMAKE_SOURCE_DIR}/src/*.c
)

include_directories(
  src
  include
)

find_library(pruio_location pruio)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} LINK_PUBLIC ${pruio_location})
