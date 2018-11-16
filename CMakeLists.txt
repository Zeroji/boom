cmake_minimum_required(VERSION 3.6)
project(boom)

set(CMAKE_CXX_STANDARD 11)

# Cross-platform source files and libraries

include_directories(src)
file(GLOB COMMON_SOURCE_FILES src/core/*.cpp)
file(GLOB CLIENT_SOURCE_FILES src/client/*.cpp)

set(TARGET_LIBS sfml-graphics sfml-window sfml-system)

# Linux client
add_executable(boom ${COMMON_SOURCE_FILES} ${CLIENT_SOURCE_FILES})
target_link_libraries(boom ${TARGET_LIBS})

add_custom_command(TARGET boom POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res ${PROJECT_BINARY_DIR}/res)

# Windows client
add_executable(boom.exe ${COMMON_SOURCE_FILES} ${CLIENT_SOURCE_FILES})

set(TARGET_LIBS_WIN_ONLY freetype jpeg opengl32 winmm gdi32 ws2_32)
foreach(lib ${TARGET_LIBS})
    list(APPEND TARGET_LIBS_WIN ${lib}-s)
endforeach()

target_link_libraries(boom.exe ${TARGET_LIBS_WIN} ${TARGET_LIBS_WIN_ONLY})

add_custom_command(TARGET boom.exe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E tar "cfv" "boom.zip" --format=zip
        ${PROJECT_BINARY_DIR}/boom.exe
        ${PROJECT_BINARY_DIR}/res)