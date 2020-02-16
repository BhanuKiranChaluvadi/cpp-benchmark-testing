cmake_minimum_required (VERSION 3.10)

## set the project name and version
project(simpleTest)

add_executable(${PROJECT_NAME}
                simpletest.cc)

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE 
                    ${benchmark_INCLUDE_DIRECTORIES})

target_link_libraries(${PROJECT_NAME}
                    benchmark)
