cmake_minimum_required(VERSION 3.8)
project(cppstd17)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp csv.h StringTool.h ws.h)
add_executable(cppstd17 ${SOURCE_FILES})