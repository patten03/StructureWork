#ifndef STRUCTUREWORK
#define STRUCTUREWORK

#include "MenuWork.h"
#include <iomanip>
#include <fstream>
#include <sstream>

// типы методов оценивания
enum sessionType { test = 1, exam, courseWork, courseProject };

// массив методов оценивания
const extern std::vector<std::string> sessionKind;

// символ выхода
const extern std::string exitStr;

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
MainElm* appendMainElm(std::string appSubject);
// удаление дисциплины из структуры
void removeMainElm(std::string remSubject);

// добавление метода оценивания в структуру
void appendAddElm(std::string appSession, std::string subjectName);
// удаление метода оценивания из структуры
void removeAddElm(std::string remSession, MainElm* subjectPtr);

// запись методов оценивания для предмета
bool insertAddElm(MainElm* subjectPtr);

// основное меню программы
void menu();

// меню записи или дозаписи структуры
bool continueWriting();

// меню редактирования структуры
bool editStructure();

bool edit_appendSession();
bool edit_removeSubject();
bool edit_removeSession();

//bool subjectFound(std::string name);
MainElm* subjectFound(std::string name);

// сохранение структуры в файл
bool createFile();

// загрузка структуры из файла
void loadFile(std::string filename);

// полное удаление структуры
void deleteStructure();

// фильтр для выбора файлов формата .iss
bool receiveISS(const std::string& filename);

#endif // STRUCTUREWORK