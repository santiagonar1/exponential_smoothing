cmake_minimum_required(VERSION 3.28)
project(holt_winters)

set(CMAKE_CXX_STANDARD 20)

find_package(ensmallen REQUIRED)

file(GLOB SOURCES
        src/*.cpp
)

add_library(holt_winters
        ${SOURCES})

target_link_libraries(holt_winters
        ensmallen::ensmallen)

target_include_directories(holt_winters
        PUBLIC "${holt_winters_SOURCE_DIR}/include")

add_subdirectory(demos)
add_subdirectory(tests)
