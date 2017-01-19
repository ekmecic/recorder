cmake_minimum_required(VERSION 2.8)

project(recorder)

set(TARGET ${CMAKE_PROJECT_NAME})
set(CMAKE_C_FLAGS "-std=gnu99 -Wall -Wextra -lrt -O3")

# Pick up all of the header and source files recursively
file(GLOB_RECURSE SOURCES
  ${CMAKE_SOURCE_DIR}/src/*.h
  ${CMAKE_SOURCE_DIR}/src/*.c
  ${CMAKE_SOURCE_DIR}/lib/*.h
  ${CMAKE_SOURCE_DIR}/lib/*.c
  ${CMAKE_SOURCE_DIR}/include/argparse/*.h
  ${CMAKE_SOURCE_DIR}/include/argparse/*.c
)

include_directories(
  src
  include
)

find_library(libpruio pruio)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} LINK_PUBLIC ${libpruio})
