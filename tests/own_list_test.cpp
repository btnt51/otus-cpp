#include <iostream>
#include <sstream>
#include <gtest/gtest.h>
#include "../include/ownlist.hpp"
#include "../include/allocator.hpp"

TEST(Test_allocator, ownlist) {
    std::stringstream local;
    auto cout_buff = std::cout.rdbuf();
    std::cout.rdbuf(local.rdbuf());
    auto list = ownList<long>{};
    for(int i = 0; i < 10; ++i){
        list.emplace(factorial(i));
    }

    /* for(auto &el : list) {
        std::cout << el << std::endl;
    }  */

    for(auto it = list.begin(); it != list.end(); ++it)
        std::cout << *it << "\n";

    std::cout.rdbuf(cout_buff);
    ASSERT_EQ(local.str(), "1\n1\n2\n6\n24\n120\n720\n5040\n40320\n362880\n");
}