cmake_minimum_required(VERSION 2.8.4)
project(CList)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Tests.h Tests.cxx)
add_executable(CList ${SOURCE_FILES})