cmake_minimum_required(VERSION 3.13)
project(Project_Files)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project_Files main.cpp Genome.cpp GenomeMatcher.cpp Trie.h)