cmake_minimum_required(VERSION 3.17)

project(server)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")


find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(server Server.cpp)

target_link_libraries(server ${Boost_LIBRARIES})
