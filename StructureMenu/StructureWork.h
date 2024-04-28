#ifndef STRUCTUREWORK
#define STRUCTUREWORK

#include "MenuWork.h"

enum sessionType { test = 1, exam, courseWork, courseProject };


// структура методов оценивания
struct AddElm {
	std::string session;
	AddElm* ptr;
};

// структура дисциплин
struct MainElm {
	std::string subject;
	MainElm* ptr1; // ptrDown, указатель на учебную дисциплину
	AddElm* ptr2;  // ptrLeft, указатель на метод оценивания
};

// начальный указатель на всю структуру
extern MainElm* mainPtr;

void printStructure();

void appendMainElm(std::string appSubject);
void removeMainElm(std::string remSubject);

void appendAddElm(std::string session, std::string subjectName);
void removeAddElm(std::string remSession, std::string subjectName);

void menu();
bool receiveISS(const std::string& filename);

#endif // STRUCTUREWORK