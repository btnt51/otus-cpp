#include "File.hpp"


#include <iostream>

std::string getSHA1(const std::string& p_arg) {
    boost::uuids::detail::sha1 sha1;
    sha1.process_bytes(p_arg.data(), p_arg.size());
    unsigned hash[5] = {0};
    sha1.get_digest(hash);

    // Back to string
    char buf[41] = {0};

    for (int i = 0; i < 5; i++)
    {
        std::snprintf(buf + (i << 3), 40, "%08x", hash[i]);
    }

    return std::string(buf);
}


std::string getCRC32(const std::string& my_string) {
    boost::crc_32_type result;
    result.process_bytes(my_string.data(), my_string.length());
    std::stringstream ss;
    ss << result.checksum();
    return ss.str();
}


File::File(short blocksize, std::filesystem::path pathToFile) :
    m_blockSize(blocksize) {
    isEof = false;
    this->mp_file = std::make_shared<std::ifstream>(pathToFile, std::ios::in|std::ios::binary);
    this->mp_file->seekg(0);
}


bool File::compareFiles(File a, File b, std::string hash) {
    if(a.mv_hashArray.empty())
        a.readBlock(hash);
    if(b.mv_hashArray.empty())
        b.readBlock(hash);
    int k = 0;
    while(!a.getIsEof() && !b.getIsEof()) {
        std::cout << "A: " << a.mv_hashArray[k] << std::endl;
        std::cout << "B: " << b.mv_hashArray[k] << std::endl;
        if(a.mv_hashArray[k] != b.mv_hashArray[k])
            return false;
        if(!a.readBlock(hash))
            break;
        if(!b.readBlock(hash))
            break;
        std::cout << ++k << std::endl;
    }
    if(a.mv_hashArray.size() != b.mv_hashArray.size())
        return false;
    return true;
}

bool File::readBlock(std::string hash) {
    if(mp_file->peek() == EOF) {
        this->isEof = true;
        return false;
    }
    if(this->mp_file->is_open()) {
        std::string block(this->m_blockSize, '\0');
        mp_file->seekg(mv_hashArray.size()*m_blockSize);
        mp_file->read(&block[0], this->m_blockSize);
        if (hash == "SHA1") {
            mv_hashArray.emplace_back(getSHA1(block));
        } else {
            mv_hashArray.emplace_back(getCRC32(block));
        }
        
        return true;
    }
    return false;
}