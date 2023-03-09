/**
 * @file Filter.hpp
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief File that contains declarations of 2 Filters. FileFilter checks path to file (file) by it's name and size. 
 * DirFilter checks path to dir (dir) by it's depth and not in exclude directories vector.
 * @version 0.1
 * @date 2023-03-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef FILTER_HPP
#define FILTER_HPP

#include <vector>

#include "Mask.hpp"

namespace fs = std::filesystem;


using Path = fs::path;

using ScanPath = std::pair<Path, std::size_t>;


/**
 * @brief FileFilter checking path to file (file) by it's name and size.
 * 
 */
class FileFilter {
public:
/**
 * @brief Construct a new File Filter object
 * 
 * @param regex mask for regex
 * @param sizeOfFile minimal size of file
 */
    FileFilter(std::string regex=".*", std::size_t sizeOfFile=1);
/** 
 * @brief validate file path by regex mask and size of File
 * 
 * @param path to file
 * @return true if path valid
 * @return false if path is not valid
 */
    auto isValid(Path path)->bool;

private:
    Mask m_mask;
    std::size_t m_sizeOfFile;
};

/**
 * @brief DirFilter checks path to dir (dir) by it's depth and not in exclude directories vector.
 * 
 */
class DirFilter {
public:
/**
 * @brief Construct a new Dir Filter object
 * 
 * @param excludeDirs dirs than should not be in prepared for checking pathes
 * @param depth depth from root (base start folder) 
 */
    DirFilter(std::vector<Path> excludeDirs=std::vector<Path>(0,""), std::size_t depth=0);

/**
 * @brief chec
 * 
 * @param scan pair of path and it's depth
 * @return true if path valid
 * @return false if path is not valid 
 */
    auto isValid(ScanPath scan)->bool;

private:
    std::vector<Path> m_excludeDirs;
    std::size_t m_depth;
};

#endif //FILTER_HPP