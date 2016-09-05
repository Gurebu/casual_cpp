cmake_minimum_required(VERSION 3.6)
project(casual_cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0")
set(CONCURRENT_SRC concurrent/spinlock.cpp)
set(FUNC_SRC func/irange.cpp func/functional.cpp)

set(SOURCE_FILES ${CONCURRENT_SRC} ${FUNC_SRC} main.cpp tests/base/Test.cpp tests/base/ThreadingTest.cpp)
add_executable(casual_cpp ${SOURCE_FILES})