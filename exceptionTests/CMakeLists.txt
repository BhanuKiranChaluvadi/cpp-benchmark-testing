cmake_minimum_required (VERSION 3.10)

## set the project name and version
project(exceptionTest VERSION 1.0)

add_executable(${PROJECT_NAME}
                exceptions_main.cpp
                exceptions.cpp)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE 
                    ${benchmark_INCLUDE_DIRECTORIES})

target_link_libraries(${PROJECT_NAME}
                    benchmark)
