#include "gtest/gtest.h"
#include "../src/Server/Server.h"

TEST(server_test, valid_data) {
    ASSERT_EQ(result, Server::start());
}

TEST(server_test, not_valid_data) {
    ASSERT_EQ(NULL, Server::stop());
}