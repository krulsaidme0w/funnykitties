add_library(menu menu.h menu.cpp)

target_include_directories(menu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(menu PUBLIC sfml-graphics sfml-window button gamecontroller)