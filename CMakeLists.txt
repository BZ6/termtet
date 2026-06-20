cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME tetris)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories(${INCLUDE})

find_package(Threads REQUIRED)

add_executable(hello ${srcs})
target_compile_options(hello PRIVATE /std:c11)

target_link_libraries(hello Threads::Threads)
