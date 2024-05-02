// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
ofstream fout("log.txt");

TPostfix::TPostfix(size_t variable, size_t RPN): cap_RPN(RPN), cap_variable(variable), polynomials_inserted(0)
{
	Rev_Pol_Notation = nullptr;
	arr_name_variable = new string[cap_variable]();
}

void TPostfix::Polish_Notation(const string& t, bool need_to_check) {

	Lexeme* tmp = new Lexeme[cap_RPN]();
	delete[]Rev_Pol_Notation;
	Rev_Pol_Notation = tmp;
	ind_RPN = 0;
	ind_variable = 0;

	string inp;
	if (need_to_check)
	{
		for (i = 0; i < t.length(); i++)
			if (t[i] != ' ') inp.push_back(t[i]);
		i = 0;
	}
	else inp = t;
	i = 0;

	size_t quan_open_braсkets = 0;

	while (i < inp.length())
	{
		if(inp[i] == '+') { Lexeme tmp(1, '+', i);

			while (!ops.isEmpty() && (ops.top().type_of_lex == 6 ||
				ops.top().type_of_lex == 5 ||
				(ops.top().type_of_lex == 1)))
				insert_result(ops.pop());

			ops.push(move(tmp));
		}

		else if (inp[i] == '*') { Lexeme tmp(1, '*', i);

			while (!ops.isEmpty() && (ops.top().type_of_lex == 6 ||
				ops.top().type_of_lex == 5 ||
				(ops.top().type_of_lex == 1 &&
					(*(char*)ops.top().lex == '/' || *(char*)ops.top().lex == '*'))))
				insert_result(ops.pop());

			ops.push(move(tmp));
		}

		else if (inp[i] == '/') { Lexeme tmp(1, '/', i);

			while (!ops.isEmpty() && (ops.top().type_of_lex == 6 ||
				ops.top().type_of_lex == 5 ||(
				ops.top().type_of_lex == 1 && *(char*)ops.top().lex == '/')))
				insert_result(ops.pop());

			ops.push(move(tmp));
		}

		else if (inp[i] == '(') {
			quan_open_braсkets++;

			if (inp[i + 1] == ')')
			{
				string except("Incorrect brackets input: brackets at positions ");
				except += to_string(i) + ", " + to_string(i + 1);
				except += " are next to each other";
				throw invalid_argument(except);
			}

			Lexeme tmp(2, '(', i);

			ops.push(move(tmp));
		}

		else if (inp[i] == ')') {
			if (quan_open_braсkets > 0)
			{
				quan_open_braсkets--;

				while (ops.top().type_of_lex != 2)
					insert_result(ops.pop());
				ops.pop();
			}
			else
			{
				string except("Incorrect brackets input at position ");
				except += to_string(i);
				throw invalid_argument(except);
			}
		}

		else if (inp[i] == '-') {
			if (i == 0 || inp[i - 1] == '+' || inp[i - 1] == '*' ||
				inp[i - 1] == '/' || inp[i - 1] == '-' || inp[i - 1] == '(') //if it is an unary minus
			{
				if ((inp[i + 1] <= '9' && inp[i + 1] >= '0') || inp[i + 1] == '-' || inp[i + 1] == '.' || inp[i + 1] == ','
					|| (inp[i+1] >= 'A' && inp[i+1] <= 'Z') || (inp[i+1] >= 'a' && inp[i+1] <= 'z')) //if the minus is followed by an operand or another minus
				{
					Lexeme tmp(5, '-', i); //define if as a unary one
					ops.push(move(tmp));
				}
				else
				{
					string except("Incorrect minus input at position ");
					except += to_string(i);
					throw invalid_argument(except);
				}
			}
			else
			{//define if as a binary one
				Lexeme tmp(1, '-', i);

				while (!ops.isEmpty() && (ops.top().type_of_lex == 6 ||
					ops.top().type_of_lex == 5 ||
					ops.top().type_of_lex == 1 &&
						( *(char*)ops.top().lex == '*' || *(char*)ops.top().lex == '-' || *(char*)ops.top().lex == '/')))
					insert_result(ops.pop());

				ops.push(move(tmp));
			}
		}

		else if ((inp[i] >='A' && inp[i] <= 'Z') || (inp[i] >= 'a' && inp[i] <= 'z')) {//if a polynomial is entered

			string name;
			name += inp[i];
			i++;
			while (i < inp.length() &&
				((inp[i] <= '9' && inp[i] >= '0') || (inp[i] >= 'A' && inp[i] <= 'Z') || (inp[i] >= 'a' && inp[i] <= 'z') || inp[i] == '_'))
			{
				name += inp[i];	//copy its name into an auxiliary variable.
				i++;
			}

			i--;

			if (!avail(name))//if this polynomial has not yet been encountered before
				insert_variable(move(name)); //add his name,
			ind_variable++;

			Lexeme tmp(4, ind_variable-1); //in the corresponding lexeme in the RPN put the name of the polynomial

			insert_result(tmp);
		}

		else{
			if ((inp[i] >= '0' && inp[i] <= '9') || inp[i] == '.' || inp[i] == ',') //numerage input
			{
				double res = 0;
				int after_len = 0, sign = 1, power = 0;
				while (i < inp.length() && inp[i] <= '9' && inp[i] >= '0')
				{
					res *= 10;
					res += inp[i] - '0';
					i++;
				}
				if (i < inp.length() && (inp[i] == '.' || inp[i] == ','))
				{
					i++;
					if ((inp[i]>'9'|| inp[i] < '0') && inp[i] != 'e' ||
						(inp[i] == 'e' && (i<2 || (inp[i - 2] > '9' || inp[i - 2] < '0')))) {
						string except("Incorrect numerage input at position ");
						except += to_string(i);
						throw invalid_argument(except);
					}
					while (i < inp.length() && inp[i] <= '9' && inp[i] >= '0')
					{
						after_len++;
						res += (inp[i] - '0') * pow(10, -1 * after_len);
						i++;
					}
				}
				if (i < inp.length() && inp[i] == 'e')
				{
					i++;
					if (inp.length() - i < 1) {
						string except("Incorrect numerage input at position ");
						except += to_string(i);
						throw invalid_argument(except);
					}
					else if (inp[i] == '-')
					{
						sign = -1;
					}
					else if (inp[i] == '+')
					{
						sign = 1;
					}
					else {
						string except("Incorrect numerage input at position ");
						except += to_string(i);
						throw invalid_argument(except);
					}
					i++;
					if (i < inp.length() && inp[i] <= '9' && inp[i] >= '0')
					while (i < inp.length() && inp[i] <= '9' && inp[i] >= '0')
					{
						power *= 10;
						power += inp[i] - '0';
						i++;
					}
					else {
						string except("Incorrect numerage input at position ");
						except += to_string(i);
						throw invalid_argument(except);
					}
				}
				res *= pow(10, sign * power);
				i--;
				Lexeme tmp(7, res);

				insert_result(tmp);
			}
			else {
				string except("Incorrect character input at position ");
				except += to_string(i);
				throw invalid_argument(except);
			}
		}
		i++;
	}
	if (quan_open_braсkets != 0) //output of quanity and positions of extra '('
	{
		string except("There are ");
		except += to_string(quan_open_braсkets);
		except += " extra '(' in line: at positions ";
		bool first = true;
		while (!ops.isEmpty())
		{
			if (ops.top().type_of_lex == 2)
				if (first)
				{
					except += to_string(ops.pop().pos);
					first = false;
				}
				else
					except += ", " + to_string(ops.pop().pos);
			else
				insert_result(ops.pop());
		}
		throw invalid_argument(except);
	}
	else while (!ops.isEmpty())
		insert_result(ops.pop());
	//arr_value_variable = new Polynomial[ind_variable];
}

