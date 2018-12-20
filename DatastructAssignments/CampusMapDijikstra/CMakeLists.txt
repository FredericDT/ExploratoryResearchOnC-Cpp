cmake_minimum_required(VERSION 3.8)
project(CampusMapDijikstra)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Vertex.h Edge.h)
add_executable(CampusMapDijikstra ${SOURCE_FILES})