cmake_minimum_required (VERSION 3.5)
project(PosixThreadHandler CXX)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")
include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(PosixThreadHandler STATIC ${SOURCES})

add_subdirectory(test)