add_library(gamecontroller gamecontroller.h gamecontroller.cpp)

target_include_directories(gamecontroller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gamecontroller PUBLIC sfml-graphics sfml-audio gameobject player)
