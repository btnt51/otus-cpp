/**
 * @file controller.h
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief File that contains declaration and defenetion of class controller for pattern MVC.
 * @version 0.1
 * @date 2022-12-12
 * @warning This work was done for educational purposes.
 * 
 */

#ifndef H_CONTROLLER
#define H_CONTROLLER

#include "model.h"


/// @brief Class that implements Controller
class Controller {
public:
    Controller() = default;

    ~Controller() = default;

    void createModel() {
        _model = std::make_unique<Model>();
        _model.get()->newView();
    }

    void close() {
        _model.get()->close();
    }
    void exportModel(std::string fileName) {
        _model.get()->save(fileName);
    }

    void importData(std::string fileName) {
        _model.get()->import(fileName);
    }

    template<typename T>
    void drawPrimitive(T *primitive) {
        
        _model.get()->draw(primitive);
    }

    void ereasePrimitive(std::pair<int, int> coord) {
        if(_model.get()->selectPrimitive(coord)) {
            _model.get()->erease();
        }
    }

    void ereasePrimitive(std::string name) {
        if(_model.get()->selectPrimitive(name)) {
            _model.get()->erease();
        }
    }


    void getPrimitiveInfo(std::pair<int ,int> coord) {
        if(_model.get()->selectPrimitive(coord)) {
            _model.get()->showInfo();
        }
    }


    void getPrimitiveInfo(std::string name) {
        if(_model.get()->selectPrimitive(name)) {
            _model.get()->showInfo();
        }
    }

private:
    std::unique_ptr<Model> _model;

};


#endif