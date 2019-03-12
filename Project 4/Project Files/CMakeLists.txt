cmake_minimum_required(VERSION 3.13)
project(Project_Files)

set(CMAKE_CXX_STANDARD 17)

add_executable(Genomics officialMain.cpp Genome.cpp GenomeMatcher.cpp main.cpp)