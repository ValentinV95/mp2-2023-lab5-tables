#include <cstdlib>
#include "arithmetic.hpp"
#include "tables.hpp" 
#include "polynoms.hpp"

Polynom calc_polynom(const string &expr) {
	TPostfix<Polynom> postfix;
	vector<string> lexems = arithmetic_to_lexems(expr);
	try {
		postfix.toPostfix(lexems);
	}
	catch (const exception &e) {
		cout << e.what() << endl;
	}
	postfix.askOperands(cin);
	Polynom res;
	try {
		res = postfix.calculate();
		cout << res << endl;
	}
	catch (const exception &e) {
		cout << e.what() << endl;
	}
	return res;
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");
	char buf;
	std::string namebuf;
	std::string polybuf;
	UnordTable<std::string, Polynom> ut;
	OrdTable<std::string, Polynom> ot;
	HashTable<std::string, Polynom> ht(1000);
	while (true) {
		bool quit = false;
		std::cout << "����� ���������� � ��������� �� ������ � �������� ���������, �������� ��������:" << std::endl;
		std::cout << "1) �������� ������� � �������;" << std::endl << "2) ������� ������� �� �������;" << std::endl;
		std::cout << "3) ������� ������� �� �����;" << std::endl << "4) �����." << std::endl;
		get_var(buf);
		switch (buf) {
			case '1': {
				std::cout << "������� ��� ��������: ";
				std::getline(std::cin, namebuf);
				std::cout << "������� �������������� ��������� �� x, y, z, ���������� ������� (��������� ^, +, -, *)" << std::endl;
				std::cout << "������: (5*x^2 + 6*y*z) * x^3 (������ ������� * ����� x,y,z)." << std::endl;
				std::getline(std::cin, polybuf);
				try {
					Polynom poly = calc_polynom(polybuf);
					ut.insert(namebuf, poly);
					ot.insert(namebuf, poly);
					ht.insert(namebuf, poly);
				}
				catch (const std::exception& e) {
					std::cout << "Exception: " << e.what() << std::endl;
				}
				break;
			}
			case '2': {
				std::cout << "������� ��� ��������: ";
				std::getline(std::cin, namebuf);
				std::cout << "�������� �������: " << std::endl;
				try {
					Polynom* poly = ut.find(namebuf);
					if (poly != nullptr) {
						std::cout << *poly << std::endl;
					}
					ut.pop(namebuf);
					ot.pop(namebuf);
					ht.pop(namebuf);
				}
				catch (const std::exception& e) {
					std::cout << "Exception: " << e.what() << std::endl;
				}
				break;
			}
			case '3': {
				std::cout << "������� ��� ��������: ";
				std::getline(std::cin, namebuf);
				std::cout << "�������� �������: " << std::endl;
				try {
					Polynom* poly = ut.find(namebuf);
					if (poly != nullptr) {
						std::cout << *poly << std::endl;
					}
					poly = ot.find(namebuf);
					poly = ht.find(namebuf);
				}
				catch (const std::exception& e) {
					std::cout << "Exception: " << e.what() << std::endl;
				}
				break;
			}
			case '4': {
				quit = true;
				break;
			}
			default: {
				continue;
			}
		}
		if (quit == true) { break; }
	}
}
