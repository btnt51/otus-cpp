#include <iostream>
#include <sstream>
#include <gtest/gtest.h>
#include "../include/allocator.hpp"


TEST(Test_allocator, map) {
    std::stringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());
    auto map2 = std::map<
			int,
			int,
			std::less<int>,
			ownAllocator<std::pair<
					const int, int>, 10> >{};

    for(auto i = 0; i < 10; ++i) {
        map2[i] = factorial(i);
    }
    
    for(auto &el : map2) {
        std::cout << el.first << " " << el.second << std::endl;
    } 
    std::cout.rdbuf(cout_buff);
    ASSERT_EQ(local.str(), "0 1\n1 1\n2 2\n3 6\n4 24\n5 120\n6 720\n7 5040\n8 40320\n9 362880\n");
}

