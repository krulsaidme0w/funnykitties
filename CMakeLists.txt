cmake_minimum_required(VERSION 3.16.3)

project(funny_kitties CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)
