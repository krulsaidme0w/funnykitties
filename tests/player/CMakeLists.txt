find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(player_tests main.cpp player_tests.cpp)

target_link_libraries(player_tests ${GTEST_LIBRARIES} Threads::Threads player map gamecontroller)

add_test(NAME player_tests COMMAND player_tests)
