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

void appendAddElm(std::string appSession, std::string subjectName) {
	MainElm* curMainElmPtr = mainPtr;
	// ������� �� �����������, ����� ���������
	while (curMainElmPtr != nullptr and curMainElmPtr->subject != subjectName) {
		curMainElmPtr = curMainElmPtr->ptr1;
	}

	if (curMainElmPtr != nullptr) {

		// �������� �������� ������ ����������
		AddElm* tmp = new AddElm;
		tmp->ptr = nullptr;
		tmp->session = appSession;

		// �������� �� ������� ���� �����-�� ������� ���������� � ���������
		if (curMainElmPtr->ptr2 == nullptr) // ������ ���������� ������� ����������
			curMainElmPtr->ptr2 = tmp;
		else {                              // ������ ������� ������� ����������
			AddElm* curAddElmPtr = curMainElmPtr->ptr2;
			// ������� ������� ����������
			while (curAddElmPtr->ptr != nullptr)
				curAddElmPtr = curAddElmPtr->ptr;
			curAddElmPtr->ptr = tmp;
		}
	}
	else {} // TODO ��������� �����-������ �������������� ��� ������, ����� ���������� �� ���� �������
}

void removeAddElm(std::string remSession, std::string subjectName) {
	MainElm* curMainElmPtr = mainPtr;
	// ����� ��������� ����������
	while (curMainElmPtr->subject != subjectName and curMainElmPtr->ptr1 != nullptr)
		curMainElmPtr = curMainElmPtr->ptr1;
	// ���� �� ���� ������� ��������� ����������
	if (curMainElmPtr->subject != subjectName)
		return;

	// �������� �� ��������� ������� ����������
	if (curMainElmPtr->ptr2 == nullptr)
		return;

	AddElm* curAddElmPtr = curMainElmPtr->ptr2;
	// ������, ����� ����� ���������� � ���������� ������������
	if (curAddElmPtr->ptr == nullptr) {
		// ����� ���������� ���������
		if (curAddElmPtr->session == remSession) {
			delete curAddElmPtr;
			curMainElmPtr->ptr2 = nullptr;
		}
		return;
	}

	AddElm* precAddElmPtr = nullptr; // ���������� �������
	// ������� ���������
	while (curAddElmPtr->session != remSession and curAddElmPtr->ptr != nullptr) {
		precAddElmPtr = curAddElmPtr;
		curAddElmPtr = curAddElmPtr->ptr;
	}

	if (curAddElmPtr->session == remSession) {
		AddElm* remPtr = curAddElmPtr;           // ���������� ��������� �� ��������� �������

		// ������, ����� ��� ������ ������ ����� ���������� � � ������ �� �� ����
		if (precAddElmPtr == nullptr)
			curMainElmPtr->ptr2 = curAddElmPtr->ptr;  // �������� � ���������� � ������ ���������� ����� ��������� ������� ����������
		else
			precAddElmPtr->ptr = curAddElmPtr->ptr;  // �������� � ��������� ����� ����������
		delete remPtr;                               // �������� ���������� ��������
	}
}
void printStructure() {
	MainElm* curMainElmPtr;
	curMainElmPtr = mainPtr;
	// ������� ��������� ��� ������
	while (curMainElmPtr != nullptr) {
		std::cout << curMainElmPtr->subject;

		AddElm* curAddElmPtr = curMainElmPtr->ptr2;
		// ������� ������� ���������� ��� ������
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
