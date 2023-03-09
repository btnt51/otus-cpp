#include "Mask.hpp"
#include <iostream>

Mask::Mask(std::string maskStr) {
    //this->prepareString(maskStr);
    m_reg = std::regex(maskStr, std::regex_constants::icase);
}

bool Mask::validateFile(std::filesystem::path path) {
    if(std::regex_match(path.stem().string(), this->m_reg))
        return true;
    else
        return false;
}

void Mask::prepareString(std::string &maskStr) {
    std::regex_replace(maskStr, std::regex("."), "\\.");
    std::regex_replace(maskStr, std::regex("*"), "\\*");
    std::regex_replace(maskStr, std::regex("?"), "\\?");
    std::regex_replace(maskStr, std::regex("\\?"), ".");
    std::regex_replace(maskStr, std::regex("\\*"), ".*");
}