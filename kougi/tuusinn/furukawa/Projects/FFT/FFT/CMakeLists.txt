cmake_minimum_required(VERSION 3.7)
project(FFT)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        FFT.cpp
        stdafx.cpp
        stdafx.h
        targetver.h)

add_executable(FFT ${SOURCE_FILES})