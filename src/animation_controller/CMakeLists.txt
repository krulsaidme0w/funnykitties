add_library(animationcontroller animationcontroller.h animationcontroller.cpp)

target_include_directories(animationcontroller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(animationcontroller PUBLIC sfml-graphics)
