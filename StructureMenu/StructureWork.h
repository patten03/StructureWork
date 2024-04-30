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
void appendMainElm(std::string appSubject);
// �������� ���������� �� ���������
void removeMainElm(std::string remSubject);

// ���������� ������ ���������� � ���������
void appendAddElm(std::string session, std::string subjectName);
// �������� ������ ���������� �� ���������
void removeAddElm(std::string remSession, std::string subjectName);

// ������ ������� ���������� ��� ��������
void insertAddElm(std::string subjectName);

// �������� ���� ���������
void menu();

// ���� ������ ��� �������� ���������
bool continueWriting();

// ���� �������������� ���������
void editStructure();

void edit_appendSession();
void edit_removeSubject();
void edit_removeSession();

bool subjectFound(std::string name);
bool sessionFound(std::string sessionName, std::string subjectName);

// ���������� ��������� � ����
bool createFile();

// �������� ��������� �� �����
void loadFile(std::string filename);

// ������ �������� ���������
void deleteStructure();

// ������ ��� ������ ������ ������� .iss
bool receiveISS(const std::string& filename);

#endif // STRUCTUREWORK