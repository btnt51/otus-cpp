/**
 * @file editor.h
 * @author Evgeniy btnt51 (prog@btnt51.ru)
 * @brief File that implements editor pseudo UI.
 * @version 0.1
 * @date 2022-12-12
 * @warning This work was done for educational purposes.
 * 
 */
#ifndef H_EDITOR
#define H_EDITOR

#include "controller.h"
/// @brief Class that implements Editor
class Editor {
public:
    Editor() = default;

    ~Editor() = default;

    void onImportButtonClick(std::string fileName) {
        _controller.get()->importData(fileName);
    }

    void onExportButtonClick(std::string fileName) {
        _controller.get()->exportModel(fileName);
    }

    void open() {
        
        _controller = std::make_unique<Controller>();
        _controller.get()->createModel();
    }

    void onCicrleButtonAddClick(std::string name, std::pair<int, int> cord, int radius) {
        _controller.get()->drawPrimitive(new Circle(name, cord.first, cord.second, radius));
    }

    void onSquareButtonAddClick(std::string name, std::pair<int, int> coord, int width) {
        _controller.get()->drawPrimitive(new Square(name, coord.first, coord.second, width));
    }

    void onRectangleButtonAddClick(std::string name, std::pair<int, int> coord, int width, int height) {
        _controller.get()->drawPrimitive(new Rectangle(name, coord.first, coord.second, width, height));
    }

    void onEreaseButtonClick(std::pair<int, int> coord) {
        _controller.get()->ereasePrimitive(coord);
    }

    void onEreaseButtonClick(std::string name) {
        _controller.get()->ereasePrimitive(name);
    }

    void onPrimitiveInWorkspaceClick(std::pair<int, int> coord) {
        _controller.get()->getPrimitiveInfo(coord);
    }

    void onPrimitiveInPrimitiveTableClick(std::string name) {
        _controller.get()->getPrimitiveInfo(name);
    }

private:
    std::unique_ptr<Controller> _controller{nullptr};

};

#endif //H_EDITOR