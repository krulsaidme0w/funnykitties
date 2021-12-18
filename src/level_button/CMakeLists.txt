add_library(level_button level_button.h level_button.cpp)

target_include_directories(level_button PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(level_button PUBLIC sfml-graphics sfml-window dir)