cmake_minimum_required(VERSION 3.6)
project(boom)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Map.cpp Map.hpp Tile.cpp Tile.hpp Engine.cpp Engine.hpp Client.cpp Client.hpp Renderer.cpp Renderer.hpp)
add_executable(boom ${SOURCE_FILES})
target_link_libraries(boom sfml-graphics sfml-window sfml-system)

add_custom_command(TARGET boom POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res ${PROJECT_BINARY_DIR}/res)
