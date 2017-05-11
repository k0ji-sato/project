cmake_minimum_required(VERSION 3.7)
project(tansaku)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        enshu2.c
        queueI.h
        queueP.h
        queueS.h)

add_executable(tansaku ${SOURCE_FILES})