void TPostfix::insert_result(const Lexeme& lex)
{
	if (ind_RPN == cap_RPN)
	{
		Lexeme* tmp = new Lexeme[cap_RPN *= 2];
		copy(Rev_Pol_Notation + 0, Rev_Pol_Notation + ind_RPN, tmp);
		delete[]Rev_Pol_Notation;
		Rev_Pol_Notation = tmp;
	}
	Rev_Pol_Notation[ind_RPN++] = lex;
}

void TPostfix::insert_variable(string&& name)
{
	if (ind_variable == cap_variable)
	{
		string* tmp = new string[cap_variable *= 2];
		copy(arr_name_variable + 0, arr_name_variable + ind_variable, tmp);
		delete[]arr_name_variable;
		arr_name_variable = tmp;
	}
	arr_name_variable[ind_variable] = name;
}

void TPostfix::asker()
{
	if (ind_variable > 0)
	{
		if(polynomials_inserted< ind_variable)
		cout << "Для каждого выведенного имени полинома введите количество мономов в нём, а затем - мономы: коэффициент перед мономом, степень x, степень y, степень z : " << endl;
		for (size_t j = 0; j < ind_variable; j++)
		{
			if (!avail(arr_name_variable[j]))
			{
				cout << arr_name_variable[j] << endl;
				Polynomial tmp;
				cin >> tmp;

				insert_polynomial(arr_name_variable[j], tmp);
			}
		}

	}
}

