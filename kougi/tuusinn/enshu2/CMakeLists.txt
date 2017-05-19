cmake_minimum_required(VERSION 3.7)
project(enshu2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Spectrum.cpp)

add_executable(enshu2 ${SOURCE_FILES})