#include <iostream>
#include <sstream>
#include "../include/print_ip.hpp"
#include <gtest/gtest.h>


TEST(Test_containers, vector) {
    std::stringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());
    print_ip(std::vector<int>{100, 200, 300, 400} );
    std::cout.rdbuf(cout_buff);
    ASSERT_EQ(local.str(), "100.200.300.400\n");
}


TEST(Test_containers, list) {
    std::stringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());
    print_ip(std::list<short>{400, 300, 200, 100}  );
    std::cout.rdbuf(cout_buff);
    ASSERT_EQ(local.str(), "400.300.200.100\n");
}


TEST(Test_containers, tuple) {
    std::stringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());
    print_ip(std::make_tuple(123, 456, 789, 0));
    std::cout.rdbuf(cout_buff);
    ASSERT_EQ(local.str(), "123.456.789.0\n");
}