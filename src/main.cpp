#include <iostream>
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/detail/sha1.hpp"
#include "boost/crc.hpp"


std::string get_sha1(const std::string& p_arg)
{
    boost::uuids::detail::sha1 sha1;
    sha1.process_bytes(p_arg.data(), p_arg.size());
    unsigned hash[5] = {0};
    sha1.get_digest(hash);

    // Back to string
    char buf[41] = {0};

    for (int i = 0; i < 5; i++)
    {
        std::snprintf(buf + (i << 3), 40, "%08x", hash[i]);
    }

    return std::string(buf);
}

uint32_t GetCrc32(const std::string& my_string) {
    boost::crc_32_type result;
    result.process_bytes(my_string.data(), my_string.length());
    return result.checksum();
}

int main(int argc, char ** argv) {
	try {
		if (argc < 2) {
      		std::cerr << "Call: " << *argv << " STR\n";
      		return 1;
		}

		std::cout << get_sha1(argv[1]) << '\n';

		std::cout << GetCrc32(argv[1]) << '\n';

	} 
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
