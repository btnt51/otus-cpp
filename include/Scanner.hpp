/**
 * @file Scanner.hpp
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief File that contains declarations of 2 Scanners. FileScanner validation and preparing pathes. 
 * DuplicateScanner scanning pathes for duplicate files.
 * @version 0.1
 * @date 2023-03-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SCANNER_HPP
#define SCANNER_HPP


#include <filesystem>
#include <iostream>
#include <vector>
#include <set>

#include "Filter.hpp"
#include "File.hpp"


using fsRecIter = fs::recursive_directory_iterator;


using Results = std::vector<std::pair<Path, std::set<Path> > >;


/**
 * @brief FileScanner validation and preparing pathes by using filters.
 * 
 */
class FileScanner {
public:
/**
 * @brief Construct a new File Scanner object
 * 
 * @param excludeDirs Pathes that needed to be excluded from pathes to scan.
 * @param regex string that will be used for constructing std::regex
 *              and using for filtering files by their names.
 * @param depth depth of checking files and directories.
 * @param sizeOfFile minimal size of file.
 */
    FileScanner(std::vector<Path> excludeDirs=std::vector<Path>(0,""),
                std::string regex=".*", std::size_t depth=0,
                std::size_t sizeOfFile=1);

    
/**
 * @brief validate pathes with with special filters
 * 
 * @param searchDirs pathes that will be validated
 * @return std::set<Path> of files that's needs to be checked for duplicates
 */
    auto validatePathes(std::vector<Path> &searchDirs) -> std::set<Path>;


private:
    FileFilter m_fileFilter;
    DirFilter m_dirFilter;

};

/**
 * @brief DuplicateScanner scanning pathes for duplicate files via class File.
 * 
 */
class DuplicateScanner {
public:
/**
 * @brief Construct a new Duplicate Scanner object
 * 
 * @param filesForDuplicates files that's needs to be checked for duplicates
 * @param hash hash algorithm that will be used for comparing files.
 */
    DuplicateScanner(std::set<Path> filesForDuplicates, std::string hash);

/**
 * @brief checking files for duplicates
 * 
 * @return Results pairs of Path and set of pathes with duplicates
 */
    auto checkFiles()->Results;

private:
    std::set<Path> filesForDuplicates;
    std::vector<File> files;
    std::string m_hash;
};


#endif //SCANNER_HPP