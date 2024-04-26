#include "StructureWork.h"
#include "MenuWork.h"

bool receiveISS(const std::string& filename) {
	return (filename.rfind(".iss") != std::string::npos);
}

void menu() {
	std::cout << "����� ���������� � ��������� StructureWork." << std::endl
		<< "��������� �������� � �������� ������������ � �� �������� ����������." << std::endl << std::endl
		<< "��� ������ � ������� ��� ������ ��������� � ��� �� ����������, ��� � ���������." << std::endl << std::endl;

	bool quit(false); // ���������� ������ �� ���������
	while (!quit) {
		std::cout << "�������� ��������:" << std::endl;
		std::vector<std::string> menuPanel{
			"������� ����",
			"������������� ����",
			"����� �� ���������"
		};
		ask(menuPanel); // ����� �������� � ������� ��� �� ������ �������������
		int choice = inputChoice(menuPanel.size());

		std::string file;
		// ������� �� ����� �������� �������������
		switch (choice) {
		case 1:
		{ // �������� �����

			break;
		}
		case 2:
		{ // �������������� �����
			file = findFile("�������� ����:", receiveISS);
			if (file != "") {
				continue;
			}
			break;
		}
		case 3:
		{
			quit = true;
			break;
		}
		default:
			break;
		}
	}
}
