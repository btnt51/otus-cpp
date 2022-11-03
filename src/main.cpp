#include <iostream>
#include "../include/allocator.hpp"
#include "../include/ownlist.hpp"

int main(int, char **) {
	auto list = ownList<long>{}; 
    for(int i = 0; i < 10; ++i){
        list.emplace(factorial(i));
    }


    for(auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << "\n"; 
	}

	try {
		std::cout << "MAP 1" << std::endl;
		auto map1 = std::map<int, int>{};
		for(auto i = 0; i < 10; ++i) {
			map1[i] = factorial(i);
		}
		
		for(auto &el : map1) {
			std::cout << el.first << " " << el.second << std::endl;
		}


		std::cout << "MAP 2" << std::endl;
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
	}
	catch(std::bad_alloc &ba) {
		std::cerr << ba.what() << std::endl;
	}
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
