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

	// ������, ����� � ��������� ��� �� ������ ��������
	if (mainPtr == nullptr) {
		mainPtr = appPtr;
		appPtr->ptr1 = nullptr;
	}

	else {
		while (curPtr->ptr1 != nullptr) {
			curPtr = curPtr->ptr1; // ������� ���������
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

		// �������������� ����� ����� enter ��� ������ ���������� ��������
		if (curMainElmPtr->ptr1 != nullptr)
			std::cout << std::endl;

		curMainElmPtr = curMainElmPtr->ptr1;
	}
}

void menu() {
	std::cout << "����� ���������� � ��������� StructureWork." << std::endl
		<< "��������� �������� � �������� ������������ � �� �������� ����������." << std::endl << std::endl
		<< "��� ������ � ������� ��� ������ ��������� � ��� �� ����������, ��� � ���������." << std::endl << std::endl;

	bool quit(false); // ���������� ������ �� ���������
	while (!quit) {
		std::cout << "�������� ��������:" << std::endl;
		std::vector<std::string> menuPanel{
			"������� ����",
			"������������� ����",
			"����� �� ���������"
		};
		ask(menuPanel); // ����� �������� � ������� ��� �� ������ �������������
		int choice = inputChoice(menuPanel.size());

		std::string file;
		// ������� �� ����� �������� �������������
		switch (choice) {
		case 1:
		{ // �������� �����

			break;
		}
		case 2:
		{ // �������������� �����
			file = findFile("�������� ����:", receiveISS);
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
