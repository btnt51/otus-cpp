#include <iostream>
#include "../include/allocator.hpp"
#include "../include/ownlist.hpp"

int main(int, char **) {
	try {
		auto map1 = std::map<int, int>{};
		for(auto i = 0; i < 10; ++i) {
			map1[i] = factorial(i);
		}
		
		for(auto &el : map1) {
			std::cout << el.first << " " << el.second << std::endl;
		}


		auto map2 = std::map<int, int, std::less<int>,
			ownAllocator<std::pair<
					const int, int>, 10> >{};

		for(auto i = 0; i < 10; ++i) {
			map2[i] = factorial(i);
		}
		
		for(auto &el : map2) {
			std::cout << el.first << " " << el.second << std::endl;
		}

		auto list = ownList<int>{}; 
		for(int i = 0; i < 10; ++i){
			list.emplace(i);
		}


		for(auto it = list.begin(); it != list.end(); ++it) {
			std::cout << *it << "\n"; 
		}

		ownList<int, ownAllocator<Node<int>, 10> > list2; 
		for(int i = 0; i < 10; ++i){
			list2.emplace(i);
		}


		for(auto it = list2.begin(); it != list2.end(); ++it) {
			std::cout << *it << "\n"; 
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
