cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 17)

project(a_star_search)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(a-star-search ${SOURCES})
