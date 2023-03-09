#include "File.hpp"



auto getSHA1(const std::string& p_arg)->std::string {
    boost::uuids::detail::sha1 sha1;
    sha1.process_bytes(p_arg.data(), p_arg.size());
    unsigned hash[5] = {0};
    sha1.get_digest(hash);
    char buf[41] = {0};
    for (int i = 0; i < 5; i++)
    {
        std::snprintf(buf + (i << 3), 40, "%08x", hash[i]);
    }

    return std::string(buf);
}


auto getCRC32(const std::string& my_string)->std::string {
    boost::crc_32_type result;
    result.process_bytes(my_string.data(), my_string.length());
    std::stringstream ss;
    ss << result.checksum();
    return ss.str();
}


File::File(fs::path pathToFile, short blocksize) :
    m_blockSize(blocksize), pathToFile(pathToFile) {
    isEof = false;
    this->mp_file = std::make_shared<std::ifstream>(pathToFile, std::ios_base::in|std::ios_base::binary);
    int zero  = 0;
    this->mp_file->seekg(zero);
}


bool File::compareFiles(File &a, File &b, std::string hash) {
    if(a.mv_hashArray.size() == 0)
        if(!a.readBlock(hash))
            return false;
    if(b.mv_hashArray.size() == 0)
        if(!b.readBlock(hash))
            return false;
    std::size_t k = 0;
    bool bO = true;
    while(bO) {            
        if(a.mv_hashArray[k] != b.mv_hashArray[k]) {
            bO = false;
            return false;
        }
        if(!a.isEof){
            if(!a.readBlock(hash) && k >= a.mv_hashArray.size() )
                break;
        }
        if(!b.isEof) {
            if(!b.readBlock(hash) && k > b.mv_hashArray.size())
                break;
        }
        if(a.isEof && k >= a.mv_hashArray.size())
            break;  
        if(b.isEof && k >= b.mv_hashArray.size())
            break;
        ++k;
    }
    if(a.mv_hashArray.size() != b.mv_hashArray.size()) {
        return false;
    }
    return true;
}

bool File::readBlock(std::string hash) {
    if(fs::is_empty(pathToFile)) {
        this->isEof = true;
        this->mp_file->close();
        return false;
    }

    if(mp_file->peek() == std::istream::traits_type::eof()) {
        if(mp_file->eof()) {
            this->isEof = true;
            this->mp_file->close();
            return false;
        }
    }
    
    if(this->mp_file->is_open()) {
        std::string block(this->m_blockSize, '\0');
        std::size_t seek = mv_hashArray.size()*m_blockSize;
        mp_file->seekg(seek);
        mp_file->read(&block[0], this->m_blockSize);
        if (hash == "SHA1") {
            mv_hashArray.emplace_back(getSHA1(std::string(block.begin(), block.end())));
        } else {
            mv_hashArray.emplace_back(getCRC32(std::string(block.begin(), block.end())));
        }
        
        return true;
    }
    return false;
}