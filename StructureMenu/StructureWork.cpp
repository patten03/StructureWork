#include "StructureWork.h"
#include "MenuWork.h"

MainElm* mainPtr = nullptr;

bool receiveISS(const std::string& filename) {
	return (filename.rfind(".iss") != std::string::npos);
}

void appendMainElm(std::string appSubject) {
	MainElm* appPtr = new MainElm;
	appPtr->subject = appSubject;
	appPtr->ptr1 = nullptr;
	appPtr->ptr2 = nullptr;

	MainElm* curPtr = mainPtr;

	// случай, когда в структуре нет ни одного элемента
	if (mainPtr == nullptr) {
		mainPtr = appPtr;
		appPtr->ptr1 = nullptr;
	}

	else {
		while (curPtr->ptr1 != nullptr) {
			curPtr = curPtr->ptr1; // перебор элементов
		}
		curPtr->ptr1 = appPtr;
	}
}

void printStructure() {
	MainElm* curMainElmPtr;
	curMainElmPtr = mainPtr;
	while (curMainElmPtr != nullptr) {
		std::cout << curMainElmPtr->subject;

		AddElm* curAddElmPtr = curMainElmPtr->ptr2;
		while (curAddElmPtr != nullptr) {
			std::cout << '\t' << curAddElmPtr->session;
			curAddElmPtr = curAddElmPtr->ptr;
		}

		// предотвращение ввода ввода enter при выводе последнего элемента
		if (curMainElmPtr->ptr1 != nullptr)
			std::cout << std::endl;

		curMainElmPtr = curMainElmPtr->ptr1;
	}
}

void menu() {
	std::cout << "Добро пожаловать в программу StructureWork." << std::endl
		<< "Программа работает с учебными дисциплинами и их методами оценивания." << std::endl << std::endl
		<< "Для работы с файлами они должны находится в той же директории, что и программа." << std::endl << std::endl;

	bool quit(false); // переменная выхода из программы
	while (!quit) {
		std::cout << "Выберите действие:" << std::endl;
		std::vector<std::string> menuPanel{
			"Создать файл",
			"Редактировать файл",
			"Выйти из программы"
		};
		ask(menuPanel); // вывод действий в консоль для их выбора пользователем
		int choice = inputChoice(menuPanel.size());

		std::string file;
		// реакция на выбор действия пользователем
		switch (choice) {
		case 1:
		{ // создание файла

			break;
		}
		case 2:
		{ // редактирование файла
			file = findFile("Выберите файл:", receiveISS);
			if (file != "") {
				continue;
			}
			break;
		}
		case 3:
		{
			quit = true;
			break;
		}
		default:
			break;
		}
	}
}
