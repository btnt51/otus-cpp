#include <iostream>
#include <sstream>
#include "../include/print_ip.hpp"
#include <gtest/gtest.h>


TEST(Test_string_value, STDSTRING) {
    std::stringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());
    print_ip( std::string{"Hello, World!"} );
    std::cout.rdbuf(cout_buff);
    ASSERT_EQ(local.str(), "Hello, World!\n");
}