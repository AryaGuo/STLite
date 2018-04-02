cmake_minimum_required(VERSION 3.9)
project(priority_queue)

set(CMAKE_CXX_STANDARD 11)

add_executable(priority_queue
        data/five/code.cpp
        #data/five.memcheck/code.cpp
        #data/four/code.cpp
        #data/four.memcheck/code.cpp
        #data/one/code.cpp
        #data/one.memcheck/code.cpp
        #data/three/code.cpp
        #data/three.memcheck/code.cpp
        #data/two/code.cpp
        #data/two.memcheck/code.cpp
        #main.cpp
        exceptions.hpp
        priority_queue.hpp
        utility.hpp)
