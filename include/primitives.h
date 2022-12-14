/**
 * @file primitives.h
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief File that contains declaration of interface IPrimitive and declaration and defenetion of simple primitives like Circle, Square and Rectangle.
 * @version 0.1
 * @date 2022-12-12
 * @warning This work was done for educational purposes.
 * 
 */
#ifndef H_PRIMITIVE
#define H_PRIMITIVE

#include <tuple>
/// @brief Interface class for Primitives
class IPrimitive {
public:
    virtual std::pair<int, int> getCoordinates() = 0;

    virtual std::string getName() = 0;

    virtual ~IPrimitive() = default;
};

/// @brief Nested class that implements Circle from Interface class IPrimitive
class Circle : public IPrimitive {
public:
    Circle(std::string name, int x, int y, unsigned radius) : _name(name), _x(x), _y(y), _radius(radius) {}

    std::string getName() override { return _name; }
    
    std::tuple<std::string, int, int, unsigned> getParams() { return std::make_tuple(_name, _x, _y, _radius); }

    std::pair<int, int> getCoordinates() override { return std::make_pair(_x, _y);}

    void resizeRadius(unsigned radius) { _radius += radius;}


private:
    std::string _name;
    int _x;
    int _y;
    int _radius;
    
};


/// @brief Nested class that implements Square from Interface class IPrimitive
class Square : public IPrimitive {
public:
    Square(std::string name, int x, int y, unsigned width) : _name(name), _x(x), _y(y), _width(width) {}
    
    std::string getName() override { return _name; }

    std::tuple<std::string, int, int, unsigned> getParams() { return std::make_tuple(_name, _x, _y, _width); }

    std::pair<int, int> getCoordinates() override { return std::make_pair(_x, _y);}

    void resizeWidth(unsigned width) { _width += width;}

private:
    std::string _name;
    int _x;
    int _y;
    int _width;
    
};


/// @brief Nested class that implements Rectangle from Interface class IPrimitive
class Rectangle : public IPrimitive {
public:
    Rectangle(std::string name, int x, int y, unsigned width, unsigned height) : _name(name), _x(x), _y(y), _width(width), _height(height) {}
    
    std::string getName() override { return _name; }

    std::tuple<std::string, int, int, unsigned, unsigned> getParams() { return std::make_tuple(_name, _x, _y, _width, _height); }

    std::pair<int, int> getCoordinates() override { return std::make_pair(_x, _y);}

    void resizeWidth(unsigned width) { _width += width;}

    void resizeHeight(unsigned height) { _height += height;}

private:
    std::string _name;
    int _x;
    int _y;
    int _width;
    int _height;
    
};

#endif //H_PRIMITIVE