/**
 * @file File.hpp
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief File contains declaration of class File. Provides work with filestreams.
 * @version 0.1
 * @date 2023-03-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef FILE_HPP
#define FILE_HPP

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/detail/sha1.hpp"
#include "boost/crc.hpp"

namespace fs = std::filesystem;

/**
 * @brief File class provides work with filestreams by block with fixed size. 
 * 
 */
class File {
public:
/**
 * @brief Construct a new File object
 * 
 * @param pathToFile path to file
 * @param blocksize size of block
 */
    File(fs::path pathToFile, short blocksize = 5);

/**
 * @brief static function for comparing 2 files
 * 
 * @param a first file
 * @param b second file
 * @param hash hash function
 * @return true if files are same
 * @return false if files are not same
 */
    static bool compareFiles(File &a, File &b, std::string hash);

    

private:
/**
 * @brief inner function for comparing files
 * 
 * @param hash hash functions
 * @return true if reading was okey
 * @return false if reading was with error, like end of file or smthg of that
 */
    bool readBlock(std::string hash);

private:
    std::vector<std::string> mv_hashArray; 
    size_t m_blockSize;
    std::shared_ptr<std::ifstream> mp_file;
    bool isEof;
    fs::path pathToFile;
};

#endif //FILE_HPP