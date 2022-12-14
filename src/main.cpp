#include "../include/editor.h"

int main(int, char **) {
	try {
		Editor ed;
		ed.open();
		ed.onCicrleButtonAddClick("Circ 1", std::make_pair(1,2), 5);

		ed.onRectangleButtonAddClick("Rec 1", std::make_pair(3,5),2,5);

		ed.onEreaseButtonClick("Rec 1");

		ed.onPrimitiveInWorkspaceClick(std::make_pair(1, 2)); 
		
	} 
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}
