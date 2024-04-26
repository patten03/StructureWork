#ifndef STRUCTUREWORK
#define STRUCTUREWORK

#include "MenuWork.h"

struct AddElm {
	std::string session;
	AddElm* ptr;
};

struct MainElm {
	std::string book;
	MainElm* ptr1; // ptrDown
	AddElm* ptr2;  // ptrLeft
};

MainElm* main_ptr = nullptr;

void menu();
bool receiveISS(const std::string& filename);

#endif // STRUCTUREWORK