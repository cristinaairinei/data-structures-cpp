cmake_minimum_required(VERSION 3.30)
project(Matrix)

set(CMAKE_CXX_STANDARD 26)

add_executable(Matrix
        App.cpp
        Matrix.cpp
        Matrix.h
        ShortTest.cpp
        ShortTest.h
        ExtendedTest.cpp
        ExtendedTest.h)
