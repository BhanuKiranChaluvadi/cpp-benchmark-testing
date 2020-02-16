cmake_minimum_required (VERSION 3.10)

## set the project name and version
project(simpletest VERSION 1.0)

## set(CMAKE_BUILD_TYPE debug)

## specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

## find required package
find_package(benchmark REQUIRED)

## add the executable
# add_executable(simpletest simpletest.cc) 
# target_link_libraries(simpletest benchmark::benchmark)

add_executable(${PROJECT_NAME}
                exceptions_main.cpp
                exceptions.cpp)
target_link_libraries (${PROJECT_NAME}
                        benchmark::benchmark)
