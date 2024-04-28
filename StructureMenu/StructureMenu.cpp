#include "StructureWork.h"
#include "MenuWork.h"
#include <iostream>

int main() {
	standartSettings();
	//menu();

	appendMainElm("Math");
	appendMainElm("AnGeom");
	appendMainElm("ConEng");
	appendMainElm("LineAlg");


	appendAddElm("1", "AnGeom");
	appendAddElm("1", "ConEng"); appendAddElm("2", "ConEng");
	appendAddElm("1", "LineAlg"); appendAddElm("2", "LineAlg"); appendAddElm("3", "LineAlg");


	printStructure(); std::cout << std::endl;

	//removeAddElm("1", "Math");
	//removeAddElm("1", "AnGeom");
	//removeAddElm("1", "ConEng");
	//removeAddElm("1", "LineAlg");

	removeAddElm("0", "Math");
	removeAddElm("1", "AnGeom");
	removeAddElm("2", "ConEng");
	removeAddElm("3", "LineAlg");

	printStructure();

	return 0;
}
