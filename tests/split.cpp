#include <fstream>
#include "../include/ipfilter.hpp"
#include "googletest/googletest/include/gtest/gtest.h"



TEST(test_build, split_empty)
{
    std::vector<std::string> right_value = {""};
    EXPECT_EQ(split("", '.'), right_value);
}

TEST(test_build, split_eleven)
{
    std::vector<std::string> right_value = {"11"};
    EXPECT_EQ(split("11", '.'), right_value);
}

TEST(test_build, split_two_dots)
{
    std::vector<std::string> right_value = {"", "", ""};
    EXPECT_EQ(split("..", '.'), right_value);
}

TEST(test_build, split_eleven_with_postfix_dot)
{
    std::vector<std::string> right_value = {"11", ""};
    EXPECT_EQ(split("11.", '.'), right_value);
}

TEST(test_build, split_eleven_with_prefix_dot)
{
    std::vector<std::string> right_value = {"", "11"};
    EXPECT_EQ(split(".11", '.'), right_value);
}

TEST(test_build, split_eleven_twelve)
{
    std::vector<std::string> right_value = {"11", "22"};
    EXPECT_EQ(split("11.22", '.'), right_value);
}



