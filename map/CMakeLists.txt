cmake_minimum_required(VERSION 3.9)
project(map)

set(CMAKE_CXX_STANDARD 11)

add_executable(map
        #data/five/code.cpp
        #data/five.memcheck/code.cpp
        #data/four/code.cpp
        data/four.memcheck/code.cpp
        #data/one/code.cpp
        #data/one.memcheck/code.cpp
        #data/seven/code.cpp
        #data/seven.memcheck/code.cpp
        #data/six/code.cpp
        #data/six.memcheck/code.cpp
        #data/three/code.cpp
        #data/three.memcheck/code.cpp
        #data/two/code.cpp
        #data/two.memcheck/code.cpp
        #main.cpp
        data/class-bint.hpp
        data/class-integer.hpp
        data/class-matrix.hpp
        exceptions.hpp
        map.hpp
        utility.hpp)
