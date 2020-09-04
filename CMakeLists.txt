cmake_minimum_required(VERSION 3.14)
project(test_4d)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pedantic -Wall -Wextra")

file(GLOB SOURCES "*.cpp" "*.h")
add_executable(test_4d ${SOURCES})