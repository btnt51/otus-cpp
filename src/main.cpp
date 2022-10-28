#include <iostream>
#include <vector>
#include <map>
#include "../include/allacator.hpp"

int main(int, char **) {
	try {
		/* std::cout << "MAP 1" << std::endl;
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
			Extended_Allocator<
				std::pair<
					const int, int>, 10> >{};

		std::cout << "MAP 2 TEST" << std::endl;
		for(auto i = 0; i < 10; ++i) {
			map2[i] = factorial(i);
		}
		
		for(auto &el : map2) {
			std::cout << el.first << " " << el.second << std::endl;
		}

 */
		auto v = std::vector<int, Extended_Allocator<int, 5>>{};
		//v.reserve(16);
		for (int i = 0; i < 4; ++i) {
			v.emplace_back(i);
			std::cout << "vector size = " << v.size() << std::endl;
			std::cout << std::endl;
		} 

		std::cout << "\n\n\n\nAfter creation\n\n\n\n" << std::endl;
		auto v2 = v;
		std::cout << "\n\n\n\nMAP\n\n\n\n" << std::endl;
		auto m = std::map<
			int,
			float,
			std::less<int>,
			Extended_Allocator<
				std::pair<
					const int, float>, 11> >{};

		for (int i = 0; i < 10; ++i) {
			std::cout << "\n\n" << i << "\n\n" << std::endl;
			m[i] = static_cast<float>(i); 
		}  
	} 
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
