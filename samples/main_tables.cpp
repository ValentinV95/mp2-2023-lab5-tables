#include <iostream>
#include "arithmetic.h"

int main() {
	UnorderedTable<std::string, Polynom> T1;
	OrderedTable<std::string, Polynom> T2;
	HashTable T3;
	std::string str;
	int choose;
	while (true) {
			std::cout << "Enter \"1\" if you want to edit the set of polynomials available to you\n";
			std::cout << "Enter \"2\" if you want to write an arithmetic expression with polynomials\n";
			std::cout << "Enter \"0\" to end work with program\n";
			std::cin >> choose;
			system("cls");
			if (choose == 2) while (true) {
				try {
					std::cout << "Enter a string what you want to count or enter \"end\" to end entering arithmetic expressions \n";
					std::cout << "Available math fuctions:sin, cos, tan, cot, exp, log \n";
					std::cout << "After functions you need to enter \'(\'\n";
					std::cout << "You can only use math functions for numbers or polynomials of degree 0\n";
					std::cout << "Also, the divisor can only be a number or a polynomial of degree 0\n";
					std::cout << "You can enter any names of the form #set of letters##set of numbers# for polynomials that are in table with the exeption of the names of available math functions\n";
					std::getline(std::cin, str);
					if (str == "end") {
						system("cls");
						break;
					}
					if (str == "") {
						system("cls");
						continue;
					}
					TPostfix solution(str);
					Polynom res = solution.count(T1, T2, T3);
					system("cls");
					do {
						std::cout << str << '\n';
						std::cout << "Res: " << res << "\n\n";
						std::cout << "Enter \"1\" if you want to store this polynomial\n";
						std::cout << "Enter \"0\" if you don't want to stor this polynomial\n";
						std::cin >> choose;
						if (choose != 0 && choose != 1) {
							system("cls");
							std::cout << "This option does not exist. Try again\n";
						}
					} while (choose != 0 && choose != 1);
					if (choose == 1) {
						try {
							do {
								system("cls");
								std::cout << res << "\n\n";
								std::cout << "Enter any name for this polynom\n";
								std::cin >> str;
							} while (str == "");
							T1.add(str, res);
							T2.add(str, res);
							T3.add(str, res);
						}
						catch (std::exception& e) {
							system("cls");
							std::cout << e.what() << "\n\n";
							std::getline(std::cin, str);
						}
					}
				}
				catch (std::exception& e) {
					system("cls");
					std::cout << str << '\n';
					std::cout << e.what() << "\n\n";
				}
			}
			else if (choose == 1) while (true) {
				try {
					std::cout << "Select an option:\n1)Add new polynomial to table\n2)delete polynomial from table\n3)find a polynomial in table(or rename it)\n0)end edit table sith polynomials\n";
					std::cin >> choose;
					if (choose < 0 || choose>3) {
						system("cls");
						std::cout << "This option does not exist. Try again\n";
						continue;
					}
					if (choose == 0) {
						system("cls");
						break;
					}
					else if (choose == 1) {
						Polynom p;
						system("cls");
						std::getline(std::cin, str);
						std::cout << "Enter the polynomial of the variables \"x\", \"y\", \"z\"\n";
						std::cout << "The degree of each variable is an integer from 0 to 9\n";
						std::getline(std::cin, str);
						p = str;
						do {
							system("cls");
							std::cout << p << "\n\n";
							std::cout << "Enter any name for this polynom\n";
							std::cin >> str;
						} while (str == "");
						T1.add(str, p);
						T2.add(str, p);
						T3.add(str, p);
						system("cls");
					}
					else {
						system("cls");
						std::cout << "Enter the name of the polynomial you want to interact with\n";
						std::cin >> str;
						system("cls");
						if (choose == 2) {
							T1.del(str);
							T2.del(str);
							T3.del(str);
						}
						if (choose == 3) {
							do {
								Polynom p;
								T1.find(str);
								T2.find(str);
								p = T3.find(str);
								std::cout << p << "\n\n";
								std::cout << "Select an option:\n1)Rename this polynomial\n0)return to table menu\n";
								std::cin >> choose;
								system("cls");
								if (choose == 1) {
									T1.del(str);
									T2.del(str);
									T3.del(str);
									do {
										system("cls");
										std::cout << p << "\n\n";
										std::cout << "Enter new name for this polynom\n";
										std::cin >> str;
									} while (str == "");
									T1.add(str, p);
									T2.add(str, p);
									T3.add(str, p);
									system("cls");
								}
								else if (choose != 0) {
									std::cout << "This option does not exist. Try again\n";
								}
							} while (choose != 1 && choose != 0);
						}
					}
				}
				catch (std::exception& e) {
					system("cls");
					std::cout << e.what() <<"\n";
				}
			}
			else if (choose == 0) break;
			else {
				system("cls");
				std::cout << "This option does not exist. Try again\n";
			}
	}
}