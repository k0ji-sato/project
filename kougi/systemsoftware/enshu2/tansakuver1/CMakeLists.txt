cmake_minimum_required(VERSION 3.7)
project(tansakuver1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        hash.h
        intmath.h
        main.c
        queueP.h
        queuePI.h)

add_executable(tansakuver1 ${SOURCE_FILES})