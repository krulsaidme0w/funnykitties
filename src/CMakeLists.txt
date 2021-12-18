add_subdirectory(menu)
add_subdirectory(buttons)
add_subdirectory(level_menu)
add_subdirectory(level_button)

add_library(dir dir.cpp)
target_include_directories(dir PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})