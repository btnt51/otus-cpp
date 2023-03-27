#include <iostream>

#include "async.h"

int main([[maybe_unused]] int argv, [[maybe_unused]]char **argc) {
	try {
		auto h = async::connect(5);
		auto h2 = async::connect(6);
		async::receive(h, "1", 1);
		async::receive(h2, "11\n", 2);
		async::receive(h, "2\n3\n4\n5\n6\n{\na\n", 15);
		async::receive(h2, "12\n13\n14\n15\n16\n{\n17\n", 15);
		async::receive(h, "b\nc\nd\n}\n89\n", 11);
		async::disconnect(h);
		async::disconnect(h2);
	} 
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
