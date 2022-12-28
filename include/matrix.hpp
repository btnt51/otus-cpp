/**
 * @file matrix.hpp
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief Основной аголовочный файл матрицы описывающий обёртку над классом Element
 * @version 0.1
 * @date 2022-12-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <utility>
#include <vector>
#include <tuple>
#include <map>

#include "matrixUtil.hpp"

using cord = std::pair<int, int>;

template<typename Type, Type defaultValue = 0>
class Matrix {
public:
using iterator = typename std::map<cord, Element<Type, defaultValue> >::iterator;

    //template<typename Type, Type defaultValue>
    Matrix() {
    }


    Type getDefValue() {
        return defaultValue;
    }

    MatrixHelper<Type, defaultValue> operator[] (int row) {
        return MatrixHelper<Type, defaultValue>(*this, row);
    } 

    std::map<cord, Element<Type, defaultValue> > &getData() {
        return _data;
    }

    iterator begin() { return _data.begin();}

    iterator end() { return _data.end(); }
    size_t size() { return _data.size();}



private:
    //size_t size = 0;

    std::map<cord, Element<Type, defaultValue> > _data;

    
    
};



#endif //MATRIX_H