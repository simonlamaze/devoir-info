cmake_minimum_required(VERSION 3.29)
project(Chess)

set(CMAKE_CXX_STANDARD 20)
file(GLOB SOURCES
        *.h
        *.cpp
)

set(
        SOURCE_FILES
        main.cpp
        pieces.h

)
add_executable(Chess ${SOURCE_FILES})
