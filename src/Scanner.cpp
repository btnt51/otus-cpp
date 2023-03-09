#include "Scanner.hpp"





FileScanner::FileScanner(std::vector<Path> excludeDirs,
                std::string regex, std::size_t depth, 
                std::size_t sizeOfFile) {

    this->m_dirFilter = DirFilter(excludeDirs, depth);
    this->m_fileFilter = FileFilter(regex, sizeOfFile);
}


auto FileScanner::validatePathes(std::vector<Path> &searchDirs)->std::set<Path> {
    std::vector<Path> result;
    std::vector<ScanPath> tempPathes;
    for(auto &path : searchDirs) {
        if(fs::exists(path) && fs::is_directory(path)) {
            fsRecIter iter(path, fs::directory_options::skip_permission_denied), end;
            while(iter != end) {
                ScanPath pathToScan = std::make_pair(iter->path(), iter.depth());;
                if(iter->is_directory() && !m_dirFilter.isValid(pathToScan)) {
                    iter.disable_recursion_pending();
                } else {
                    if(iter->is_regular_file() && m_dirFilter.isValid(pathToScan)) {
                        Path pathFromIter = iter->path();
                        if(iter->is_symlink()) {
                            pathFromIter = fs::absolute(fs::weakly_canonical(fs::read_symlink(pathFromIter)));
                        } 
                        if(m_fileFilter.isValid(pathFromIter)) {
                            result.push_back(pathFromIter);
                        }
                    }
                }
                iter++;
            }
        }
    }

    std::sort(result.begin(), result.end(), [](auto &left, auto &right) {
        return fs::file_size(left) > fs::file_size(right);
    });

    return std::set(result.begin(), result.end());
}


DuplicateScanner::DuplicateScanner(std::set<Path> filesForDuplicates, std::string hash) 
           : m_hash(hash){
    for(auto &el : filesForDuplicates) {
        files.emplace_back(File(el));
    } 
    this->filesForDuplicates = filesForDuplicates;
}

auto DuplicateScanner::checkFiles()->Results{
    Results resultOutput;
    for(std::size_t i = 0; i < files.size(); ++i) {
        std::set<Path> resultPerPath;
        for(std::size_t j = i + 1 ; j < files.size(); ++j) {
            auto it = filesForDuplicates.begin();
            std::advance(it, j);
            
            if(auto res = File::compareFiles(files[i], files[j], m_hash); res) {
                auto it = filesForDuplicates.begin();
                std::advance(it, j);
                resultPerPath.insert(*it);
            }
        }
        if(!resultPerPath.empty()) {
            auto it = filesForDuplicates.begin();
            std::advance(it, i);
            resultOutput.emplace_back(std::make_pair(*it, resultPerPath));
        }
    }
    return resultOutput;
}