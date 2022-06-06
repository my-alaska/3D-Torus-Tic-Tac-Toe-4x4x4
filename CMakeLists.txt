cmake_minimum_required(VERSION 3.19)
project(tictactoe_torus)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

set(CMAKE_MODULE_PATH $(PROJECT_SOURCE_DIR)/cmake)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(tictactoe_torus main.cpp game_map.cpp game_map.h)

target_link_libraries(tictactoe_torus ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -mwindows)