cmake_minimum_required(VERSION 3.21)
project(lab1)

enable_testing()
add_subdirectory(googletest)
add_executable(testapp main.cpp BigInt.cpp BigInt.hpp)
target_link_libraries(testapp gtest_main)
