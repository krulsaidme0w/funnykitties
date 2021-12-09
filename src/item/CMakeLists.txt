add_library(item item.h item.cpp)

target_include_directories(item PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(item PUBLIC sfml-graphics sfml-audio gameobject player gamecontroller)
