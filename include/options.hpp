/**
 * @file options.hpp
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief File contains class options that provides work with boost_options.
 * @version 0.1
 * @date 2023-03-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef OPTIONS_HPP
#define OPTIONS_HPP


#include <filesystem>
#include <iostream>
#include <vector>

#include "boost/program_options.hpp"


namespace po = boost::program_options;

using Path = std::filesystem::path;
using description = po::options_description;

/**
 * @brief Options that provides work with boost_options like with one unit.
 * 
 */
class Options {
public:
/**
 * @brief Construct a new Options object
 * 
 * @param argc amount of args from console
 * @param argv args from console
 */
    Options(int &argc, char **argv);

public:
    std::vector<Path> scanDir;
    std::vector<Path> excludeDir;
    int depth;
    int fileSize;
    std::string mask;
    int blockSize;
    std::string hashAlgo;

private:
/**
 * @brief defualt initizialation for possible args
 * 
 */
    void initDescription();

    description m_desc;
    po::variables_map m_vm;

};

#endif //OPTIONS_HPP