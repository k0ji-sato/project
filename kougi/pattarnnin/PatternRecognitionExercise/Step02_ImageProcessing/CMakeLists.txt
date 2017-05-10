cmake_minimum_required(VERSION 3.7)
project(Step02_ImageProcessing)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Config.h
        main.cpp
        PgmIO.h)

add_executable(Step02_ImageProcessing ${SOURCE_FILES})