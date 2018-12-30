cmake_minimum_required(VERSION 3.8)
project(FINAL_2nd)

set(CMAKE_CXX_STANDARD 11)

set(A A.cpp)
set(B B.cpp)
set(C C.cpp)

add_executable(A ${A})
add_executable(B ${B})
add_executable(C ${C})