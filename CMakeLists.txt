cmake_minimum_required(VERSION 3.6)
project(boom)

set(CMAKE_CXX_STANDARD 11)

# Cross-platform source files and libraries
set(SOURCE_FILES main.cpp Map.cpp Map.hpp Tile.cpp Tile.hpp Engine.cpp Engine.hpp Client.cpp Client.hpp Renderer.cpp Renderer.hpp Entity.cpp Entity.hpp Player.cpp Player.hpp Direction.cpp Direction.hpp InputHandler.cpp InputHandler.hpp Control.cpp Control.hpp)
set(TARGET_LIBS sfml-graphics sfml-window sfml-system)

# Linux client
#set(CMAKE_SYSTEM_NAME Linux)
add_executable(boom ${SOURCE_FILES} PlayerSkin.cpp PlayerSkin.hpp PlayerMenu.cpp PlayerMenu.hpp ResourceLoader.cpp ResourceLoader.hpp)
target_link_libraries(boom ${TARGET_LIBS})

add_custom_command(TARGET boom POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res ${PROJECT_BINARY_DIR}/res)

# Windows client
add_executable(boom.exe ${SOURCE_FILES})

set(TARGET_LIBS_WIN_ONLY freetype jpeg opengl32 winmm gdi32 ws2_32)
foreach(lib ${TARGET_LIBS})
    list(APPEND TARGET_LIBS_WIN ${lib}-s)
endforeach()

target_link_libraries(boom.exe ${TARGET_LIBS_WIN} ${TARGET_LIBS_WIN_ONLY})

add_custom_command(TARGET boom.exe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E tar "cfv" "boom.zip" --format=zip
        ${PROJECT_BINARY_DIR}/boom.exe
        ${PROJECT_BINARY_DIR}/res)