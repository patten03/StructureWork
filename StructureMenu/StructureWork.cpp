#include "StructureWork.h"
#include "MenuWork.h"

MainElm* mainPtr = nullptr;

const std::vector<std::string> sessionKind{
	"ЗАЧЕТ",
	"ЭКЗАМЕН",
	"КР",
	"КП",
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

	// случай, когда в структуре нет ни одного элемента
	if (mainPtr == nullptr) {
		mainPtr = appPtr;
		appPtr->ptr1 = nullptr;
	}

	else {
		while (curPtr->ptr1 != nullptr) {
			curPtr = curPtr->ptr1; // перебор элементов
		}
		curPtr->ptr1 = appPtr;
	}
	return appPtr;
}

void removeMainElm(std::string remSubject) {
	MainElm* curMainElmPtr = mainPtr;
	MainElm* precMainElmPtr = nullptr;
	// перебор по дисциплинам, поиск требуемой
	while (curMainElmPtr != nullptr and curMainElmPtr->subject != remSubject) {
		precMainElmPtr = curMainElmPtr;
		curMainElmPtr = curMainElmPtr->ptr1;
	}

	// случай, когда дисциплина не найдена
	if (curMainElmPtr->subject != remSubject)
		return;

	// удаление всех методов оценивания
	AddElm* curAddElmPtr = curMainElmPtr->ptr2;
	AddElm* succAddElmPtr = nullptr;
	while (curAddElmPtr != nullptr) {
		succAddElmPtr = curAddElmPtr->ptr;
		delete curAddElmPtr;
		curAddElmPtr = succAddElmPtr;
	}
	curMainElmPtr->ptr2 = nullptr;

	// удаление дисциплины

	// случай, когда дисциплина идет сразу после указателя на структуру
	if (mainPtr == curMainElmPtr) {
		MainElm* remPtr = curMainElmPtr;
		mainPtr = curMainElmPtr->ptr1;
		delete remPtr;

		return;
	}

	// общий случай

	MainElm* remPtr = curMainElmPtr;
	precMainElmPtr->ptr1 = curMainElmPtr->ptr1;
	delete remPtr;
}

void appendAddElm(std::string appSession, MainElm* subjectPtr) {
	if (subjectPtr != nullptr) {

		// создание элемента метода оценивания
		AddElm* tmp = new AddElm;
		tmp->ptr = nullptr;
		tmp->session = appSession;

		// проверка на наличие хоть каких-то методов оценивания в программе
		if (subjectPtr->ptr2 == nullptr) // случай отсутствия методов оценивания
			subjectPtr->ptr2 = tmp;
		else {                              // случай наличия методов оценивания
			AddElm* curAddElmPtr = subjectPtr->ptr2;
			// перебор методов оценивания
			while (curAddElmPtr->ptr != nullptr)
				curAddElmPtr = curAddElmPtr->ptr;
			curAddElmPtr->ptr = tmp;
		}
	}
	else {} // TODO придумать какое-нибудь предупреждение или ошибку, когда дисциплина не была найдена
}

void removeAddElm(std::string remSession, MainElm* subjectPtr) {
	// проверка на отсутсвие методов оценивания
	if (subjectPtr->ptr2 == nullptr)
		return;

	AddElm* curAddElmPtr = subjectPtr->ptr2;
	// случай, когда метод оценивания у дисциплины единственный
	if (curAddElmPtr->ptr == nullptr) {
		// метод оценивания совпадает
		if (curAddElmPtr->session == remSession) {
			delete curAddElmPtr;
			subjectPtr->ptr2 = nullptr;
		}
		return;
	}

	AddElm* precAddElmPtr = nullptr; // предыдущий элемент
	// перебор элементов
	while (curAddElmPtr->session != remSession and curAddElmPtr->ptr != nullptr) {
		precAddElmPtr = curAddElmPtr;
		curAddElmPtr = curAddElmPtr->ptr;
	}

	if (curAddElmPtr->session == remSession) {
		AddElm* remPtr = curAddElmPtr;           // сохранение указателя на удаляемый элемент

		// случай, когда был выбран первый метод оценивания и в списке он не один
		if (precAddElmPtr == nullptr)
			subjectPtr->ptr2 = curAddElmPtr->ptr;  // привязка к дисциплины и метода оценивания между удаляемым методом оценивания
		else
			precAddElmPtr->ptr = curAddElmPtr->ptr;  // привязка к элементов между удаляемыми
		delete remPtr;                               // удаление требуемого элемента
	}
}

