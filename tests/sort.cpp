#include <fstream>
#include "../include/ipfilter.hpp"
#include "googletest/googletest/include/gtest/gtest.h"


TEST(sort, old_sort_with)
{
    std::ifstream ifs("tests/sort.tsv");
    std::vector<std::vector<std::string> > ip_pool;
    for(std::string line; std::getline(ifs, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
    }
    std::ifstream ifsorted("tests/sorted.tsv");
    std::vector<std::vector<std::string> > sorted;
    for(std::string line; std::getline(ifsorted, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        sorted.push_back(split(v.at(0), '.'));
    }
    EXPECT_EQ(sort(ip_pool), sorted);
}


TEST(sort, sort_with_ipAddress)
{
    std::ifstream ifs("tests/sort.tsv");
    std::vector<ipAddress > ip_pool;
    for(std::string line; std::getline(ifs, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        ip_pool.push_back(ipAddress(split(v.at(0), '.')));
    }
    std::ifstream ifsorted("tests/sorted.tsv");
    std::vector<ipAddress> sorted;
    for(std::string line; std::getline(ifsorted, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        sorted.push_back(ipAddress(split(v.at(0), '.')));
    }
    EXPECT_EQ(sort(ip_pool), sorted);
}