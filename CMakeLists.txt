cmake_minimum_required(VERSION 3.14)
project(virtual_memory_simulator_team_21)

set(CMAKE_CXX_STANDARD 14)

add_executable(virtual_memory_simulator_team_21
        main.cpp PageTable.cpp PageTable.h Page.cpp Page.h)
