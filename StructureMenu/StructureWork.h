#ifndef STRUCTUREWORK
#define STRUCTUREWORK

#include "MenuWork.h"
#include <iomanip>
#include <fstream>
#include <sstream>

// структура методов оценивания
struct AddElm {
	std::string session;
	AddElm* ptr; // указатель на следующий метод оценивания
};

// структура дисциплин
struct MainElm {
	std::string subject;
	MainElm* ptr1; // указатель на учебную дисциплину
	AddElm* ptr2;  // указатель на метод оценивания
};

// глобальные переменные

extern MainElm* mainPtr;                           // начальный указатель на всю структуру
const extern std::vector<std::string> sessionKind; // массив методов оценивания
const extern std::string exitStr;                  // символ выхода из меню ввода

// функции для прямой работы со структурой

void deleteStructure();                         // полное удаление структуры
MainElm* subjectFound(std::string name);        // получения указателя на дисциплину по ее названию
void printStructure();                          // вывод структуры в консоль
MainElm* appendMainElm(std::string appSubject); // добавление дисциплины в структуру
void removeMainElm(std::string remSubject);     // удаление дисциплины из структуры
void appendAddElm(std::string appSession, std::string subjectName); // добавление метода оценивания в структуру
void removeAddElm(std::string remSession, MainElm* subjectPtr);     // удаление метода оценивания из структуры

// функии для работы с пользователем, меню

void menu();                            // основное меню программы
bool continueWriting();                 // меню записи или дозаписи структуры
bool insertAddElm(MainElm* subjectPtr); // запись нескольких методов оценивания для предмета
bool createFile();                      // сохранение структуры в файл
void loadFile(std::string filename);    // загрузка структуры из файла
bool editStructure();                   // меню редактирования структуры

// меню редактирования структуры

bool edit_appendSession(); // добавление метода оценивания
bool edit_removeSubject(); // удаление дисциплины
bool edit_removeSession(); // удаление метода оценивания

// допольнительный функции

bool receiveISS(const std::string& filename); // фильтр для выбора файлов формата .iss

#endif // STRUCTUREWORK