add_library(map map.h map.cpp)

target_include_directories(map PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(map PUBLIC sfml-graphics sfml-audio player)
