cmake_minimum_required(VERSION 3.16)

project(SVDImageClassification)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O2")

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
set(MAIN_FILE ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable(SVDImageClassification ${SOURCES} ${MAIN_FILE})
