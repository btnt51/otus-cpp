#include <iostream>
#include <sstream>
#include "../include/print_ip.hpp"
#include <gtest/gtest.h>


TEST(Test_integral_value, INT8_T) {
    std::stringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());
    print_ip(std::int8_t{-1});
    std::cout.rdbuf(cout_buff);
    ASSERT_EQ(local.str(), "255\n");
}

TEST(Test_integral_value, INT16_T) {
    std::stringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());
    print_ip(std::int16_t{0});
    std::cout.rdbuf(cout_buff);
    ASSERT_EQ(local.str(), "0.0\n");
}

TEST(Test_integral_value, INT32_T) {
    std::ostringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());
    print_ip(std::int32_t{2130706433});
    std::cout.rdbuf(cout_buff);
    ASSERT_EQ(local.str(), "127.0.0.1\n");
}

TEST(Test_integral_value, INT64_T) {
    std::ostringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());
    print_ip(std::int64_t{8875824491850138409});
    std::cout.rdbuf(cout_buff);
    ASSERT_EQ(local.str(), "123.45.67.89.101.112.131.41\n");
}