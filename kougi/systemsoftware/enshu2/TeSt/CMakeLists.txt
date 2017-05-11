cmake_minimum_required(VERSION 3.7)
project(TeSt)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        queueI.h
        test.c)

add_executable(TeSt ${SOURCE_FILES})