cmake_minimum_required(VERSION 3.26)
project(hello_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(hello_cpp main.cpp
        lib.cpp)