cmake_minimum_required(VERSION 3.28)
project(holt_winters)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES
        src/*.cpp
)

add_library(holt_winters
        ${SOURCES})

target_include_directories(holt_winters
        PUBLIC "${holt_winters_SOURCE_DIR}/include")

add_subdirectory(demos)
add_subdirectory(tests)
