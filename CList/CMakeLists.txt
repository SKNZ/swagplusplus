cmake_minimum_required(VERSION 2.8.4)
project(CList)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-O0  -Wall -Wextra -g -std=c++11 -fmudflap -lmudflap")

set(SOURCE_FILES main.cpp Tests.h Tests.cxx)
add_executable(CList ${SOURCE_FILES})
