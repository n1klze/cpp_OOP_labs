cmake_minimum_required(VERSION 3.21)

# задаем используемый стандарт С++
set(CMAKE_CXX_STANDARD 14)

project(lab2)

set(exe_name ${PROJECT_NAME})
set(test_name test)

add_executable(${exe_name} main.cpp)

add_library(corelib OBJECT command_line_parser.h command_line_parser.cpp game_field.h game_field.cpp file_parser.h
        file_parser.cpp game_rules.h game_rules.cpp game.cpp game.h life_interface.cpp life_interface.h factory.cpp
        factory.h life_console_interface.cpp life_console_interface.h life_offline_interface.cpp life_offline_interface.h file_format_exception.h)
target_link_libraries(${exe_name} corelib)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${test_name} test.cpp)
target_link_libraries(${test_name} gtest_main)
target_link_libraries(${test_name} corelib)