void TPostfix::insert_polynomial(const string& name, const Polynomial& p, bool need_to_insert_name)
{
	if (need_to_insert_name)
	{
		string n(name);
		insert_variable(move(n));
		ind_variable++;
	}

	time_t mytime = time(NULL);
	struct tm* now = localtime(&mytime);
	fout << "Time costs of insertion: (" << now->tm_mday << '.' << now->tm_mon + 1 << '.' << now->tm_year + 1900 << ' ' << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << ')' << endl;

	auto start_1{ chrono::steady_clock::now() };
	UnordTable.push(name, p);
	auto end_1{ chrono::steady_clock::now() };
	chrono::duration<double> es_1 = end_1 - start_1;
	fout << "Unordered table: " << es_1.count() << " sec" << endl;

	auto start_2{ chrono::steady_clock::now() };
	Hsh_Table.push(name, p);
	auto end_2{ chrono::steady_clock::now() };
	chrono::duration<double> es_2 = end_2 - start_2;
	fout << "Hash table: " << es_2.count() << " sec" << endl;

	auto start_3{ chrono::steady_clock::now() };
	RBT_tree.insert(name, p);
	auto end_3{ chrono::steady_clock::now() };
	chrono::duration<double> es_3 = end_3 - start_3;
	fout << "Red-black tree: " << es_3.count() << " sec" << endl << endl;

	polynomials_inserted++;
}

Polynomial TPostfix:: search(const string& name)
{
	time_t mytime = time(NULL);
	struct tm* now = localtime(&mytime);
	fout << "Time costs of search: (" << now->tm_mday << '.' << now->tm_mon + 1 << '.' << now->tm_year + 1900 << ' ' << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << ')' << endl;

	auto start_1{ chrono::steady_clock::now() };
	Polynomial tmp1(UnordTable.return_by_Ldata(name));
	auto end_1{ chrono::steady_clock::now() };
	chrono::duration<double> es_1 = end_1 - start_1;
	fout << "Unordered table: " << es_1.count() << " sec" << endl;
	
	auto start_2{ chrono::steady_clock::now() };
	Polynomial tmp2(Hsh_Table.find(name));
	auto end_2{ chrono::steady_clock::now() };
	chrono::duration<double> es_2 = end_2 - start_2;
	fout << "Hash table: " << es_2.count() << " sec" << endl;

	auto start_3{ chrono::steady_clock::now() };
	Polynomial tmp3(RBT_tree.search(name));
	auto end_3{ chrono::steady_clock::now() };
	chrono::duration<double> es_3 = end_3 - start_3;
	fout << "Red-black tree: " << es_3.count() << " sec" << endl << endl;
	
	if (tmp1 != tmp2)
	{
		throw invalid_argument("Hash table and unordered table returned different polynomials");
	}
	if (tmp1 != tmp3)
	{
		throw invalid_argument("Red-Black tree and unordered table returned different polynomials");
	}
	return tmp1;
}

