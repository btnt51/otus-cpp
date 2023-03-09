#include "Filter.hpp"
#include <filesystem>




FileFilter::FileFilter(std::string regex, std::size_t sizeOfFile) {
    this->m_mask = Mask(regex);
    this->m_sizeOfFile = sizeOfFile;
}

auto FileFilter::isValid(Path path)->bool {
    if(fs::exists(path)) {
        if (fs::file_size(path) > this->m_sizeOfFile) {
            if(m_mask.validateFile(path))
                return true;
        }
    }
    return false;
}


DirFilter::DirFilter(std::vector<Path> excludeDirs,
 std::size_t depth) : m_excludeDirs(excludeDirs), m_depth(depth) {

 }

 auto DirFilter::isValid(ScanPath scan)->bool {
    auto notInVector = [&](auto &path)->bool{
        return std::find(m_excludeDirs.begin(), m_excludeDirs.end(), path) == m_excludeDirs.end();
    };
    if(scan.second <= m_depth && (notInVector(scan.first) || this->m_excludeDirs.empty())) {
            return true;
    }
    return false;
 }
