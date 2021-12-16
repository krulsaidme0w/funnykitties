cmake_minimum_required(VERSION 3.16.3)

project(funny_kitties CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

add_subdirectory(src)
add_subdirectory(cmd)
add_subdirectory(tests)

file(COPY assets DESTINATION ./)
file(COPY levels DESTINATION ./)