bool TPostfix::avail(const string& name)
{
	time_t mytime = time(NULL);
	struct tm* now = localtime(&mytime);
	fout << "Time costs of checking availability: (" << now->tm_mday << '.' << now->tm_mon + 1 << '.' << now->tm_year + 1900 << ' ' << now->tm_hour << ':' << now->tm_min << ':' << now->tm_sec << ')' << endl;

	auto start_1{ chrono::steady_clock::now() };
	bool tmp1(UnordTable.is_Ldata(name));
	auto end_1{ chrono::steady_clock::now() };
	chrono::duration<double> es_1 = end_1 - start_1;
	fout << "Unordered table: " << es_1.count() << " sec" << endl;

	auto start_2{ chrono::steady_clock::now() };
	bool tmp2(Hsh_Table.avail(name));
	auto end_2{ chrono::steady_clock::now() };
	chrono::duration<double> es_2 = end_2 - start_2;
	fout << "Hash table: " << es_2.count() << " sec" << endl;

	auto start_3{ chrono::steady_clock::now() };
	bool tmp3(RBT_tree.avail(name));
	auto end_3{ chrono::steady_clock::now() };
	chrono::duration<double> es_3 = end_3 - start_3;
	fout << "Red-black tree: " << es_3.count() << " sec" << endl << endl;

	if (tmp1 != tmp2)
	{
		throw invalid_argument("Hash table and unordered table returned different polynomials");
	}
	if (tmp1 != tmp3)
	{
		throw invalid_argument("Red-Black tree and unordered table returned different polynomials");
	}
	return tmp1;
}

