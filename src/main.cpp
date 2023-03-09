#include <iostream>


#include "options.hpp"
#include "Scanner.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char ** argv) {
	try {
        Options options(argc, argv);


        FileScanner fileScanner(options.excludeDir, 
                options.mask, options.depth, options.fileSize);

        auto filesToSeacrhDuplicates = fileScanner.validatePathes(options.scanDir);


        DuplicateScanner duplicateScanner(filesToSeacrhDuplicates, options.hashAlgo);

        auto results = duplicateScanner.checkFiles();

        for(auto &el : results) {
            std::cout << el.first << " has " << el.second.size() << " duplicates: " << std::endl;
            for(auto &path : el.second) {
                std::cout << path << std::endl;
            }
            std::cout << std::endl;
        }
    }
    catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
