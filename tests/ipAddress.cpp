#include <fstream>
#include "../include/ipaddress.hpp"
#include <gtest/gtest.h>


TEST(ipAddress, fill_ip_with_ZERO) 
{
    ipAddress t(std::vector<std::string> {"0", "0", "0", "0"});
    std::array<int, 4> res= {0,0,0,0};
    EXPECT_EQ(t.getBytes(), res);
}