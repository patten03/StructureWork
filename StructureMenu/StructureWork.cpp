#include "StructureWork.h"
#include "MenuWork.h"

MainElm* mainPtr = nullptr;

const std::vector<std::string> sessionKind{
	"�����",
	"�������",
	"��",
	"��",
};

const std::string exitStr = "0";

bool receiveISS(const std::string& filename) {
	return (filename.rfind(".iss") != std::string::npos);
}

MainElm* appendMainElm(std::string appSubject) {
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
	return appPtr;
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

void appendAddElm(std::string appSession, MainElm* subjectPtr) {
	if (subjectPtr != nullptr) {

		// �������� �������� ������ ����������
		AddElm* tmp = new AddElm;
		tmp->ptr = nullptr;
		tmp->session = appSession;

		// �������� �� ������� ���� �����-�� ������� ���������� � ���������
		if (subjectPtr->ptr2 == nullptr) // ������ ���������� ������� ����������
			subjectPtr->ptr2 = tmp;
		else {                              // ������ ������� ������� ����������
			AddElm* curAddElmPtr = subjectPtr->ptr2;
			// ������� ������� ����������
			while (curAddElmPtr->ptr != nullptr)
				curAddElmPtr = curAddElmPtr->ptr;
			curAddElmPtr->ptr = tmp;
		}
	}
	else {} // TODO ��������� �����-������ �������������� ��� ������, ����� ���������� �� ���� �������
}

void removeAddElm(std::string remSession, MainElm* subjectPtr) {
	// �������� �� ��������� ������� ����������
	if (subjectPtr->ptr2 == nullptr)
		return;

	AddElm* curAddElmPtr = subjectPtr->ptr2;
	// ������, ����� ����� ���������� � ���������� ������������
	if (curAddElmPtr->ptr == nullptr) {
		// ����� ���������� ���������
		if (curAddElmPtr->session == remSession) {
			delete curAddElmPtr;
			subjectPtr->ptr2 = nullptr;
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
			subjectPtr->ptr2 = curAddElmPtr->ptr;  // �������� � ���������� � ������ ���������� ����� ��������� ������� ����������
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
	// ����� ����������
	std::cout << "����� ���������� � ��������� StructureWork." << std::endl
		<< "��������� �������� � �������� ������������ � �� �������� ����������." << std::endl << std::endl
		<< "��� ������ � ������� ��� ������ ��������� � ��� �� ����������, ��� � ���������." << std::endl << std::endl;


	bool isSaved(false); // ���������� ��������� �� ��, ���� �� ��������� ��������� � ����
	bool quit(false);    // ���������� ������ �� ���������
	while (!quit) {

		if (mainPtr != nullptr) {
			if (isSaved)
				std::cout << "������� ��������� ���������" << std::endl;
			else
				std::cout << "������� ��������� �� ���������" << std::endl;
		}

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
			isSaved = false;
			break;
		}
		case 2: // �������� ���������
		{
			isSaved = !continueWriting();
			break;
		}
		case 3: // �������������� ���������
		{
			if (mainPtr != nullptr)
				isSaved = !editStructure();
			else
				std::cout << "���������� ������������� ������ ���������" << std::endl;
			break;
		}
		case 4: // ���������� ��������� � ����
		{
			isSaved = createFile();
			break;
		}
		case 5: // �������� ��������� �� �����
		{
			file = findFile("�������� ����:", receiveISS);
			if (file != "") {
				deleteStructure();
				loadFile(file);
				isSaved = true;
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

//@return ���� ���� ������� ������� �� true, ����� false
bool continueWriting() {
	std::string buffMain("");
	bool wasChanged(false); // ����, ���������� ���� ����, ���� �� ������� �����-���� ��������� � ���������
	while (buffMain != exitStr) {
		std::cout << ("������� �������� ����������, ��� ������ ������� " + exitStr) << std::endl;
		std::cout << ">>";
		std::getline(std::cin, buffMain);

		system("cls");
		if (buffMain != exitStr) {
			wasChanged = true;
			MainElm* curMainElm = appendMainElm(buffMain);
			insertAddElm(curMainElm);
		}
	}
	return wasChanged;
}

//@return ���������� true, ���� ��������� ���� ��������, ����� false
bool insertAddElm(MainElm* subjectPtr) {
	bool res(false);

	std::vector<std::string> action = sessionKind;
	action.push_back("����� �� ������");

	std::vector<std::string> curList;

	bool exit(false);
	while (exit != true) {
		std::cout << ("�������� ������ ���������� ��� ���������� " + subjectPtr->subject) << std::endl;
		ask(action);
		std::cout << "������ ��������� ������� ����������:" << std::endl;
		for (auto out : curList)
			std::cout << "  " << out << std::endl;

		int ans = inputChoice(action.size());

		if (ans < 5) {
			res = true;
			appendAddElm(action[ans - 1], subjectPtr);
			curList.push_back(action[ans - 1]);
		}
		else if (ans == 5) {
			exit = true;
		}
	}
	system("cls");
	return res;
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

//@return ���������� true, ���� ���� ��� ������, ����� false
bool createFile() {
	MainElm* curMainElmPtr;
	curMainElmPtr = mainPtr;

	// ������, ����� ��������� ������
	if (mainPtr == nullptr) {
		std::cout << "������ �������� � ���� ������ ���������" << std::endl;
		return false; // ���� �� ��� ��������, �� ������
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
		return true; // ���� ��� ��������
	}
	return false; // ���� �� ��� ��������, �� ������� ������������
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

		MainElm* curMainElmPtr = appendMainElm(subject);
		while (getline(ss, session, '\t'))
			appendAddElm(session, curMainElmPtr);
	}

	instream.close();
}

//@return ���������� true, ���� ��������� ���� ��������, ����� false
bool editStructure() {
	bool res(false);

	if (mainPtr != nullptr) {
		std::vector<std::string> action{
	"�������� ����� ����������",
	"������� ����������",
	"������� ����� ����������",
	"����� � ������� ����"
		};

		bool quit(false);

		while (!quit) {
			printStructure();
			std::cout << std::endl;
			std::cout << "�������� ��������:" << std::endl;
			ask(action);
			int ans = inputChoice(action.size());

			printStructure();
			std::cout << std::endl;
			switch (ans) {
			case 1: // ���������� ������ ����������
			{
				res = edit_appendSession();
				break;
			}
			case 2: // �������� ����������
			{
				res = edit_removeSubject();
				break;
			}
			case 3: // �������� ������ ����������
			{
				res = edit_removeSession();
				break;
			}
			case 4: // ����� � ����
			{
				quit = true;
				system("cls");
				break;
			}
			default:
				break;
			}
		}
	}
	return res;
}

//@return ���������� true, ���� ��������� ���� ��������, ����� false
bool edit_appendSession() {
	bool res(false);

	std::cout << ("������� �������� ����������, � ������� ������ �������� ������ ����������, ��� ������ ������� " + exitStr) << std::endl;
	std::string buff("");

	while (buff != exitStr) {
		std::cout << ">>";
		std::getline(std::cin, buff);

		MainElm* curMainElmPtr = subjectFound(buff);
		if (curMainElmPtr != nullptr and buff != exitStr) {
			system("cls");
			res += insertAddElm(curMainElmPtr);
			buff = exitStr;
		}
		else if (buff == exitStr)
			system("cls");
		else
			std::cout << "���������� �� �������" << std::endl;
	}
	return res;
}

//@return ���������� true, ���� ��������� ���� ��������, ����� false
bool edit_removeSubject() {
	bool res(false);

	std::cout << ("������� �������� ����������, ������� ������ �������, ��� ������ ������� " + exitStr) << std::endl;
	std::string buff("");

	while (buff != exitStr) {
		std::cout << ">>";
		std::getline(std::cin, buff);

		if (subjectFound(buff) and buff != exitStr) {
			res = true;
			removeMainElm(buff);
			system("cls");
			buff = exitStr;
		}
		else if (buff == exitStr)
			system("cls");
		else
			std::cout << "���������� �� �������" << std::endl;
	}
	return res;
}

//@return ���������� true, ���� ��������� ���� ��������, ����� false
bool edit_removeSession() {
	bool res(false);

	std::cout << ("������� �������� ����������, �� ������� ������ ������� ����� ����������, ��� ������ ������� " + exitStr) << std::endl;
	std::string buffMainElm("");

	while (buffMainElm != exitStr) {
		std::cout << ">>";
		std::getline(std::cin, buffMainElm);

		MainElm* curMainElmPtr = subjectFound(buffMainElm);
		if (curMainElmPtr != nullptr and buffMainElm != exitStr) {
			std::vector<std::string> action = sessionKind;
			action.push_back("����� �� ������");

			bool exit(false);
			while (exit != true) {
				system("cls");
				printStructure();
				std::cout << std::endl;
				std::cout << ("�������� ����� ����������, ������� ������ ������� � ���������� " + buffMainElm) << std::endl;
				ask(action);

				int ans = inputChoice(action.size());

				if (ans < 5) {
					res = true;
					removeAddElm(action[ans - 1], curMainElmPtr);
				}
				else if (ans == 5) {
					buffMainElm = exitStr;
					exit = true;
				}
			}
			system("cls");
		}
		else if (buffMainElm == exitStr)
			system("cls");
		else
			std::cout << "���������� �� �������" << std::endl;
	}
	return res;
}

MainElm* subjectFound(std::string name) {
	MainElm* curMainElmPtr = mainPtr;
	while (curMainElmPtr->subject != name and curMainElmPtr->ptr1 != nullptr)
		curMainElmPtr = curMainElmPtr->ptr1;
	if (curMainElmPtr->subject == name)
		return curMainElmPtr;
	else
		return nullptr;
}