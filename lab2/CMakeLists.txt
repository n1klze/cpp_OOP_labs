cmake_minimum_required(VERSION 3.21)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab2 main.cpp command_line_parser.h command_line_parser.cpp game_field.h game_field.cpp file_parser.h file_parser.cpp game_rules.h game_rules.cpp)
