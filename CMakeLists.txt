cmake_minimum_required(VERSION 3.6)
project(casual_cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0")
set(CONCURRENT_SRC concurrent/spinlock.cpp concurrent/blocking/stack.cpp)
set(FUNC_SRC func/irange.cpp func/functional.cpp)
set(TEST_SRC tests/base/Test.cpp tests/base/ThreadingTest.cpp)

set(SOURCE_FILES ${CONCURRENT_SRC} ${FUNC_SRC} ${TEST_SRC} main.cpp)
add_executable(casual_cpp ${SOURCE_FILES})