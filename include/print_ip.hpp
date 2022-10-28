/**
    \file
    \mainpage Homework 3
	\brief Homework 
	\author btnt51
	\date October 2022
	\warning This work was done for educational purposes.
*Implementing overloads of the function of printing some IP-address using SFINAE.
*/

#ifndef PRINT_IP_H
#define PRINT_IP_H

#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <cstdint>

/// @brief Namespace that contains aliases for sfinae
namespace utility{
    template<typename T>
    using enable_strings_t = std::enable_if_t< std::is_same_v<T, std::string> >;

    template<typename T>
    using enable_nums_t = typename std::enable_if_t< std::is_integral_v<T> && !std::is_same_v<T, bool> >;

    template<template <typename, typename> typename Container, typename T, typename Alloc=std::allocator<T>>
    using enabale_containers_t = typename std::enable_if_t< std::is_same_v< Container <T, Alloc>, std::vector<T, Alloc> > 
                                                            || std::is_same_v< Container <T, Alloc>, std::list<T, Alloc> >>;

    template<typename T, typename... Args>
    using enable_tuple_t = typename std::enable_if_t <std::conjunction_v<std::is_same<T, Args>...> >;                                                
}



/// @brief Printing in std::cout IP-address that represented as std::string 
/// @tparam T typename T
/// @param ipAddress input IP-address
template<typename T>
utility::enable_strings_t<T> print_ip(T ipAddress){
    std::cout << ipAddress << std::endl;
}


/// @brief Printing in std::cout IP-address that represented as integral by bytes
/// @tparam T typename 
/// @param ipAddress input IP-address
template<typename T>
utility::enable_nums_t<T> print_ip(T num) {
    union {
        uint8_t bytes[sizeof(T)];
        T value;
    };
    value = num;
    if constexpr (sizeof(T) == 0) {
        std::cout << +bytes[0] << std::endl;
        return;
    } else {
        for(std::size_t t = sizeof(T) -1; t; --t) {
            std::cout << +bytes[t] << ".";
        }
        std::cout << +bytes[0] << std::endl;
    }
}

/// @brief Printing in std::cout IP-address that represented as elements of container
/// @tparam Container template of container
/// @tparam T typename 
/// @tparam Alloc template of allocator
/// @param container inputes conatiner with Ip-address
template<template <typename, typename> typename Container, typename T, typename Alloc=std::allocator<T>>
utility::enabale_containers_t<Container, T, Alloc> print_ip(Container<T, Alloc> container) {
    for(auto it = container.begin(); it != container.end(); it++) {
        if(static_cast<long unsigned int>(std::distance(container.begin(), it)) == container.size()-1)
            break;
        std::cout << *it << ".";
    }
    std::cout << container.back() << std::endl;
}


/// @brief Printing in std::cout IP-address that represented as elements of tuple
/// @tparam T typename
/// @tparam Indexes indexes of a tuple
template<typename T, size_t...Indexes>
void print(T tuple, std::index_sequence<Indexes...>) {
    (..., (std::cout << (Indexes == 0? "" : ".") << std::get<Indexes>(tuple)));
    std::cout << std::endl;
}

/// @brief Printing in std::cout IP-address that represented as elements same type of tuple
/// @tparam T typename
/// @tparam Args other elements of a tuple
template<typename T,typename... Args>
utility::enable_tuple_t<T, Args...> print_ip(std::tuple<T, Args...> tuple) {
    print(tuple, std::make_index_sequence<sizeof...(Args)+1>());
}

#endif //PRINT_IP_H