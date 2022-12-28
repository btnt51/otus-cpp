/**
 * @file matrixUtil.hpp
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief Заголовочный файл реализующий утилиты для обеспечения работы матрицы
 * @version 0.1
 * @date 2022-12-25
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef VALUE_HPP
#define VALUE_HPP

#include <utility>
#include <algorithm>

template<typename Type, Type defaultValue> class Matrix;


template<typename Type, Type defaultValue = 0>
class Element {
public:
    Element(Matrix<Type, defaultValue> &matrix, Type val) : _matrix(matrix), _value(val) {}

    

    void setCoord(int &row, int &column) {
        coord.first = row;
        coord.second = column;
    }

    void setCoord(std::pair<int, int> &anCoord) {
        coord = anCoord;
    }


    void operator=(Type const& value) {
        if(value == defaultValue) {
            auto iter = _matrix.getData().find(coord);

            if(iter != _matrix.getData().end()) {
                _matrix.getData().erase(iter);
            }
        } else {
            _matrix.getData().insert(std::make_pair(this->coord, Element(_matrix, value, this->coord)));
        }
    }

    operator std::tuple<int&, int&, int&>() {
        return std::tuple<int&, int&, int&>(this->coord.first, this->coord.first, this->_value);
    }
    

    template<typename Xtype, Xtype defaultValueX>
    friend bool operator==(const Element& lhs, const Element<Xtype, defaultValueX>& rhs) {
        return lhs.getValue() == rhs.getValue();
    }

    friend bool operator==(const Element& lhs, const Element& rhs) {
        return lhs.getValue() == rhs.getValue();
    }

    bool operator==(const Type& rhs) const {
        return this->getValue() == rhs;
    }

    friend std::ostream &operator<<(std::ostream &os, Element<Type, defaultValue> const &obj) {
        if (obj._value == defaultValue)
            os << defaultValue;
        else
            os << obj._value;
        return os;
    }

    Type getValue() const {
        return this->_value;
    }


private:
    Element(Matrix<Type, defaultValue> &matrix, 
            Type val, std::pair<int, int> cond) : 
            _matrix(matrix), _value(val), coord(cond) 
            {   }

    Matrix<Type, defaultValue> &_matrix;
    Type _value = defaultValue;
    std::pair<int, int> coord;
    int _row;
    int _column;

};

template<typename Type, Type defaultValue = 0>
class MatrixHelper {
public:

    explicit MatrixHelper(Matrix<Type, defaultValue> &matrix_, int row_)
            : _matrix(matrix_)
            , _newCell(Element<Type, defaultValue>(_matrix, defaultValue))
            , _row(row_)
    {  }

    Element<Type, defaultValue> &operator[](int col) {
        auto coord = std::make_pair(_row, col);
        auto it = _matrix.getData().find(coord);
        if (it != _matrix.getData().end()) {
            it->second.setCoord(coord);
            return it->second;
        } else {
            _newCell.setCoord(coord);
            return _newCell;
        }
    }

private:
    Matrix<Type, defaultValue> &_matrix;
    Element<Type, defaultValue> _newCell;
    int _row;

};


#endif //VALUE_HPP