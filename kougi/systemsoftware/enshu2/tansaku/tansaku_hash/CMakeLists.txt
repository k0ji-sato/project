cmake_minimum_required(VERSION 3.7)
project(tansaku_hash)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        hash.h
        intmath.h
        main.c
        queueP.h
        queuePI.h)

add_executable(tansaku_hash ${SOURCE_FILES})