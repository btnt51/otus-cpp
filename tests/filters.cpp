#include <fstream>
#include "../include/ipfilter.hpp"
#include "googletest/googletest/include/gtest/gtest.h"



TEST(filters, old_filter_1_with_strings)
{
    std::ifstream ifs("ip_filter.tsv");
    std::vector<std::vector<std::string> > ip_pool;
    for(std::string line; std::getline(ifs, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
    }
    std::ifstream ifsorted("tests/filter_1.tsv");
    std::vector<std::vector<std::string> > filterRes;
    for(std::string line; std::getline(ifsorted, line);)
    {
        filterRes.push_back(split(line, '.'));
    }
    ip_pool = sort(ip_pool);

    EXPECT_EQ(filter(ip_pool, 1), filterRes);
}

TEST(filters, old_filter_46_70_with_strings)
{
    std::ifstream ifs("ip_filter.tsv");
    std::vector<std::vector<std::string> > ip_pool;
    for(std::string line; std::getline(ifs, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
    }
    std::ifstream ifsorted("tests/filter_46_70.tsv");
    std::vector<std::vector<std::string> > filterRes;
    for(std::string line; std::getline(ifsorted, line);)
    {
        filterRes.push_back(split(line, '.'));
    }
    ip_pool = sort(ip_pool);
    EXPECT_EQ(filter(ip_pool, 46, 70), filterRes);
}

TEST(filters, old_filter_any_46_with_string)
{
    std::ifstream ifs("ip_filter.tsv");
    std::vector<std::vector<std::string> > ip_pool;
    for(std::string line; std::getline(ifs, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
    }
    std::ifstream ifsorted("tests/filter_any_46.tsv");
    std::vector<std::vector<std::string> > filterRes;
    for(std::string line; std::getline(ifsorted, line);)
    {
        filterRes.push_back(split(line, '.'));
    }
    ip_pool = sort(ip_pool);
    EXPECT_EQ(filter_any(ip_pool, 46), filterRes);
}



TEST(filter, new_filter_1_with_ipAddress)
{
    std::ifstream ifs("ip_filter.tsv");
    std::vector<ipAddress> ip_pool;
    for(std::string line; std::getline(ifs, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        ip_pool.push_back(ipAddress(split(v.at(0), '.')));
    }
    std::ifstream ifsorted("tests/filter_1.tsv");
    std::vector<ipAddress> filterRes;
    for(std::string line; std::getline(ifs, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        filterRes.push_back(ipAddress(split(v.at(0), '.')));
    }
    ip_pool = sort(ip_pool);

    EXPECT_EQ(filter(ip_pool, 1), filterRes);
}

TEST(filter, new_filter_46_70_with_ipAddress)
{
    std::ifstream ifs("ip_filter.tsv");
    std::vector<ipAddress> ip_pool;
    for(std::string line; std::getline(ifs, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        ip_pool.push_back(ipAddress(split(v.at(0), '.')));
    }
    std::ifstream ifsorted("tests/filter_46_70.tsv");
    std::vector<ipAddress> filterRes;
    for(std::string line; std::getline(ifs, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        filterRes.push_back(ipAddress(split(v.at(0), '.')));
    }
    ip_pool = sort(ip_pool);
    EXPECT_EQ(filter(ip_pool, 46, 70), filterRes);
}

TEST(filter, new_filter_any_46_with_ipAddress)
{
    std::ifstream ifs("ip_filter.tsv");
    std::vector<ipAddress> ip_pool;
    for(std::string line; std::getline(ifs, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        ip_pool.push_back(ipAddress(split(v.at(0), '.')));
    }
    std::ifstream ifsorted("tests/filter_any_46.tsv");
    std::vector<ipAddress> filterRes;
    for(std::string line; std::getline(ifs, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        filterRes.push_back(ipAddress(split(v.at(0), '.')));
    }
    ip_pool = sort(ip_pool);
    EXPECT_EQ(filter_any(ip_pool, 46), filterRes);
}

