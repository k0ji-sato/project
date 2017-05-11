cmake_minimum_required(VERSION 3.7)
project(ega)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ega_cheat.c)

add_executable(ega ${SOURCE_FILES})