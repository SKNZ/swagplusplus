cmake_minimum_required(VERSION 2.8.4)
project(CList)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0  -Wall -Wextra -Werror -g -std=c++11")

set(SOURCE_FILES main.cxx Tests.h Tests.cxx CList2.h CList2.hxx CList2Iterator.hxx CList2ConstIterator.hxx CList2Node.hxx)

add_executable(CList ${SOURCE_FILES})
