#ifndef STRUCTUREWORK
#define STRUCTUREWORK

#include "MenuWork.h"

// типы методов оценивания
enum sessionType { test = 1, exam, courseWork, courseProject };

// символ выхода
extern std::string exitStr;

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

// вывод структуры в консоль
void printStructure();

// добавление дисциплин в структуру
void appendMainElm(std::string appSubject);
// удаление дисциплины из структуры
void removeMainElm(std::string remSubject);

// добавление метода оценивания в структуру
void appendAddElm(std::string session, std::string subjectName);
// удаление метода оценивания из структуры
void removeAddElm(std::string remSession, std::string subjectName);

// основное меню программы
void menu();

// меню создания файлов
void createFile();

void insertAddElm(std::string subjectName);

// меню редактирования файлов
void editFile();

// фильтр для выбора файлов формата .iss
bool receiveISS(const std::string& filename);

#endif // STRUCTUREWORK