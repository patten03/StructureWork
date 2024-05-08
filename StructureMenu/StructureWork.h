#ifndef STRUCTUREWORK
#define STRUCTUREWORK

#include "MenuWork.h"
#include <iomanip>
#include <fstream>
#include <sstream>

// ��������� ������� ����������
struct AddElm {
	std::string session;
	AddElm* ptr; // ��������� �� ��������� ����� ����������
};

// ��������� ���������
struct MainElm {
	std::string subject;
	MainElm* ptr1; // ��������� �� ������� ����������
	AddElm* ptr2;  // ��������� �� ����� ����������
};

// ���������� ����������

extern MainElm* mainPtr;                           // ��������� ��������� �� ��� ���������
const extern std::vector<std::string> sessionKind; // ������ ������� ����������
const extern std::string exitStr;                  // ������ ������ �� ���� �����

// ������� ��� ������ ������ �� ����������

void deleteStructure();                           // ������ �������� ���������
MainElm* subjectFound(std::string name);          // ��������� ��������� �� ���������� �� �� ��������
void printStructure();                            // ����� ��������� � �������
MainElm* appendMainElm(std::string appSubject);   // ���������� ���������� � ���������
void removeMainElm(std::string remSubject);       // �������� ���������� �� ���������
bool greater(const MainElm* a, const MainElm* b); // ������� ��������� ��� �������� ���������, ������������ ����� > 
bool lesser(const MainElm* a, const MainElm* b);  // ������� ��������� ��� �������� ���������, ������������ ����� <
void sortStructure(bool compare(const MainElm*, const MainElm*));   // ���������� ���������
void appendAddElm(std::string appSession, std::string subjectName); // ���������� ������ ���������� � ���������
void removeAddElm(std::string remSession, MainElm* subjectPtr);     // �������� ������ ���������� �� ���������

// ������ ��� ������ � �������������, ����

void menu();                            // �������� ���� ���������
bool continueWriting();                 // ���� ������ ��� �������� ���������
bool insertAddElm(MainElm* subjectPtr); // ������ ���������� ������� ���������� ��� ��������
bool createFile();                      // ���������� ��������� � ����
void loadFile(std::string filename);    // �������� ��������� �� �����
bool editStructure();                   // ���� �������������� ���������
bool menuSorting();                     // ���� ���������� ��������� �� �����������

// ���� �������������� ���������

bool edit_appendSession(); // ���������� ������ ����������
bool edit_removeSubject(); // �������� ����������
bool edit_removeSession(); // �������� ������ ����������

// �������������� �������

bool receiveISS(const std::string& filename); // ������ ��� ������ ������ ������� .iss
void isAdequate(const std::string str);       // �������� �� ������������ ���������� �������� ����������

#endif // STRUCTUREWORK