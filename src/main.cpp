#include <iostream>
#include "cmd.hpp"

int main([[maybe_unused]] int argv, char **argc) {
	try {
		std::cout << (argc[1]) << std::endl;
		CMD cmd(std::stoi(std::string(argc[1])));
		cmd.takeConsoleControl();
	} 
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
