cmake_minimum_required(VERSION 3.31)
project(SortedMultiMap2)

set(CMAKE_CXX_STANDARD 23)

add_executable(SortedMultiMap2 App.cpp
        SortedMultiMap.cpp
        SMMIterator.cpp
        ExtendedTest.cpp
        ShortTest.cpp)
