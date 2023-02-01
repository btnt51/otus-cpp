#include <iostream>
#include "cmd.hpp"
#include "logger.hpp"
#include "outputCMD.hpp"

int main([[maybe_unused]] int argv, char **argc) {
	try {
		//std::cout << (argc[1]) << std::endl;
        std::shared_ptr<Logger> log(new Logger());
        std::shared_ptr<outputCMD> output(new outputCMD());
		CMD cmd(std::stoi(std::string(argc[1])));
        cmd.subscribe(log);
        cmd.subscribe(output);
		cmd.takeConsoleControl();
        cmd.unsubscribe(log->getSubscriberId());
        cmd.unsubscribe(output->getSubscriberId());
	} 
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
