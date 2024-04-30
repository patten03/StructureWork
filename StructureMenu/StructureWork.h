#ifndef STRUCTUREWORK
#define STRUCTUREWORK

#include "MenuWork.h"
#include <iomanip>
#include <fstream>
#include <sstream>

// ���� ������� ����������
enum sessionType { test = 1, exam, courseWork, courseProject };

// ������ ������� ����������
const extern std::vector<std::string> sessionKind;

// ������ ������
const extern std::string exitStr;

// ��������� ������� ����������
struct AddElm {
	std::string session;
	AddElm* ptr;
};

// ��������� ���������
struct MainElm {
	std::string subject;
	MainElm* ptr1; // ptrDown, ��������� �� ������� ����������
	AddElm* ptr2;  // ptrLeft, ��������� �� ����� ����������
};

// ��������� ��������� �� ��� ���������
extern MainElm* mainPtr;

// ����� ��������� � �������
void printStructure();

// ���������� ��������� � ���������
MainElm* appendMainElm(std::string appSubject);
// �������� ���������� �� ���������
void removeMainElm(std::string remSubject);

// ���������� ������ ���������� � ���������
void appendAddElm(std::string appSession, std::string subjectName);
// �������� ������ ���������� �� ���������
void removeAddElm(std::string remSession, MainElm* subjectPtr);

// ������ ������� ���������� ��� ��������
bool insertAddElm(MainElm* subjectPtr);

// �������� ���� ���������
void menu();

// ���� ������ ��� �������� ���������
bool continueWriting();

// ���� �������������� ���������
bool editStructure();

bool edit_appendSession();
bool edit_removeSubject();
bool edit_removeSession();

//bool subjectFound(std::string name);
MainElm* subjectFound(std::string name);

// ���������� ��������� � ����
bool createFile();

// �������� ��������� �� �����
void loadFile(std::string filename);

// ������ �������� ���������
void deleteStructure();

// ������ ��� ������ ������ ������� .iss
bool receiveISS(const std::string& filename);

#endif // STRUCTUREWORK