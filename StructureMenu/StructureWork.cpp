#include "StructureWork.h"
#include "MenuWork.h"

//@brief ��������� ��������� �� ��� ���������
MainElm* mainPtr = nullptr;

//@brief ������ ������� ����������
const std::vector<std::string> sessionKind{
	"�����",
	"�������",
	"��",
	"��",
};

//@brief ������ ������ �� ���� �����
const std::string exitStr = "0";

//@brief ������ ��� ������ ������ ������� .iss
//@return ���������� true ���� ������ .iss, ����� false
//@param filename - �������� �����, �� �������� ���������� ����������
bool receiveISS(const std::string& filename) {
	int dotPos = filename.rfind(".iss");
	if (dotPos != std::string::npos) {
		std::string extension = filename.substr(dotPos, filename.size() - 1);
		return (extension == ".iss");
	}
	else
		return false; // ���� � �������� ����� � ����������� ����� ���
}

//@brief ���������� ���������� � ���������
//@return ���������� ��������� �� ����������, ������� ���� �������
//@param appSubject - �������� ������������ ����������
MainElm* appendMainElm(std::string appSubject) {
	// ������������� ����� ����������
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
	// ����� ������
	else {
		while (curPtr->ptr1 != nullptr) {
			curPtr = curPtr->ptr1; // ������� ���������
		}
		curPtr->ptr1 = appPtr;
	}
	return appPtr;
}

//@brief �������� ���������� �� ���������
//@param remSubject - �������� �������� ����������
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

//@brief ���������� ������ ���������� � ���������
//@param appSession - �������� ������������ ������ ����������
//@param subjectPtr - ��������� �� ����������, � ������� ����������� ����� ����������
void appendAddElm(std::string appSession, MainElm* subjectPtr) {
	// �������� �� ������������� �������
	if (subjectPtr != nullptr) {

		// �������� �������� ������ ����������
		AddElm* tmp = new AddElm;
		tmp->ptr = nullptr;
		tmp->session = appSession;

		// �������� �� ������� ���� �����-�� ������� ���������� � ���������
		if (subjectPtr->ptr2 == nullptr)    // ������ ���������� ������� ����������
			subjectPtr->ptr2 = tmp;
		else {                              // ������ ������� ������� ����������
			AddElm* curAddElmPtr = subjectPtr->ptr2;
			// ������� ������� ����������
			while (curAddElmPtr->ptr != nullptr)
				curAddElmPtr = curAddElmPtr->ptr;
			curAddElmPtr->ptr = tmp;
		}
	}
}

//@brief �������� ������ ���������� �� ���������
//@param remSession - �������� ���������� ������ ����������
//@param subjectPtr - ��������� �� ����������, �� ������� ��������� ����� ����������
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

//@brief ����� ��������� � �������
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
		std::cout << std::endl;

		curMainElmPtr = curMainElmPtr->ptr1;
	}
	// ������, ����� ��������� ������
	if (mainPtr == nullptr) {
		std::cout << "��������� �����";
	}
}

