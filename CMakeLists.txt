cmake_minimum_required(VERSION 3.10)

project(benchmarkTesting)

set(CMAKE_BUILD_TYPE debug)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(tpl/googletest)
add_subdirectory(tpl/google-benchmark)
add_subdirectory(exceptionTests)
add_subdirectory(sampleTests)