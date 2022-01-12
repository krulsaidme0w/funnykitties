add_library(mapcontroller mapcontroller.h mapcontroller.cpp)

target_include_directories(mapcontroller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(mapcontroller PUBLIC sfml-graphics sfml-audio map)
