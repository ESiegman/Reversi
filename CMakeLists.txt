cmake_minimum_required(VERSION 3.10)

# Project name
project(MyGameProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
set(SOURCES
    src/board.cpp
    src/game.cpp
    src/opponent.cpp
    src/main.cpp
)

# Header files
set(HEADERS
    src/board.hpp
    src/game.hpp
    src/consts.hpp
    src/opponent.hpp
)

# Create executable
add_executable(Reversi ${SOURCES} ${HEADERS})

