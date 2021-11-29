add_library(player player.h player.cpp)

target_include_directories(player PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(player PUBLIC sfml-graphics sfml-audio gameobject animationcontroller)
