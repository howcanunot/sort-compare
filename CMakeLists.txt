cmake_minimum_required(VERSION 3.20)
project(SortrCompare)

set(CMAKE_CXX_STANDARD 20)

add_executable(SortrCompare main.cpp metrics/sortings/sortings.cpp metrics/metrics.cpp)
