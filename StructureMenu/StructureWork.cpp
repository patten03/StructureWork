#include "StructureWork.h"
#include "MenuWork.h"

MainElm* mainPtr = nullptr;

std::string exitStr = "0";

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

void removeMainElm(std::string remSubject) {
	MainElm* curMainElmPtr = mainPtr;
	MainElm* precMainElmPtr = nullptr;
	// ������� �� �����������, ����� ���������
	while (curMainElmPtr != nullptr and curMainElmPtr->subject != remSubject) {
		precMainElmPtr = curMainElmPtr;
		curMainElmPtr = curMainElmPtr->ptr1;
	}

	// ������, ����� ���������� �� �������
	if (curMainElmPtr->subject != remSubject)
		return;

	// �������� ���� ������� ����������
	AddElm* curAddElmPtr = curMainElmPtr->ptr2;
	AddElm* succAddElmPtr = nullptr;
	while (curAddElmPtr != nullptr) {
		succAddElmPtr = curAddElmPtr->ptr;
		delete curAddElmPtr;
		curAddElmPtr = succAddElmPtr;
	}
	curMainElmPtr->ptr2 = nullptr;

	// �������� ����������

	// ������, ����� ���������� ���� ����� ����� ��������� �� ���������
	if (mainPtr == curMainElmPtr) {
		MainElm* remPtr = curMainElmPtr;
		mainPtr = curMainElmPtr->ptr1;
		delete remPtr;

		return;
	}

	// ����� ������

	MainElm* remPtr = curMainElmPtr;
	precMainElmPtr->ptr1 = curMainElmPtr->ptr1;
	delete remPtr;
}

void appendAddElm(std::string appSession, std::string subjectName) {
	MainElm* curMainElmPtr = mainPtr;
	// ������� �� �����������, ����� ���������
	while (curMainElmPtr != nullptr and curMainElmPtr->subject != subjectName)
		curMainElmPtr = curMainElmPtr->ptr1;

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
	const int widthHead(20);
	const int widthCell(10);

	MainElm* curMainElmPtr;
	curMainElmPtr = mainPtr;

	std::cout << "��� ���������:" << std::endl;
	// ������� ��������� ��� ������
	while (curMainElmPtr != nullptr) {
		std::cout << std::left << std::setw(widthHead) << curMainElmPtr->subject;

		AddElm* curAddElmPtr = curMainElmPtr->ptr2;
		// ������� ������� ���������� ��� ������
		while (curAddElmPtr != nullptr) {
			std::cout << std::left << std::setw(widthCell) << curAddElmPtr->session;
			curAddElmPtr = curAddElmPtr->ptr;
		}

		// �������������� ����� ����� enter ��� ������ ���������� ��������
		if (curMainElmPtr->ptr1 != nullptr)
			std::cout << std::endl;

		curMainElmPtr = curMainElmPtr->ptr1;
	}
	// ������, ����� ��������� ������
	if (mainPtr == nullptr) {
		std::cout << "��������� �����";
	}
}

void menu() {
	std::cout << "����� ���������� � ��������� StructureWork." << std::endl
		<< "��������� �������� � �������� ������������ � �� �������� ����������." << std::endl << std::endl
		<< "��� ������ � ������� ��� ������ ��������� � ��� �� ����������, ��� � ���������." << std::endl << std::endl;


	bool isSaved(false); // ���������� ��������� �� ��, ���� �� ��������� ��������� � ����
	bool quit(false);    // ���������� ������ �� ���������
	while (!quit) {
		std::cout << "�������� ��������:" << std::endl;
		std::vector<std::string> menuPanel{
			"������� ����� ���������",
			"���������� ���������",
			"������������� ���������",
			"��������� ��������� � ����",
			"��������� ��������� �� �����",
			"������� ��������� � �������",
			"����� �� ���������"
		};
		ask(menuPanel); // ����� �������� � ������� ��� �� ������ �������������
		int choice = inputChoice(menuPanel.size());

		std::string file;
		// ������� �� ����� �������� �������������
		switch (choice) {
		case 1: // �������� ����� ���������
		{
			deleteStructure();
			continueWriting();
			break;
		}
		case 2: // �������� ���������
		{
			continueWriting();
			break;
		}
		case 3: // �������������� ���������
		{
			//editStructure();
			break;
		}
		case 4: // ���������� ��������� � ����
		{
			createFile();
			break;
		}
		case 5: // �������� ��������� �� �����
		{
			file = findFile("�������� ����:", receiveISS);
			if (file != "") {
				deleteStructure();
				loadFile(file);
			}
			break;
		}
		case 6: // ����� ��������� � �������
		{
			printStructure();
			std::cout << std::endl << std::endl;
			break;
		}
		case 7: // ����� �� ���������
		{
			quit = true;
			deleteStructure();
			break;
		}
		default:
			break;
		}
	}
}

