cmake_minimum_required(VERSION 3.2)
project(StlTest)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CSS_STANDARD_REQUIRED TRUE)

add_executable(StlTest src/main.cpp vector/include/Vector.hpp)
