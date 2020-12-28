cmake_minimum_required(VERSION 3.16)

project(Gomoku C)

aux_source_directory(. DIR_SRCS)

include_directories("./include")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
add_compile_definitions(_DEBUG)
endif ()

add_executable(gomoku ${DIR_SRCS})