void printStructure() {
	const int widthHead(20);
	const int widthCell(10);

	MainElm* curMainElmPtr;
	curMainElmPtr = mainPtr;

	std::cout << "Вид структуры:" << std::endl;
	// перебор дисциплин для вывода
	while (curMainElmPtr != nullptr) {
		std::cout << std::left << std::setw(widthHead) << curMainElmPtr->subject;

		AddElm* curAddElmPtr = curMainElmPtr->ptr2;
		// перебор методов оценивания для вывода
		while (curAddElmPtr != nullptr) {
			std::cout << std::left << std::setw(widthCell) << curAddElmPtr->session;
			curAddElmPtr = curAddElmPtr->ptr;
		}

		// предотвращение ввода ввода enter при выводе последнего элемента
		if (curMainElmPtr->ptr1 != nullptr)
			std::cout << std::endl;

		curMainElmPtr = curMainElmPtr->ptr1;
	}
	// случай, когда структура пустая
	if (mainPtr == nullptr) {
		std::cout << "Структура пуста";
	}
}

void menu() {
	// вывод вступления
	std::cout << "Добро пожаловать в программу StructureWork." << std::endl
		<< "Программа работает с учебными дисциплинами и их методами оценивания." << std::endl << std::endl
		<< "Для работы с файлами они должны находится в той же директории, что и программа." << std::endl << std::endl;


	bool isSaved(false); // переменная указывает на то, была ли сохранена структура в файл
	bool quit(false);    // переменная выхода из программы
	while (!quit) {

		if (mainPtr != nullptr) {
			if (isSaved)
				std::cout << "Текущая структура сохранена" << std::endl;
			else
				std::cout << "Текущая структура не сохранена" << std::endl;
		}

		std::cout << "Выберите действие:" << std::endl;
		std::vector<std::string> menuPanel{
			"Создать новую структуру",
			"Дозаписать структуру",
			"Редактировать структуру",
			"Сохранить структуру в файл",
			"Загрузить структуру из файла",
			"Вывести структуру в консоль",
			"Выйти из программы"
		};
		ask(menuPanel); // вывод действий в консоль для их выбора пользователем
		int choice = inputChoice(menuPanel.size());

		std::string file;
		// реакция на выбор действия пользователем
		switch (choice) {
		case 1: // создание новой структуры
		{
			deleteStructure();
			continueWriting();
			isSaved = false;
			break;
		}
		case 2: // дозапись структуры
		{
			isSaved = !continueWriting();
			break;
		}
		case 3: // редактирование структуры
		{
			if (mainPtr != nullptr)
				isSaved = !editStructure();
			else
				std::cout << "Невозможно редактировать пустую структуру" << std::endl;
			break;
		}
		case 4: // сохранение структуры в файл
		{
			isSaved = createFile();
			break;
		}
		case 5: // загрузка структуры из файла
		{
			file = findFile("Выберите файл:", receiveISS);
			if (file != "") {
				deleteStructure();
				loadFile(file);
				isSaved = true;
			}
			break;
		}
		case 6: // вывод структуры в консоль
		{
			printStructure();
			std::cout << std::endl << std::endl;
			break;
		}
		case 7: // выход из программы
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

//@return если были введены измения то true, иначе false
bool continueWriting() {
	std::string buffMain("");
	bool wasChanged(false); // флаг, показывает факт того, были ли введены какие-либо изменения в структуру
	while (buffMain != exitStr) {
		std::cout << ("Введите название дисциплины, для выхода введите " + exitStr) << std::endl;
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

//@return возвращает true, если структура была изменена, иначе false
bool insertAddElm(MainElm* subjectPtr) {
	bool res(false);

	std::vector<std::string> action = sessionKind;
	action.push_back("Выйти из выбора");

	std::vector<std::string> curList;

	bool exit(false);
	while (exit != true) {
		std::cout << ("Выберите методы оценивания для дисциплины " + subjectPtr->subject) << std::endl;
		ask(action);
		std::cout << "Список введенных методов оценивания:" << std::endl;
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

//@return возвращает true, если файл был создан, иначе false
bool createFile() {
	MainElm* curMainElmPtr;
	curMainElmPtr = mainPtr;

	// случай, когда структура пустая
	if (mainPtr == nullptr) {
		std::cout << "Нельзя записать в файл пустую структуру" << std::endl;
		return false; // файл не был сохранен, по ошибке
	}

	std::string filename = askName("Введите название файла, для выхода введите " + exitStr);
	// проверка на символ выхода и то, является ли структура пустой
	if (filename != exitStr) {
		filename = filename + "_" + currentTime() + ".iss";

		std::fstream outstream;
		outstream.open(filename, std::ios_base::out);

		// перебор дисциплин для вывода
		while (curMainElmPtr != nullptr) {
			outstream << curMainElmPtr->subject;

			AddElm* curAddElmPtr = curMainElmPtr->ptr2;
			// перебор методов оценивания для вывода
			while (curAddElmPtr != nullptr) {
				outstream << '\t' << curAddElmPtr->session;
				curAddElmPtr = curAddElmPtr->ptr;
			}

			// предотвращение ввода ввода enter при выводе последнего элемента
			if (curMainElmPtr->ptr1 != nullptr)
				outstream << std::endl;

			curMainElmPtr = curMainElmPtr->ptr1;
		}

		std::cout << "Структура сохранена в файл под названием " << filename << std::endl;

		outstream.close();
		return true; // файл был сохранен
	}
	return false; // файл не был сохранен, по желанию пользователя
}

void loadFile(std::string filename) {
	std::fstream instream;
	instream.open(filename, std::ios_base::in);

	// проверка на открытие файла
	if (!instream.is_open()) {
		std::cout << "Произошла ошибка при открытии файла" << std::endl;
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

//@return возвращает true, если структура была изменена, иначе false
bool editStructure() {
	bool res(false);

	if (mainPtr != nullptr) {
		std::vector<std::string> action{
	"Добавить метод оценивания",
	"Удалить дисциплину",
	"Удалить метод оценивания",
	"Выйти в главное меню"
		};

		bool quit(false);

		while (!quit) {
			printStructure();
			std::cout << std::endl;
			std::cout << "Выберите действие:" << std::endl;
			ask(action);
			int ans = inputChoice(action.size());

			printStructure();
			std::cout << std::endl;
			switch (ans) {
			case 1: // добавление метода оценивания
			{
				res = edit_appendSession();
				break;
			}
			case 2: // удаление дисциплины
			{
				res = edit_removeSubject();
				break;
			}
			case 3: // удаление метода оценивания
			{
				res = edit_removeSession();
				break;
			}
			case 4: // выход в меню
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

//@return возвращает true, если структура была изменена, иначе false
bool edit_appendSession() {
	bool res(false);

	std::cout << ("Введите название дисциплины, к которой хотите добавить методы оценивания, для выхода введите " + exitStr) << std::endl;
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
			std::cout << "Дисциплина не найдена" << std::endl;
	}
	return res;
}

//@return возвращает true, если структура была изменена, иначе false
bool edit_removeSubject() {
	bool res(false);

	std::cout << ("Введите название дисциплины, которую хотите удалить, для выхода введите " + exitStr) << std::endl;
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
			std::cout << "Дисциплина не найдена" << std::endl;
	}
	return res;
}

//@return возвращает true, если структура была изменена, иначе false
bool edit_removeSession() {
	bool res(false);

	std::cout << ("Введите название дисциплины, из которой хотите удалить метод оценивания, для выхода введите " + exitStr) << std::endl;
	std::string buffMainElm("");

	while (buffMainElm != exitStr) {
		std::cout << ">>";
		std::getline(std::cin, buffMainElm);

		MainElm* curMainElmPtr = subjectFound(buffMainElm);
		if (curMainElmPtr != nullptr and buffMainElm != exitStr) {
			std::vector<std::string> action = sessionKind;
			action.push_back("Выйти из выбора");

			bool exit(false);
			while (exit != true) {
				system("cls");
				printStructure();
				std::cout << std::endl;
				std::cout << ("Выберите метод оценивания, который хотите удалить у дисциплины " + buffMainElm) << std::endl;
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
			std::cout << "Дисциплина не найдена" << std::endl;
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