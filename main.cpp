#include "lib.h"

#include <iostream>

int main(int, char **) {
	std::cout << "Build: " << build() << std::endl;
	std::cout << "Hello, world!" << std::endl;
	return 0;
}
