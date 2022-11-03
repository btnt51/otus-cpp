#include <iostream>
#include "../include/allacator.hpp"

int main(int, char **) {
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
			custom_allocator<std::pair<
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
