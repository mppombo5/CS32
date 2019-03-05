cmake_minimum_required(VERSION 3.13)
project(Project_Files)

set(CMAKE_CXX_STANDARD 14)

add_executable(Set testSet.cpp Set.h)
add_executable(List list.cpp)
add_executable(Sorts sorts.cpp)