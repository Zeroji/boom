cmake_minimum_required(VERSION 3.6)
project(boom)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Map.cpp Map.hpp Tile.cpp Tile.hpp)
add_executable(boom ${SOURCE_FILES})
