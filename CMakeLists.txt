cmake_minimum_required(VERSION 3.16)
project(snake_engine LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Sources
add_executable(snake
    src/main.cpp
    src/app.cpp
    src/renderer.cpp
    src/button.cpp
    src/input.cpp
    src/text.cpp
    src/snake_game.cpp
)

# Dependencies
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(snake PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf)

target_include_directories(snake PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Warnings
if(MSVC)
    target_compile_options(snake PRIVATE /W4 /permissive-)
else()
    target_compile_options(snake PRIVATE -Wall -Wextra -Wpedantic -Wno-unused-parameter)
endif()

# Install rule (optional)
install(TARGETS snake RUNTIME DESTINATION bin)
