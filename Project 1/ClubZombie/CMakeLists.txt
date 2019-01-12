cmake_minimum_required(VERSION 3.13)
project(ClubZombie)

set(CMAKE_CXX_STANDARD 14)

add_executable(ClubZombie main.cpp Zombie.cpp Zombie.h Arena.cpp Arena.h Player.cpp Player.h Game.cpp Game.h globals.h utilities.cpp)