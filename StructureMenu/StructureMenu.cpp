#include "StructureWork.h"
#include "MenuWork.h"
#include <iostream>

int main() {
	standartSettings();
	//menu();

	appendMainElm("МатАн");
	appendMainElm("АнГем");
	appendMainElm("ЛинАл");

	printStructure();
	return 0;
}
