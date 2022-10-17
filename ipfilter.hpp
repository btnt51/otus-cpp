#pragma once
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

std::vector<std::string> split(const std::string &str, char d);


std::vector<std::vector<std::string> > sort(const std::vector<std::vector<std::string> > &inVec);

std::string helpFunc(int a);

std::vector<std::vector<std::string> > filter_any(const std::vector<std::vector<std::string> > &inVec, int byte);

void print(const std::vector<std::vector<std::string> > &inVec);

template<typename...T>
std::vector<std::vector<std::string> > filter(const std::vector<std::vector<std::string> > &inVec, T...Bytes)
{
    std::vector<std::vector<std::string> > result;
    std::vector<int> bytes = {{Bytes...}};
    if(bytes.size() == 1) {
        std::vector<std::string> byte;
        byte.push_back(helpFunc(bytes[0]));
        std::copy_if(inVec.begin(), inVec.end(), std::back_inserter(result), [&byte](auto el){
            if(el.at(0) == byte.at(0))
                return true;
            return false;
        });
        return result;
    } else {
        std::vector<std::string> byte;
        byte.push_back(helpFunc(bytes[0]));
        byte.push_back(helpFunc(bytes[1]));
        std::copy_if(inVec.begin(), inVec.end(), std::back_inserter(result), [&byte](auto el){
            if(el.at(0) == byte[0] && el.at(1) == byte[1])
                return true;
            return false;
        });
        return result;
    }
    return result;
}
