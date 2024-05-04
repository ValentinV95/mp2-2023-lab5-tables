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
		cout << "Лог операций с таблицами - в файле log.txt" << endl
			<< "Введите номер:" << endl << "1)Ввод и сохранение полинома" <<
			endl << "2)Ввод и подсчёт выражения с полиномами" << endl;
		cin >> action1;
		while (again == 'y')
		{

			while (action1 == 1)
			{
				cout << "Введите имя:" << endl;
				cin >> name;
				cout << "Введите количество мономов в полиноме, а затем - мономы: коэффициент перед мономом, степень x, степень y, степень z : " << endl;
				cin >> tmp;
				cout << tmp;
				T.insert_polynomial(name, tmp, true);
				cout << "Введите номер:" << endl << "1)Ввод и сохранение полинома" <<
					endl << "2)Поиск полинома по имени" << endl << "3)Ввод и подсчёт выражения с полиномами" << endl;
				cin >> action1;
				firstly = false;
			}
			while (action1 == 2 && !firstly)
			{
				cout << "Введите имя: (Будет выведен полином или сообщение об ошибке в случае его отсутствия)" << endl;
				cin >> name;
				cout << T.search(name) << endl;
				cout << "Введите номер:" << endl << "1)Ввод и сохранение полинома" <<
					endl << "2)Поиск полинома по имени" << endl << "3)Ввод и подсчёт выражения с полиномами" << endl;
				cin >> action1;
				firstly = false;
			}
			while ((firstly && action1 == 2) || action1 == 3 && !firstly)
			{
				cout << "Введите выражение:" << endl << " · Доступен ввод любого количества имён полиномов. Первый символ имени должен быть буквой латинского алфавита, остальные - буквы, цифры или '_'" << endl
					<< " · Любое количество пробелов в любом месте вводимого выражения не влияет на его результат" << endl
					<< " · Для завершения ввода нажмите Enter" << endl;
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
				cout << "Сохранить полученное значение? 'y'/<любой другой>" << endl;
				cin >> save;
				if (save == 'y')
				{
					cout << "Введите имя для значения" << endl;
					cin >> name;
					T.insert_polynomial(name, tmp, true);
				}
				cout << "Введите номер:" << endl << "1)Ввод и сохранение полинома" <<
					endl << "2)Поиск полинома по имени" << endl << "3)Ввод и подсчёт выражения с полиномами" << endl;
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