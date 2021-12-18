add_library(level_menu level_menu.h level_menu.cpp)

target_include_directories(level_menu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(level_menu PUBLIC sfml-graphics sfml-window level_button dir)