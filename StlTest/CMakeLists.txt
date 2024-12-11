cmake_minimum_required(VERSION 3.12.0)
set(PROJECT_NAME StlTest)
project(${PROJECT_NAME} C CXX)

# set standard to C++ 17
SET(LINKER_LANGUAGE CXX)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CSS_STANDARD_REQUIRED TRUE)

add_executable(StlTest src/main.cpp include/Widget.hpp include/vector.hpp include/shared_ptr.hpp include/string.hpp include/unique_ptr.hpp include/ThreadPool.hpp)
