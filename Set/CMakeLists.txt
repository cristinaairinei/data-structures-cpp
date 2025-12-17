cmake_minimum_required(VERSION 3.30)
project(Set_Lab2)

set(CMAKE_CXX_STANDARD 26)

add_executable(Set_Lab2 App.cpp
        Set.cpp
        Set.h
        SetIterator.cpp
        SetIterator.h
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h)

