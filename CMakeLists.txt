cmake_minimum_required(VERSION 3.10)
project(XML_FMI)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(XML_FMI
        helpFunctions.cpp
        helpFunctions.h
        main.cpp
        Student.cpp
        Student.h)
