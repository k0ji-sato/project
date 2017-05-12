cmake_minimum_required(VERSION 3.7)
project(degital2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        degital2.cpp
        stdafx.cpp
        stdafx.h
        targetver.h)

add_executable(degital2 ${SOURCE_FILES})