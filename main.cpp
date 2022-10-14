#include "ipfilter.hpp"

int main(void)
{
    try
    {
		std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        ip_pool = sort(ip_pool);
		print(ip_pool);
		std::vector<std::vector<std::string> > ip;
		ip = filter(ip_pool, 1);
		print(ip);
        ip.clear();
        ip = filter(ip_pool, 46, 70);
		print(ip);
        ip.clear();
        ip = filter_any(ip_pool, 46);
		print(ip); 
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
