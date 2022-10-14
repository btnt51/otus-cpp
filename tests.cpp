#include <fstream>
#include "ipfilter.hpp"
#include "googletest/googletest/include/gtest/gtest.h"



TEST(test_build, split)
{
    std::vector<std::string> t = {"11", "22"};
    EXPECT_EQ(split("11.22", '.'), t);
}

TEST(test_build, sort)
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

TEST(test_build, filter_1)
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

TEST(test_build, filter_46_70)
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

TEST(test_build, filter_any_46)
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

