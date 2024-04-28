#include "StructureWork.h"
#include "MenuWork.h"
#include <iostream>

int main() {
	standartSettings();
	//menu();

	appendMainElm("МатАн");
	appendMainElm("АнГем");
	appendMainElm("ЛинАл");

	appendAddElm("Зачет", "МатАн");
	appendAddElm("Экзамен", "МатАн");
	appendAddElm("Зачет", "АнГем");
	appendAddElm("Зачет", "ЛинАл");

	printStructure();
	return 0;
}