Polynomial TPostfix::count()
{
	double factor;
	Lexeme r_operand;
	Lexeme l_operand;
	ops.clear();
	for (i = 0; i < ind_RPN; i++)
	{															//reuse of TStack <Lexeme> ops as a stack of operands
		switch (Rev_Pol_Notation[i].type_of_lex)
		{
		case 1: {
			switch (*(char*)(Rev_Pol_Notation[i].lex))
			{
			case '+': {
				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else r_operand = ops.pop();

				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else l_operand = ops.pop();

				if (r_operand.type_of_lex == 7 && l_operand.type_of_lex == 7)
				{
					Lexeme tmp(7, (*(double*)l_operand.lex) + (*(double*)r_operand.lex));
					ops.push(move(tmp));
				}
				else if (r_operand.type_of_lex == 8 && l_operand.type_of_lex == 8)
				{
					Lexeme tmp(8, (*(Polynomial*)l_operand.lex) + (*(Polynomial*)r_operand.lex));
					ops.push(move(tmp));
				}
				else
				{
					string except("Invalid arguments input for + in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				break;
			}

			case '-': {
				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else r_operand = ops.pop();

				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else l_operand = ops.pop();

				if (r_operand.type_of_lex == 7 && l_operand.type_of_lex == 7)
				{
					Lexeme tmp(7, (*(double*)l_operand.lex) - (*(double*)r_operand.lex));
					ops.push(move(tmp));
				}
				else if (r_operand.type_of_lex == 8 && l_operand.type_of_lex == 8)
				{
					Lexeme tmp(8, (*(Polynomial*)l_operand.lex) - (*(Polynomial*)r_operand.lex));
					ops.push(move(tmp));
				}
				else
				{
					string except("Invalid arguments input for - in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				break;
			}
			case '*': {
				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else r_operand = ops.pop();

				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else l_operand = ops.pop();

				if (r_operand.type_of_lex == 7 && l_operand.type_of_lex == 7)
				{
					Lexeme tmp(7, (*(double*)l_operand.lex) * (*(double*)r_operand.lex));
					ops.push(move(tmp));
				}
				else if (r_operand.type_of_lex == 8 && l_operand.type_of_lex == 8)
				{
					Lexeme tmp(8, (*(Polynomial*)l_operand.lex) * (*(Polynomial*)r_operand.lex));
					ops.push(move(tmp));
				}
				else if (r_operand.type_of_lex == 7 && l_operand.type_of_lex == 8)
				{
					Lexeme tmp(8, (*(Polynomial*)l_operand.lex).operator*=(*(double*)r_operand.lex));
					ops.push(move(tmp));
				}
				else if (r_operand.type_of_lex == 8 && l_operand.type_of_lex == 7)
				{
					Lexeme tmp(8, (*(Polynomial*)r_operand.lex).operator*=(*(double*)l_operand.lex));
					ops.push(move(tmp));
				}
				else
				{
					string except("Invalid arguments input for * in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}

				break;
			}
			case '/': {
				if (ops.top().type_of_lex != 7)
				{
					string except("Divider must be a number (pos ");
					except += to_string(Rev_Pol_Notation[i].pos);
					except += ")";
					throw invalid_argument(except);
				}
				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else factor = (*(double*)ops.pop().lex);

				if (ops.top().type_of_lex != 7)
				{
					string except("Dividend must be a number (pos ");
					except += to_string(Rev_Pol_Notation[i].pos);
					except += ")";
					throw invalid_argument(except);
				}
				if (abs(factor) == 0)
				{
					string except("Division by zero in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}

				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else (*(double*)ops.top().lex) /= factor;
				break;
			}
			}
			break;
		}
		case 4: {																	//polynomial
			Lexeme tmp(8, search(arr_name_variable[*(size_t*)Rev_Pol_Notation[i].lex]));
			ops.push(move(tmp));
			break;
		}
		case 5: {																	//unary -
			if (ops.isEmpty())
			{
				string except("There asren't enought operands entered for operation in position ");
				except += to_string(Rev_Pol_Notation[i].pos);
				throw invalid_argument(except);
			}
			else if(ops.top().type_of_lex == 7)
				(*(double*)ops.top().lex) *= -1;
			else if (ops.top().type_of_lex == 8)
				(*(Polynomial*)ops.top().lex).operator*=(-1);
			break;
		}
		//case 6: {																	//встречена функция
		//	if (ops.isEmpty())
		//	{
		//		string except("There asren't enought operands entered for operation in position ");
		//		except += to_string(Rev_Pol_Notation[i].pos);
		//		throw invalid_argument(except);
		//	}
		//	else
		//	{
		//		r_operand = (*(double*)ops.top().lex);							//для читаемости
		//		if (*(int*)(Rev_Pol_Notation[i].lex) == 1)
		//			(*(double*)ops.top().lex) = sin(r_operand);

		//		else if (*(int*)(Rev_Pol_Notation[i].lex) == 2)
		//			(*(double*)ops.top().lex) = cos(r_operand);

		//		else if (*(int*)(Rev_Pol_Notation[i].lex) == 3)
		//			(*(double*)ops.top().lex) = tan(r_operand);

		//		else if (*(int*)(Rev_Pol_Notation[i].lex) == 4)
		//			(*(double*)ops.top().lex) = exp(r_operand);

		//		else if (*(int*)(Rev_Pol_Notation[i].lex) == 5)
		//			if (r_operand > 0)
		//				(*(double*)ops.top().lex) = log(r_operand);
		//			else {
		//				string except("Invalid argument for ln in position ");
		//				except += to_string(Rev_Pol_Notation[i].pos);
		//				throw invalid_argument(except);
		//			}
		//	}
		//	break;
		case 7: {//number
			Lexeme tmp = Rev_Pol_Notation[i];
			ops.push(move(tmp));
			break;
		}
		}
	}

	Polynomial res = *(Polynomial*)ops.pop().lex;

	if (ops.isEmpty())
		return res;
	else throw invalid_argument("There are extra operands with no operations in line");
}