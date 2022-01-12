add_library(button button.h button.cpp)

target_include_directories(button PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(button PUBLIC sfml-graphics sfml-window dir)