void continueWriting() {
	std::string buffMain("");
	while (buffMain != exitStr) {
		std::cout << ("������� �������� ����������, ��� ������ ������� " + exitStr) << std::endl;
		std::cout << ">>";
		std::getline(std::cin, buffMain);

		system("cls");
		if (buffMain != exitStr) {
			appendMainElm(buffMain);
			insertAddElm(buffMain);
		}
	}
}

void insertAddElm(std::string subjectName) {
	std::vector<std::string> action{
	"�����",
	"�������",
	"��",
	"��",
	"����� � �����������"
	};

	std::vector<std::string> curList;

	bool exit(false);
	while (exit != true) {
		std::cout << ("�������� ������ ���������� ��� ���������� " + subjectName) << std::endl;
		ask(action);
		std::cout << "������ ��������� ������� ����������:" << std::endl;
		for (auto out : curList)
			std::cout << '\t' << out << std::endl;

		int ans = inputChoice(action.size());

		if (ans < 5) {
			appendAddElm(action[ans - 1], subjectName);
			curList.push_back(action[ans - 1]);
		}
		else if (ans == 5) {
			exit = true;
		}
	}
	system("cls");
}

void deleteStructure() {
	MainElm* curMainElmPtr = mainPtr;
	MainElm* precMainElmPtr = nullptr;

	while (curMainElmPtr != nullptr) {
		precMainElmPtr = curMainElmPtr;
		curMainElmPtr = curMainElmPtr->ptr1;
		removeMainElm(precMainElmPtr->subject);
	}
}

void createFile() {
	MainElm* curMainElmPtr;
	curMainElmPtr = mainPtr;

	// ������, ����� ��������� ������
	if (mainPtr == nullptr) {
		std::cout << "������ �������� � ���� ������ ���������" << std::endl;
		return;
	}

	std::string filename = askName("������� �������� �����, ��� ������ ������� " + exitStr);
	// �������� �� ������ ������ � ��, �������� �� ��������� ������
	if (filename != exitStr) {
		filename = filename + "_" + currentTime() + ".iss";

		std::fstream outstream;
		outstream.open(filename, std::ios_base::out);

		// ������� ��������� ��� ������
		while (curMainElmPtr != nullptr) {
			outstream << curMainElmPtr->subject;

			AddElm* curAddElmPtr = curMainElmPtr->ptr2;
			// ������� ������� ���������� ��� ������
			while (curAddElmPtr != nullptr) {
				outstream << '\t' << curAddElmPtr->session;
				curAddElmPtr = curAddElmPtr->ptr;
			}

			// �������������� ����� ����� enter ��� ������ ���������� ��������
			if (curMainElmPtr->ptr1 != nullptr)
				outstream << std::endl;

			curMainElmPtr = curMainElmPtr->ptr1;
		}

		std::cout << "��������� ��������� � ���� ��� ��������� " << filename << std::endl;

		outstream.close();
	}
}

void loadFile(std::string filename) {
	std::fstream instream;
	instream.open(filename, std::ios_base::in);

	// �������� �� �������� �����
	if (!instream.is_open()) {
		std::cout << "��������� ������ ��� �������� �����" << std::endl;
		return;
	}

	std::string line;
	while (!instream.eof()) {
		std::getline(instream, line);
		std::string subject;
		std::string session;

		std::stringstream ss(line);
		std::getline(ss, subject, '\t');

		appendMainElm(subject);
		while (getline(ss, session, '\t'))
			appendAddElm(session, subject);
	}

	instream.close();
}