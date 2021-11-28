cmake_minimum_required(VERSION 3.20)
project(Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

add_subdirectory(menu)
target_link_libraries(main LINK_PUBLIC menu)