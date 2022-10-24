#include <iostream>

int main(int, char **) {
	try {

	} 
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
