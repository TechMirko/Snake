cmake_minimum_required(VERSION 3.30)
project(snake_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(snake_1 main.cpp
        Snake.cpp
        Snake.h
        Board.cpp
        Board.h
        default_functions.cpp
        default_functions.h
        ../Menu.cpp
        ../Menu.h
        Position.cpp
        Position.h
        Constant.h
        PauseExit.cpp
        PauseExit.h)

target_link_libraries(snake -lncurses)
