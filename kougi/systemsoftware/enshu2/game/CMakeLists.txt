cmake_minimum_required(VERSION 3.7)
project(game)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        enshu2.c)

add_executable(game ${SOURCE_FILES})