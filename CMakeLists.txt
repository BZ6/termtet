cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME tetris)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories(${INCLUDE})

add_executable(hello ${srcs})
