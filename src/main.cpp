#include <iostream>
#include "boost/filesystem.hpp"
#include "boost/program_options.hpp"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/detail/sha1.hpp"
#include "boost/crc.hpp"


//sha1
//crc32

std::string get_sha1(const std::string& p_arg) {
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

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main([[maybe_unused]] int argc, [[maybe_unused]] char ** argv) {
	try {
        po::options_description desc("General options");
        std::string hash_type;
        desc.add_options()
            ("help,h", "Показать помощь");
        desc.add_options()
            ("scanDir,scDir", po::value<std::vector<std::string> >(), 
            "Директории для сканирования (может быть несколько)")
            ("excludeDir,exDir", po::value<std::vector<std::string> >(),
            "Директории для исключения из сканирования (может быть несколько");
        desc.add_options()
            ("depth,d", po::value<int>() , 
            "уровень сканирования (один на все директории, " 
            "0 - только указанная директория без вложенных)")
            ("fileSize,fs", po::value<int>(), 
            "минимальный размер файла в байтах, по умолчанию проверяются" 
            "все файлы больше 1 байта");

        desc.add_options()
            ("masks,m", po::value<int>(), 
            "маски имен файлов разрешенных для сравнения "
            "(не зависят от регистра)")
            ("size,S", po::value<int>(), "размер блока, которым производится чтения файлов")
            ("hash,H", po::value<std::string>(&hash_type)->default_value("SHA1"), 
            "Выбреите алгоритм хэш-функции: SHA1, CRC32");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        if(vm.count("help")) {
            std::cout << desc << std::endl;
        }

        if(vm.count("scanDir")) {
            std::cout << vm["scanDir"].as<std::vector<std::string> >()[0] << std::endl;
            fs::directory_iterator begin(vm["scanDir"].as<std::vector<std::string> >()[0]);
            fs::directory_iterator end; 
            for (; begin != end; ++ begin) {
                fs::file_status fs = fs::status(*begin);
                switch (fs.type()) {
                    case boost::filesystem::regular_file: 
                        std::cout << "FILE ";
                        break;
                    case boost::filesystem::symlink_file: 
                        std::cout << "SYMLINK ";
                        break;
                    case boost::filesystem::directory_file: 
                        std::cout << "DIRECTORY ";
                        break;
                    default: 
                        std::cout << "OTHER ";
                        break;
                    }
                    if (fs.permissions() & boost::filesystem::owner_write) {
                        std::cout << "W ";
                    } else {
                        std::cout << " ";
                    }
                    std::cout << *begin << '\n';
                }
            }
    

        if(vm["hash"].as<std::string>() == "SHA!") {
            std::cout << get_sha1("text") << '\n';
        } else {
            std::cout << GetCrc32("text") << '\n';
        }

		/* if (argc < 2) {
      		std::cerr << "Call: " << *argv << " STR\n";
      		return 1;
		} */
        
		//std::cout << get_sha1(argv[1]) << '\n';

		//std::cout << GetCrc32(argv[1]) << '\n';
    }
    catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
