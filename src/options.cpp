#include "options.hpp"

Options::Options(int &argc, char **argv) {
    initDescription();
    po::store(po::parse_command_line(argc, argv, m_desc), m_vm);
    po::notify(m_vm);

    if(m_vm.count("help")) {
        std::cout << m_desc << std::endl;
    }
}

void Options::initDescription() {

    m_desc.add_options()
            ("help,h", "Показать помощь");
    m_desc.add_options()
        ("scanDir,scDir", po::value<std::vector<Path> >(&scanDir)->default_value(std::vector<Path>(), "."), 
        "Директории для сканирования (может быть несколько)")
        ("excludeDir,exDir", po::value<std::vector<Path> >(&excludeDir)->default_value(std::vector<Path>(), ""),
        "Директории для исключения из сканирования (может быть несколько");
    m_desc.add_options()
        ("depth,d", po::value<int>(&depth)->default_value(0) , 
        "уровень сканирования (один на все директории, " 
        "0 - только указанная директория без вложенных)")
        ("fileSize,fs", po::value<int>(&fileSize)->default_value(1), 
        "минимальный размер файла в байтах, по умолчанию проверяются" 
        "все файлы больше 1 байта");

    m_desc.add_options()
        ("masks,m", po::value<std::string>(&mask)->default_value(".*"), 
        "маски имен файлов разрешенных для сравнения "
        "(не зависят от регистра)")
        ("size,S", po::value<int>(&blockSize)->default_value(5), "размер блока,"
        "которым производится чтения файлов, по умолчанию 5")
        ("hash,H", po::value<std::string>(&hashAlgo)->default_value("SHA1"), 
        "Выбреите алгоритм хэш-функции: SHA1, CRC32");     
}