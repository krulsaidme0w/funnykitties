find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(gamecontroller_tests main.cpp gamecontroller_tests.cpp)

target_link_libraries(gamecontroller_tests ${GTEST_LIBRARIES} Threads::Threads)

add_test(NAME gamecontroller_tests COMMAND gamecontroller_tests)
