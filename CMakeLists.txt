cmake_minimum_required(VERSION 3.19)
project(logger)

set(CMAKE_CXX_STANDARD 17)

set (HEADERS
        logger.h
        )

set (SOURCES
        logger.cpp
        main.cpp)

add_executable(logger ${HEADERS} ${SOURCES})