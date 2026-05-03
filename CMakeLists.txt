cmake_minimum_required(VERSION 4.1)
project(Bugs_Life_Project_2026)

set(CMAKE_CXX_STANDARD 20)

add_executable(Bugs_Life_Project_2026 main.cpp
        Bug.cpp
        Bug.h
        Crawler.cpp
        Crawler.h
        Hopper.cpp
        Hopper.h
        Board.cpp
        Board.h
        DiagonalBug.cpp
        DiagonalBug.h)
