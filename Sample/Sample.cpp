// implementation of a user app
#include "arithmetic.h"

int main()
{
	string name, input1, input2;
	short action1;
	char again = 'y', save;
	bool firstly = true, flag;
	TPostfix T;
	Polynomial tmp;
	setlocale(0, "Rus");
	try
	{
		cout << "��� �������� � ��������� - � ����� log.txt" << endl
			<< "������� �����:" << endl << "1)���� � ���������� ��������" <<
			endl << "2)���� � ������� ��������� � ����������" << endl;
		cin >> action1;
		while (again == 'y')
		{

			while (action1 == 1)
			{
				cout << "������� ���:" << endl;
				cin >> name;
				cout << "������� ���������� ������� � ��������, � ����� - ������: ����������� ����� �������, ������� x, ������� y, ������� z : " << endl;
				cin >> tmp;
				cout << tmp;
				T.insert_polynomial(name, tmp, true);
				cout << "������� �����:" << endl << "1)���� � ���������� ��������" <<
					endl << "2)����� �������� �� �����" << endl << "3)���� � ������� ��������� � ����������" << endl;
				cin >> action1;
				firstly = false;
			}
			while (action1 == 2 && !firstly)
			{
				cout << "������� ���: (����� ������� ������� ��� ��������� �� ������ � ������ ��� ����������)" << endl;
				cin >> name;
				cout << T.search(name) << endl;
				cout << "������� �����:" << endl << "1)���� � ���������� ��������" <<
					endl << "2)����� �������� �� �����" << endl << "3)���� � ������� ��������� � ����������" << endl;
				cin >> action1;
				firstly = false;
			}
			while ((firstly && action1 == 2) || action1 == 3 && !firstly)
			{
				cout << "������� ���������:" << endl << " � �������� ���� ������ ���������� ��� ���������. ������ ������ ����� ������ ���� ������ ���������� ��������, ��������� - �����, ����� ��� '_'" << endl
					<< " � ����� ���������� �������� � ����� ����� ��������� ��������� �� ������ �� ��� ���������" << endl
					<< " � ��� ���������� ����� ������� Enter" << endl;
				while (true)
				{
					getline(cin, input1);

					input2.clear();
					flag = false;
					for (size_t i = 0; i < input1.length(); i++)
						if (input1[i] != ' ') input2.push_back(input1[i]);
						else flag = true;
					if (input2.length() != 0)
					{
						if (flag)
							cout << input2 << endl;
						break;
					}

				}
				/*getline(cin, input1);

				input2.clear();
	
				for (size_t i = 0; i < input1.length(); i++)
					if (input1[i] != ' ') input2.push_back(input1[i]);
				cout << input2;
				*/
				T.Polish_Notation(input2, false);
				T.asker();
				tmp = T.count();
				cout << " = " << tmp << endl;
				cout << "��������� ���������� ��������? 'y'/<����� ������>" << endl;
				cin >> save;
				if (save == 'y')
				{
					cout << "������� ��� ��� ��������" << endl;
					cin >> name;
					T.insert_polynomial(name, tmp, true);
				}
				cout << "������� �����:" << endl << "1)���� � ���������� ��������" <<
					endl << "2)����� �������� �� �����" << endl << "3)���� � ������� ��������� � ����������" << endl;
				cin >> action1;
				firstly = false;
			}


		}
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}
//
//
//int main()
//{
//	setlocale(0, "Rus");
//	try {
//		string input, name;
//		Polynomial p;
//		cin >> name;
//		cin >> p;
//		cin >> input;
//		TPostfix T;
//		T.insert_polynomial(name, p, true);
//		T.Polish_Notation(input, true);
//		T.asker();
//		cout << " = " << T.count() << endl;
//	}
//	catch (const exception& e)
//	{
//		cout << e.what();
//	}
//}