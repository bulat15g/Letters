cmake_minimum_required(VERSION 3.6)
project(Letters)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Letter.h
        main.cpp)

add_executable(Letters ${SOURCE_FILES})