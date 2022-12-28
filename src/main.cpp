#include <iostream>

#include "../include/matrix.hpp"



int main(int, char **) {
	try {
		Matrix<int, 0> matrix;
		//matrix[0][9] = 9;
		for(int i = 0; i <= 9; i++) {
			for(int j = 0; j <= 9; j++) {
				if(i == j) {
					matrix[i][j] = i;
				}
			}
		}
		//matrix[0][9] = 9;
	 	for(int i = 0; i <= 9; ++i) {
			for(int j = 9; j >= 0; j--) {
				if((9-i)==j)
					matrix[i][j] = j;
			}
		}

		for(int i = 1; i <= 9; ++i) {
			for(int j = 1; j <= 9; ++j) {
				std::cout << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}

		std::cout << matrix.size() << std::endl;

		for(auto c: matrix) {
			int x, y, v;
			std::tie(x, y, v) = c.second;
			std::cout << x << y << v << std::endl;
		}
	} 
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
