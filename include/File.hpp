#ifndef FILE_HPP
#define FILE_HPP

#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#include "boost/filesystem.hpp"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/detail/sha1.hpp"
#include "boost/crc.hpp"


class File {
public:
    File(short blocksize, std::filesystem::path pathToFile);

    static bool compareFiles(File a, File b, std::string hash);

    std::vector<std::string> getArray() { return this->mv_hashArray; }

    bool readBlock(std::string hash);

    bool getIsEof() { return this->isEof;}

private:
    std::vector<std::string> mv_hashArray; 
    size_t m_blockSize;
    std::shared_ptr<std::ifstream> mp_file;
    bool isEof;
};

#endif //FILE_HPP