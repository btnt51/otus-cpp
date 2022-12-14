/**
 * @file view.h
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief File that contains declaration and defenetion of class View for MVC pattern
 * @version 0.1
 * @date 2022-12-12
 * @warning This work was done for educational purposes.
 * 
 */
#ifndef H_VIEW
#define H_VIEW

#include <iostream>
#include <typeindex>
#include <tuple>


#include "primitives.h"
/// @brief Class that implenets View
class View {
public:
    View() = default;

    ~View() = default;

    template<typename T>
    int workWithPrimitive(T *primitive) {
        auto type = std::type_index(typeid(*primitive));
        if(type == std::type_index(typeid(Circle))) {
            std::cout << "Circle ";
            return 0;
        } else if(type == std::type_index(typeid(Square))) {
            std::cout << "Square ";
            return 1;
        }else if(type == std::type_index(typeid(Rectangle))) {
            std::cout << "Reactangle ";
            return 2;
        } 
        std::cout << "Undefined primitive ";
        return -1;
    } 

    template<typename T>
    void drawPrimitive(T *primitive) {
        workWithPrimitive(primitive);
        auto x = primitive->getCoordinates();
        std::cout << "with name: " << primitive->getName() << "at x = " << x.first << " y = " << x.second;
        std::cout << " has been drawed" << std::endl;
    }

    template<typename T>
    void ereasePrimitive(T *primitive) {
        workWithPrimitive(primitive);
        auto x = primitive->getCoordinates();
        std::cout << "with name: " << primitive->getName() << "at x = " << std::get<0>(x) << " y = " << std::get<1>(x);
        std::cout << " has been ereased" << std::endl;
    }

    template<typename T>
    void showPrimitiveInfo(T *primitive) {
        auto type = workWithPrimitive(primitive);
        switch(type) {
            case 0:
            {
                auto circ = dynamic_cast<Circle *>(primitive);
                auto params = circ->getParams();
                std::cout << "name: " << std::get<0>(params) << " at x = " << std::get<1>(params) << " y = " << std::get<1>(params) 
                            << " radius = " << std::get<2>(params) << std::endl; 
            }
            break;
            case 1:
            {
                auto squ = dynamic_cast<Square *>(primitive);
                auto params = squ->getParams();
                std::cout << "name: " << std::get<0>(params) << " at x = " << std::get<1>(params) << " y = " << std::get<1>(params) 
                            << " width = " << std::get<2>(params) << std::endl; 
            }
            break;
            case 2:
            {
                auto rec = dynamic_cast<Rectangle *>(primitive);
                auto params = rec->getParams();
                std::cout << "name: " << std::get<0>(params) << " at x = " << std::get<1>(params) << " y = " << std::get<1>(params) 
                            << " width = " << std::get<2>(params) << " height = " << std::get<3>(params) << std::endl; 
            }
            break;
        }

    }
};

#endif //H_VIEW