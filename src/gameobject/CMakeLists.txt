add_library(gameobject gameobject.h gameobject.cpp)

target_include_directories(gameobject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gameobject PUBLIC sfml-graphics sfml-audio)
