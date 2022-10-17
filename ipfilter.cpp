#include "ipfilter.hpp"

std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


std::vector<std::vector<std::string> > sort(const std::vector<std::vector<std::string> > &inVec) {
    std::vector<std::vector<std::string> > result = inVec;
    std::sort(result.begin(), result.end(), [](auto &left, auto &right){
        std::vector<int> tl;
        std::vector<int> tr;
        for(size_t i = 0; i < left.size(); ++i) {
            tl.push_back(std::stoi(left.at(i)));
            tr.push_back(std::stoi(right.at(i)));
        }
        if(tl < tr)
            return true;
        else
            return false;
    });
    std::reverse(result.begin(), result.end());
    return result;
}


void print(const std::vector<std::vector<std::string> > &inVec) {
    for(std::vector<std::vector<std::string> >::const_iterator ip = inVec.cbegin(); ip != inVec.cend(); ++ip) {

        for(std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
            if (ip_part != ip->cbegin()) {
                std::cout << ".";
            }

            std::cout << *ip_part;
        }

        std::cout << std::endl;
    }
}

std::string helpFunc(int a) {
    return std::to_string(a);
}


std::vector<std::vector<std::string> > filter_any(const std::vector<std::vector<std::string> > &inVec, int num) {
    std::vector<std::vector<std::string> > result;
    auto byte = helpFunc(num);
    std::copy_if(inVec.begin(), inVec.end(), std::back_inserter(result), [&byte](auto ip){
        for(auto ipPart : ip) {
            if(ipPart == byte)
                return true;
        }
        return false;
    });
    return result;
}
