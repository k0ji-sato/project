cmake_minimum_required(VERSION 3.7)
project(Step05_kNearestNeighbor)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Config.h
        main.cpp
        PgmIO.h
        RecognitionResult.h)

add_executable(Step05_kNearestNeighbor ${SOURCE_FILES})