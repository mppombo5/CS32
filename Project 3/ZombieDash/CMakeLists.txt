cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME "ZombieDash")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(ZombieDash main.cpp Actor.cpp GameController.cpp GameWorld.cpp StudentWorld.cpp)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})