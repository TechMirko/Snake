cmake_minimum_required(VERSION 3.10)
project(Snake)

set(CMAKE_CXX_STANDARD 20)


add_executable(snake main.cpp
        menu.cpp
        menu.h
        costanti.h)

target_link_libraries(snake -lncurses)
