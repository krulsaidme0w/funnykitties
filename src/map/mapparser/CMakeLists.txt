add_library(mapparser mapparser.h mapparser.cpp)

target_include_directories(mapparser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(mapparser PUBLIC sfml-graphics map nlohmann_json::nlohmann_json item)
