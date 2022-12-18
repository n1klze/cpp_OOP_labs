cmake_minimum_required(VERSION 3.21)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab2 main.cpp command_line_parser.h command_line_parser.cpp game_field.h game_field.cpp file_parser.h file_parser.cpp game_rules.h game_rules.cpp
        game.cpp game.h life_interface.cpp life_interface.h
        factory.cpp factory.h life_console_interface.cpp life_console_interface.h life_offline_interface.cpp life_offline_interface.h)
