/**
 * @file Mask.hpp
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief File contains declaration of mask for regex.
 * @version 0.1
 * @date 2023-03-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef MASK_HPP
#define MASK_HPP

#include <regex>
#include <filesystem>

/**
 * @brief File that validates name of file by regex.
 * 
 */
class Mask {
public:
/**
 * @brief Construct a new Mask object
 * 
 * @param maskStr string for constructing regex
 */
    Mask(std::string maskStr=".*");
    
    /**
     * @brief function that validates filename by regex
     * 
     * @param path path to file
     * @return true if filename is valid
     * @return false if filename is not valid
     */
    auto validateFile(std::filesystem::path path)->bool;
    
private:
/**
 * @brief inner function for preparing result
 * 
 * @param maskStr reference to string
 */
    void prepareString(std::string &maskStr);

    std::regex m_reg;

};

#endif //MASK_HPP