//@brief �������� ������� ����
void menu() {
	// ����� ����������
	std::cout << "����� ���������� � ��������� StructureWork." << std::endl
		<< "��������� �������� � �������� ������������ � �� �������� ����������." << std::endl << std::endl
		<< "��� ������ � ������� ��� ������ ��������� � ��� �� ����������, ��� � ���������." << std::endl << std::endl;


	bool isSaved(false); // ���������� ��������� �� ��, ���� �� ��������� ��������� � ����
	bool quit(false);    // ���������� ������ �� ���������
	while (!quit) {

		// ����� ����, ���� �� ��������� ���������
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
			"����������� ���������",
			"������� ���������� �� ������� ����������",
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
			isSaved += createFile();
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
			std::cout << std::endl;
			break;
		}
		case 7: // ���������� ���������
		{
			isSaved = !menuSorting();
			break;
		}
		case 8: // ����� ��������� � ������������ ������� ����������
		{
			specialOutput();
			break;
		}
		case 9: // ����� �� ���������
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

//@brief ���� ������ ��� �������� ���������
//@return ���� ���� ������� ������� �� true, ����� false
bool continueWriting() {
	std::string buffMain("");
	bool wasChanged(false); // ����, ���������� ���� ����, ���� �� ������� �����-���� ��������� � ���������

	// ���� �������� �� ��� ���, ���� ������������ �� ������ ������ ������
	while (buffMain != exitStr) {
		try {
			std::cout << ("������� �������� ����������, ��� ������ ������� " + exitStr) << std::endl;
			std::cout << ">>";
			std::getline(std::cin, buffMain);

			system("cls");
			if (buffMain != exitStr) {
				isAdequate(buffMain);
				wasChanged = true;
				MainElm* curMainElm = appendMainElm(buffMain);
				insertAddElm(curMainElm);
			}
		}
		catch (const std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}

	}
	return wasChanged;
}

//@brief ������ ���������� ������� ���������� ��� ��������
//@return ���������� true, ���� ��������� ���� ��������, ����� false
//@param subjectPtr - ��������� �� ����������, � ������� ����������� ������ ����������
bool insertAddElm(MainElm* subjectPtr) {
	bool res(false);

	std::vector<std::string> action = sessionKind;
	action.push_back("����� �� ������");

	std::vector<std::string> curList; // ������ ��������� ������� ����������

	bool exit(false);
	// ���� �������� �� ��� ���, ���� �� ������������ �� ������� �����
	while (exit != true) {
		std::cout << ("�������� ������ ���������� ��� ���������� " + subjectPtr->subject) << std::endl;
		ask(action);
		std::cout << "������ ��������� ������� ����������:" << std::endl;
		// ����� ��������� ������� ����������
		for (auto out : curList)
			std::cout << "  " << out << std::endl;

		int ans = inputChoice(action.size());

		// ���� ���������� ������ ����������
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

//@brief ������ �������� ���������
void deleteStructure() {
	MainElm* curMainElmPtr = mainPtr;
	MainElm* precMainElmPtr = nullptr;

	while (curMainElmPtr != nullptr) {
		precMainElmPtr = curMainElmPtr;         // ���������� ����������� ��������, ����� �� ������ ���������
		curMainElmPtr = curMainElmPtr->ptr1;
		removeMainElm(precMainElmPtr->subject); // �������� ����������� ��������
	}
}

//@brief ���������� ���������
//@param compare - ������� ��������� ���������
void sortStructure(bool compare(const MainElm*, const MainElm*)) {
	std::vector<MainElm*> vecPtr;

	MainElm* curMainElmPtr(mainPtr);
	// ��������� ���������� �� ��� ����������
	while (curMainElmPtr != nullptr) {
		vecPtr.push_back(curMainElmPtr);
		curMainElmPtr = curMainElmPtr->ptr1;
	}

	// ���������� ����������
	std::sort(vecPtr.begin(), vecPtr.end(), compare);

	// ����������� ������������� ����������
	mainPtr = vecPtr.at(0);
	for (int i = 0; i < (vecPtr.size() - 1); i++) {
		vecPtr.at(i)->ptr1 = vecPtr.at(i + 1);
	}
	vecPtr.at(vecPtr.size() - 1)->ptr1 = nullptr;
}

//@brief ������� ��������� ��� �������� ���������
//@return ������������ ����� >
//@param a � b - ��������� �� ��������
bool greater(const MainElm* a, const MainElm* b) {
	bool res;
	res = std::lexicographical_compare(
		a->subject.begin(), a->subject.end(),
		b->subject.begin(), b->subject.end());
	return res;
}

//@brief ������� ��������� ��� �������� ���������
//@return ������������ ����� <
//@param a � b - ��������� �� ��������
bool lesser(const MainElm* a, const MainElm* b) {
	bool res;
	if (a->subject == b->subject)
		res = false;
	else
		res = not(std::lexicographical_compare(
			a->subject.begin(), a->subject.end(),
			b->subject.begin(), b->subject.end()));
	return res;
}

//@brief ���������� ������ ���������� � ��������� �� ��� ��������
//@return ���������� ��������� �� ����� ����������, ���� �� ������, �� nullptr
//@param subject - ��������� �� ����������, � ������� ������ ����� ����������
//@param session - �������� ����� ����������, ������� ��������� �����
AddElm* sessionFound(MainElm* subject, std::string session) {
	// ������, ����� ���������� �� �������� ������ ����������
	if (subject->ptr2 == nullptr)
		return nullptr;

	// ����� ������
	AddElm* curAddElmPtr = subject->ptr2;
	while (curAddElmPtr->session != session and curAddElmPtr->ptr != nullptr)
		curAddElmPtr = curAddElmPtr->ptr;
	if (curAddElmPtr->session == session)
		return curAddElmPtr;
	else
		return nullptr;
}

//@brief ���������� ��������� � ����
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

		// ������� ��������� ��� �����
		while (curMainElmPtr != nullptr) {
			outstream << curMainElmPtr->subject;

			AddElm* curAddElmPtr = curMainElmPtr->ptr2;
			// ������� ������� ���������� ��� �����
			while (curAddElmPtr != nullptr) {
				outstream << '\t' << curAddElmPtr->session;
				curAddElmPtr = curAddElmPtr->ptr;
			}

			// �������������� ����� enter ��� ������ ���������� ��������
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

//@brief �������� ��������� �� �����
//@param filename - �������� �����, �� �������� ��������� ��������� ���������
void loadFile(std::string filename) {
	std::fstream instream;
	instream.open(filename, std::ios_base::in);

	// �������� �� �������� �����
	if (!instream.is_open()) {
		std::cout << "��������� ������ ��� �������� �����" << std::endl;
		return;
	}

	std::string line;
	// ���� ��������� ��������� � �� �������� ����������
	while (!instream.eof()) {
		std::getline(instream, line);
		std::string subject;
		std::string session;

		std::stringstream ss(line);
		std::getline(ss, subject, '\t');

		MainElm* curMainElmPtr = appendMainElm(subject);
		// ���������� ���������� ������ �� ������ ����������
		while (getline(ss, session, '\t'))
			appendAddElm(session, curMainElmPtr);
	}

	instream.close();
}

//@brief ���� �������������� ���������
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
			std::cout << "�������� ��������:" << std::endl;
			ask(action);
			int ans = inputChoice(action.size());

			printStructure();
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

//@brief ���� ���������� ��������� �� �����������
//@return ���������� true, ���� ��������� ���� ��������, ����� false
bool menuSorting() {

	// ����� ��-�� ���������� ��������� � ���������
	if (mainPtr == nullptr) {
		std::cout << "���������� ����������� ������ ���������" << std::endl;
		return false;
	}

	bool isChanged;
	std::vector<std::string> action{
		"����������� �� �����������",
		"����������� �� ��������",
		"����� � ����"
	};
	ask(action);
	int choice = inputChoice(action.size());

	switch (choice) {
	case 1: // ���������� �� �����������
	{
		sortStructure(greater);
		isChanged = true;
		break;
	}
	case 2: // ���������� �� ��������
	{
		sortStructure(lesser);
		isChanged = true;
		break;
	}
	case 3: // ����� �� ����
	{
		isChanged = false;
		break;
	}
	default:
		break;
	}
	return isChanged;
}

//@brief ����� ���������, ������� �������� ������������ ������ ����������
void specialOutput() {
	const int widthHead(20);
	const int widthCell(10);

	std::vector<std::string> action = sessionKind;
	std::cout << "�������� ����� ����������, ������� ������ ����������� ��������� �����������:" << std::endl;
	ask(action);
	int choice = inputChoice(action.size());

	if (mainPtr != nullptr)
		std::cout << "����������, ���������� � ���� ����� ���������� " + action.at(choice - 1) << ":" << std::endl;

	bool isEmpty(true); // ����������, ������� ���������� ������� ��������� ���������

	MainElm* curMainElmPtr = mainPtr;
	while (curMainElmPtr != nullptr) {
		// �������, �� �������� ��������� ������ ���������� � ��������� ������� ����������
		if (sessionFound(curMainElmPtr, action.at(choice - 1)) != nullptr) {
			std::cout << std::left << std::setw(widthHead) << curMainElmPtr->subject;

			AddElm* curAddElmPtr = curMainElmPtr->ptr2;
			// ������� ������� ���������� ��� ������
			while (curAddElmPtr != nullptr) {
				std::cout << std::left << std::setw(widthCell) << curAddElmPtr->session;
				curAddElmPtr = curAddElmPtr->ptr;
			}
			std::cout << std::endl;

			isEmpty = false;
		}
		curMainElmPtr = curMainElmPtr->ptr1;
	}

	// ������, ����� ��������� ������
	if (mainPtr == nullptr) {
		std::cout << "��������� �����" << std::endl;
		return;
	}

	// ������, ����� �� ���� ������� ��������� � ��������� ������� ����������
	if (isEmpty) {
		std::cout << "���������� �� �������" << std::endl << std::endl;
		return;
	}

	std::cout << std::endl;
}

//@brief ���� ���������� ������ ���������� � ����������
//@return ���������� true, ���� ��������� ���� ��������, ����� false
bool edit_appendSession() {
	bool res(false);

	std::cout << ("������� �������� ����������, � ������� ������ �������� ������ ����������, ��� ������ ������� " + exitStr) << std::endl;
	std::string buff("");

	// ���� �������� �� ����� ������� ���������
	while (buff != exitStr) {
		std::cout << ">>";
		std::getline(std::cin, buff);

		MainElm* curMainElmPtr = subjectFound(buff);
		// ���� ������� ���������� ��� ���������� ����������
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

//@brief ���� �������� ���������� �� ���������
//@return ���������� true, ���� ��������� ���� ��������, ����� false
bool edit_removeSubject() {
	bool res(false);

	std::cout << ("������� �������� ����������, ������� ������ �������, ��� ������ ������� " + exitStr) << std::endl;
	std::string buff("");

	// ���� �������� �� ����� ������� ��������� ��� �������� ����������
	while (buff != exitStr) {
		std::cout << ">>";
		std::getline(std::cin, buff);

		// �������� ����������
		if (subjectFound(buff) and buff != exitStr) {
			res = true;
			removeMainElm(buff);
			system("cls");
			buff = exitStr;
		}
		// �������� ������� ����� �������� �������� ��� ������ ��������
		else if (buff == exitStr)
			system("cls");
		else
			std::cout << "���������� �� �������" << std::endl;
	}
	return res;
}

//@brief ���� �������� ������ ���������� �� ����������
//@return ���������� true, ���� ��������� ���� ��������, ����� false
bool edit_removeSession() {
	bool res(false);

	std::cout << ("������� �������� ����������, �� ������� ������ ������� ����� ����������, ��� ������ ������� " + exitStr) << std::endl;
	std::string buffMainElm("");

	// ���� ������ ����������
	while (buffMainElm != exitStr) {
		std::cout << ">>";
		std::getline(std::cin, buffMainElm);

		MainElm* curMainElmPtr = subjectFound(buffMainElm);
		if (curMainElmPtr != nullptr and buffMainElm != exitStr) {
			std::vector<std::string> action = sessionKind;
			action.push_back("����� �� ������");

			bool exit(false);
			// ���� ������ ������� ����������
			while (exit != true) {
				system("cls");
				printStructure();
				std::cout << ("�������� ����� ����������, ������� ������ ������� � ���������� " + buffMainElm) << std::endl;
				ask(action);

				int ans = inputChoice(action.size());

				// �������� ������ ����������
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

//@brief ���������� ���������� � ��������� �� �� ��������
//@return ���������� ��������� �� ��������� ����������, ���� �� ������, �� nullptr
//@param name - �������� ����������, ������� ��������� �����
MainElm* subjectFound(std::string name) {
	MainElm* curMainElmPtr = mainPtr;
	while (curMainElmPtr->subject != name and curMainElmPtr->ptr1 != nullptr)
		curMainElmPtr = curMainElmPtr->ptr1;
	if (curMainElmPtr->subject == name)
		return curMainElmPtr;
	else
		return nullptr;
}

//@brief �������� �� ������������ ���������� �������� ����������
//@param str - ������, ������� ����������� �� ������� ���� ����� ����� ��������
void isAdequate(const std::string str) {
	bool res(false);
	if (str != exitStr) //������ ������
	{
		std::string necessarySymbols("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
		necessarySymbols = necessarySymbols + "�������������������������������������Ũ��������������������������";
		for (int i(0); i < necessarySymbols.size(); i++) {
			if (str.find(necessarySymbols[i]) != -1)
				res = true; //���� ���� ���� ������ �� �������� ������;
		}
		if (!res) //���� �� ���� �� �������� �������� �� ������
			throw std::invalid_argument("���� ������ ��������� ���� �� ���� ����� ��������");
	}
}