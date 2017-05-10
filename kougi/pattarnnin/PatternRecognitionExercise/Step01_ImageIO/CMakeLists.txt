cmake_minimum_required(VERSION 3.7)
project(Step01_ImageIO)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Config.h
        main.cpp
        PgmIO.h)

add_executable(Step01_ImageIO ${SOURCE_FILES})