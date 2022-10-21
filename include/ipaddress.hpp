#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <vector>
#include <cassert>
#include <string>
#include <algorithm>
#include <ostream>
#include <array>

class ipAddress {
public:
    ipAddress() = delete;
    ipAddress(std::vector<std::string> ipAddressInString) {
        assert(ipAddressInString.size() != 4);
        for(auto i = 0; i < 4; ++i) {
            _Bytes[i] = std::stoi(ipAddressInString.at(i));
        }
    }

    ~ipAddress()=default;

    std::array<int, 4> getBytes() {
        return _Bytes;
    }

    friend std::ostream &operator<<(std::ostream &os, const ipAddress &address) {
        auto back_it = std::prev(address._Bytes.cend());
        for (auto it = address._Bytes.cbegin(); it != address._Bytes.cend(); ++it) {
            os << static_cast<int>(*it); // prevent interpreting the byte as character
            if (it != back_it) {
                os << ".";
            }
        }
        return os;
    }

    friend inline bool operator< (const ipAddress &leftAddress, const ipAddress &rightAddress) {
        return leftAddress._Bytes < rightAddress._Bytes;
    }

    int at(size_t num) {
        assert(num > 3);
        return _Bytes.at(num);
    }

private:
    std::array<int, 4> _Bytes;

};





#endif //IPADDRESS_H