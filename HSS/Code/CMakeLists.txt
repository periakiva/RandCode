cmake_minimum_required(VERSION 3.6)
project(HSS)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        btree.hpp
        main.cpp
        mat2hss.hpp
        rQR.hpp
        util.hpp)

add_executable(HSS ${SOURCE_FILES})