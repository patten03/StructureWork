#include "StructureWork.h"

bool receiveISS(const std::string& filename) {
	return (filename.rfind(".iss") != std::string::npos);
}

void menu() {
	std::cout << findFile("��� ����� � ���� �������� ���������", receiveISS);
}