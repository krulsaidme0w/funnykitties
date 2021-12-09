cmake_minimum_required(VERSION 3.17)

project(Server)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")


find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(Server src/Server/Server.cpp)


target_link_libraries(Server ${Boost_LIBRARIES})

