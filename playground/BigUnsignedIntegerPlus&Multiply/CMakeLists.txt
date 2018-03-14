cmake_minimum_required(VERSION 3.8)
project(playground)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp clac.cpp clac.h)
add_executable(playground ${SOURCE_FILES})