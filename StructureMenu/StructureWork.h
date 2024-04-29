#ifndef STRUCTUREWORK
#define STRUCTUREWORK

#include "MenuWork.h"
#include <iomanip>
#include <fstream>
#include <sstream>

// ���� ������� ����������
enum sessionType { test = 1, exam, courseWork, courseProject };

// ������ ������
extern std::string exitStr;

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
void continueWriting();

// ���� �������������� ���������
void editStructure();

// ���������� ��������� � ����
void createFile();

// �������� ��������� �� �����
void loadFile(std::string filename);

// ������ �������� ���������
void deleteStructure();

// ������ ��� ������ ������ ������� .iss
bool receiveISS(const std::string& filename);

#endif // STRUCTUREWORK