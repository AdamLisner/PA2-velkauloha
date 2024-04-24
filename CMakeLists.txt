cmake_minimum_required(VERSION 3.28)
project(velkauloha)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(velkauloha
        expression.h
        test.cpp
        ASTBuilder.cpp)
