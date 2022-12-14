/**
 * @file model.h
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief File that contains declaration and defenetion of class Model for pattern MVC
 * @version 0.1
 * @date 2022-12-12
 * @warning This work was done for educational purposes.
 * 
 * 
 */
#ifndef H_MODEL
#define H_MODEL

#include <vector>
#include <memory>

#include "view.h"
/// @brief Class that implements Model
class Model {
public:
    Model() = default;

    ~Model() = default;

    void newView() {
        if(!_isActive) {
            _view = std::make_unique<View>();
            _isActive = true;
        }
    }

    void save(std::string fileName) {
        if(_isActive) {
            std::cout << "Saving data to " << fileName << std::endl;
        }
    }

    void import(std::string fileName) {
        if(!_isActive) {
            _view = std::make_unique<View>();
            _isActive = true;
            std::cout << "Data was imported from " << fileName << std::endl;
        }
    }

    template<typename T>
    void draw(T *primitive) {
        if(_isActive) {
             _view.get()->drawPrimitive(primitive);
            _primitives.emplace_back(std::make_unique<T>(*primitive));
        }
    }

    void erease() {
        if(_isActive && _currentSelectedPrimitive != _primitives.end()) {
            _view.get()->ereasePrimitive((*_currentSelectedPrimitive).get());

        }
    }


    bool selectPrimitive(std::pair<int, int> coord) {
        if(_isActive) {
            for(auto it = _primitives.begin(); it != _primitives.end(); ++it) {
                if((*it)->getCoordinates() == coord) {
                    _currentSelectedPrimitive = it;
                    std::cout << "Prmitive was selected" << std::endl;
                    return true;
                }
            }
            return false;
        }
        return false;
    }


    bool selectPrimitive(std::string name) {
        if(_isActive) {
            for(auto it = _primitives.begin(); it != _primitives.end(); ++it) {
                if((*it)->getName() == name) {
                    _currentSelectedPrimitive = it;
                    std::cout << "Prmitive was selected" << std::endl;
                    return true;
                }
            }
            return false;
        }
        return false;
    }

    void showInfo() {
        if(_isActive  && _currentSelectedPrimitive != _primitives.end()) {
            _view.get()->showPrimitiveInfo((*_currentSelectedPrimitive).get());
        }
    }

    void close() {
        if(_isActive) {
            _isActive = false;
            _primitives.clear();
            _currentSelectedPrimitive = _primitives.end();
            std::cout << "Closed" << std::endl;
        }
    }

private:
    std::vector<std::unique_ptr<IPrimitive> > _primitives;
    std::unique_ptr<View> _view{nullptr};
    std::vector<std::unique_ptr<IPrimitive> >::iterator _currentSelectedPrimitive;

    bool _isActive = false;

};

#endif // H_MODEL