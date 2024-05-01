#include "AVLTreeTable.h"
#include "HashTable.h"
#include "UnorderedTable.h"
#include <iostream>

using namespace std;

void DoArithmetic(UnorderedTable& table, AVLTreeTable& tree, HashTable& hashtable) {
	cout << "You can use the polynomials that are in the table for arithmetic expressions. You can also add the result to the table." << endl;
	string exprstr;
	cout << "Entry rules: " << endl;
	cout << "Enter an expression without spaces" << endl;
	cout << "The expression itself can contain only numbers, polynoms, and functions used to numbers (sin(), cos(), tg(), ctg(), ln(), exp())" << endl;
	cout << "All operations are separated by parentheses, that is, an expression of the form 5+-4 is not allowed" << endl;
	int fl;
	do {
		fl = 1;
		try {
			cout << "Enter a correct expression" << endl;
			cin >> exprstr;
			polynoms resTable, resTree, resHash;
			resTable = table.Arithmetic(exprstr);
			resTree = table.Arithmetic(exprstr);
			resHash = table.Arithmetic(exprstr);

			cout << "the result of calculation is: " << endl;
			cout << "Unoredered table: " << endl;
			cout << resTable << endl;
			cout << "AVL TRee :" << endl;
			cout << resTree << endl;
			cout << "Hash table: " << endl;
			cout << resHash << endl;

			cout << "Would you like to add the result to tables? Enter '+' as Yes, '-' as No " << endl;
			char adding;
			cin >> adding;

			if (adding == '+') {
				string name;
				cout << "Enter the name of polynom: " << endl;
				cin >> name;
				table.add(name, resTable);
				cout << "UnorderedTable: add. Operations: " << table.counttable << endl;
				tree.add(name, resTree);
				cout << "AVLTreeTable: add. Operations: " << tree.counttree << endl;
				hashtable.add(name, resHash);
				cout << "HashTable: add. Operations: " << hashtable.counthash << endl;

			}

			fl = 0;
		}
		catch (const exception& e) {
			cout << "The entered string is incorrect" << endl;
			cout << e.what() << endl;
			cout << "Remark: " << endl;
			cout << "If the error is in the '-1' character, it means that the expression ends with an operation or an opening parenthesis" << endl;
			cout << "If the error is in the '-2' character, it means that the number of openingand closing brackets is not equal" << endl;

		}
	} while (fl);
};


int main() {
	std::cout << "To use tables please enter the amount of polynoms, you want to save and operate with: " << std::endl;
	int amount;
	std::cin >> amount;
	std::cout << "Enter the monomials of the polynomial according to the rules: " << std::endl;
	std::cout << "1) the degree of a polynomial as a single number, the digits of which are the degrees of variables. (the degree of each variable cannot exceed 9) " << std::endl;
	std::cout << "2) After the degree, specify the coefficient before the monome. " << std::endl;
	std::cout << "For example, the monomial 16y^5z should be entered as '51 16' " << std::endl;
	std::cout << "Monomes with zero coefficients cannot be introduced " << std::endl;
	std::cout << "to complete the input, type '-1 -1' " << std::endl;
	std::cout << "Name of the polynom starts with a letter and contains only letters and numbers." << std::endl;
	UnorderedTable table;
	AVLTreeTable tree;
	HashTable hashtable;
	for (int i = 0; i < amount; i++) {
		int first = 0;
		double second = 0;
		list<pair<int, double>> entmon;
		string name;
		cout << "Enter the name of polynom, then enter monoms by rules " << endl;
		cin >> name;
		cout << "Monoms: " << endl;
		while (true) {
			cin >> first >> second;
			if (first == -1 && second == -1) break;
			entmon.push_back({ first,second });
		}
		polynoms entered(entmon);
		table.add(name, entered);
		cout << "UnorderedTable: add. Operations: " << table.counttable << endl;
		tree.add(name, entered);
		cout << "AVLTreeTable: add. Operations: " << tree.counttree << endl;
		hashtable.add(name, entered);
		cout << "HashTable: add. Operations: " << hashtable.counthash << endl;
	}
	while (true) {
		cout << "If you would like to add new polynom enter 1" << endl;
		cout << "If you would like to delete polynom enter 2" << endl;
		cout << "If you would like to search polynom enter 3" << endl;
		cout << "If you would like to produce arimetical operaions with polynoms in table enter 4" << endl;
		cout << "If you would like to end enter anything else" << endl;
		short int choice;
		cin >> choice;
		try {
			if (choice == 1) {
				int first = 0;
				double second = 0;
				list<pair<int, double>> entmon;
				string name;
				cout << "Enter the name of polynom, then enter monoms by rules " << endl;
				cin >> name;
				cout << "Monoms: " << endl;
				while (true) {
					cin >> first >> second;
					if (first == -1 && second == -1) break;
					entmon.push_back({ first,second });
				}
				polynoms entered(entmon);
				table.add(name, entered);
				cout << "UnorderedTable: add. Operations: " << table.counttable << endl;
				tree.add(name, entered);
				cout << "AVLTreeTable: add. Operations: " << tree.counttree << endl;
				hashtable.add(name, entered);
				cout << "HashTable: add. Operations: " << hashtable.counthash << endl;
			}
			else if (choice == 2) {
				cout << "Enter the name of polynom which need to be deleted: " << endl;
				string name;
				cin >> name;
				table.clear(name);
				cout << "UnorderedTable: clear. Operations: " << table.counttable << endl;
				tree.clear(name);
				cout << "AVLTreeTable: clear. Operations: " << tree.counttree << endl;
				hashtable.clear(name);
				cout << "HashTable: clear. Operations: " << hashtable.counthash << endl;
			}
			else if (choice == 3) {
				cout << "Enter the name of polynom which you wanto to searh" << endl;
				string name;
				cin >> name;
				cout << table.search(name) << endl;
				cout << "UnorderedTable: search. Operations: " << table.counttable << endl;
				cout << tree.search(name) << endl;
				cout << "AVLTreeTable: search. Operations: " << tree.counttree << endl;
				cout << hashtable.search(name) << endl;
				cout << "HashTable: search. Operations: " << hashtable.counthash << endl;
			}
			else if (choice == 4) {
				DoArithmetic(table, tree, hashtable);
			}
			else break;
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
}