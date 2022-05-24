cmake_minimum_required(VERSION 3.22)
project(Chinese_Chess)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(nlohmann)

add_executable(Chinese_Chess
        nlohmann/json.hpp
        Chess.cpp
        Chess.h
        GameManager.h
        GameManager.cpp
        ChessEnum.h
        main.cpp
        Position.cpp
        Position.h
        Record.cpp
        Record.h
        Viewer.h
        Viewer.cpp
        Board.cpp
        Board.h)
