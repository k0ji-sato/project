cmake_minimum_required(VERSION 3.7)
project(enshu2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        "enshu2 2.c"
        enshu2.c
        queueI.h
        queueP.h
        queueS.h)

add_executable(enshu2 ${SOURCE_FILES})