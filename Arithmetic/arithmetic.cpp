// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"

TPostfix::TPostfix(string& t, bool need_to_check) {
	cap_RPN = 10;
	Rev_Pol_Notation = new Lexeme[cap_RPN]();

	cap_variable = 3;
	arr_num_variable = new int[cap_variable]();

	string inp;
	if (need_to_check)
	{
		for (i = 0; i < t.length(); i++)
			if (t[i] != ' ') inp.push_back(t[i]);
		i = 0;
	}
	else inp = t;

	size_t quan_open_braсkets = 0;

	while (i < inp.length())
	{
		switch (inp[i])
		{
		case '+': { Lexeme tmp(1, '+', i);

			while (!ops.isEmpty() && (ops.top().type_of_lex == 6 ||
				ops.top().type_of_lex == 5 ||
				(ops.top().type_of_lex == 1)))
				insert_result(ops.pop());

			ops.push(move(tmp));

			break;
		}

		case '*': { Lexeme tmp(1, '*', i);

			while (!ops.isEmpty() && (ops.top().type_of_lex == 6 ||
				ops.top().type_of_lex == 5 ||
				(ops.top().type_of_lex == 1 &&
					(*(char*)ops.top().lex == '/' || *(char*)ops.top().lex == '*'))))
				insert_result(ops.pop());

			ops.push(move(tmp));

			break;
		}

		case '/': { Lexeme tmp(1, '/', i);

			while (!ops.isEmpty() && (ops.top().type_of_lex == 6 ||
				ops.top().type_of_lex == 5 ||(
				ops.top().type_of_lex == 1 && *(char*)ops.top().lex == '/')))
				insert_result(ops.pop());

			ops.push(move(tmp));

			break;
		}

		case '(': {
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
			break;
		}

		case ')': {
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
			break;
		}

		case '-': {
			if (i == 0 || inp[i - 1] == '+' || inp[i - 1] == '*' ||
				inp[i - 1] == '/' || inp[i - 1] == '-' || inp[i - 1] == '(') //если это унарный минус, то
			{
				if ((inp[i + 1] <= '9' && inp[i + 1] >= '0') ||
					inp[i + 1] == '.' || inp[i + 1] == ',' || inp[i + 1] == 'x' ||
					inp[i + 1] == 'X' || inp[i + 1] == '-' || inp[i + 1] == '(' ||
					inp[i + 1] == 'e' || inp[i + 1] == 'c' || inp[i + 1] == 's' ||
					inp[i + 1] == 'l' || inp[i + 1] == 't') //если за минусом следует операнд или ещё один минус
				{
					Lexeme tmp(5, '-', i); //определи его унарным минусом
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
			{//иначе определи его бинарным
				Lexeme tmp(1, '-', i);

				while (!ops.isEmpty() && (ops.top().type_of_lex == 6 ||
					ops.top().type_of_lex == 5 ||
					ops.top().type_of_lex == 1 &&
						( *(char*)ops.top().lex == '*' || *(char*)ops.top().lex == '-' || *(char*)ops.top().lex == '/')))
					insert_result(ops.pop());

				ops.push(move(tmp));
			}
			break;
		}

		case 'x': {//если введена переменная

			int res = 0;
			i++;
			while (i < inp.length() && inp[i] <= '9' && inp[i] >= '0')
			{
				res *= 10;
				res += inp[i] - '0';	//скопируй её имя во временную вспомогательную переменную.
				i++;
			}

			i--;

			size_t j = 0;
			while (j < ind_variable && arr_num_variable[j] != res)
				j++;

			if (j == ind_variable)//если такая переменная ещё не встречалась ранее
				insert_variable(res); //добавь её в массив имён переменных,

			Lexeme tmp(4, j); //в соответствующую ей лексему в ОПЗ положи индекс этой переменной в массиве

			insert_result(tmp);

			break;
		}

		case 's':
		{
			if (inp[i + 1] == 'i' && inp[i + 2] == 'n')
			{
				Lexeme tmp_func(6, 1, i);
				ops.push(move(tmp_func));

				i += 2;
			}
			else {
				string except("Incorrect function input at position ");
				except += to_string(i);
				throw invalid_argument(except);
			}
			break;
		}

		case 'c':
		{
			if (inp[i + 1] == 'o' && inp[i + 2] == 's')
			{
				Lexeme tmp_func(6, 2, i);
				ops.push(move(tmp_func));

				i += 2;
			}
			else {
				string except("Incorrect function input at position ");
				except += to_string(i);
				throw invalid_argument(except);
			}
			break;
		}

		case 't':
		{
			if (inp[i + 1] == 'a' && inp[i + 2] == 'n')
			{
				Lexeme tmp_func(6, 3, i);
				ops.push(move(tmp_func));

				i += 2;
			}
			else {
				string except("Incorrect tan input at position ");
				except += to_string(i);
				throw invalid_argument(except);
			}
			break;
		}

		case 'e':
		{
			if (inp[i + 1] == 'x' && inp[i + 2] == 'p')
			{
				Lexeme tmp_func(6, 4, i);
				ops.push(move(tmp_func));

				i += 2;
			}
			else {
				string except("Incorrect function input at position ");
				except += to_string(i);
				throw invalid_argument(except);
			}
			break;
		}

		case 'l':
		{
			if (inp[i + 1] == 'n')
			{
				Lexeme tmp_func(6, 5, i);
				ops.push(move(tmp_func));

				i++;
			}
			else {
				string except("Incorrect function input at position ");
				except += to_string(i);
				throw invalid_argument(except);
			}
			break;
		}
		default: {
			if ((inp[i] >= '0' && inp[i] <= '9') || inp[i] == '.' || inp[i] == ',') //ввод числа
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
		}
		i++;
	}
	if (quan_open_braсkets != 0)
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
	arr_value_variable = new double[ind_variable];
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

void TPostfix::insert_variable(int xi)
{
	if (ind_variable == cap_variable)
	{
		int* tmp = new int[cap_variable *= 2];
		copy(arr_num_variable + 0, arr_num_variable + ind_variable, tmp);
		delete[]arr_num_variable;
		arr_num_variable = tmp;
	}
	arr_num_variable[ind_variable++] = xi;
}

void TPostfix::asker()
{
	if (ind_variable > 0)
	{
		cout << arr_num_variable[0];

		for (size_t j = 1; j < ind_variable; j++)
			cout << ", x" << arr_num_variable[j];
		cout << endl;

		for (size_t j = 0; j < ind_variable; j++)
			cin >> arr_value_variable[j];
	}
}

void TPostfix::input_variables(double* arr, size_t quan)
{
	if (quan != ind_variable) throw("Quanity of variables inserted and quanity of variables in input line doesn't match");
	for (size_t j = 0; j < ind_variable; j++)
		arr_value_variable[j] = arr[j];
}

size_t TPostfix::Get_ind_variable()
{
	return ind_variable;
}

double TPostfix::count()
{
	double r_operand;
	ops.clear();
	for (i = 0; i < ind_RPN; i++)
	{															//переиспользуем TStack <Lexeme> ops - теперь это stack операндов
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
				else r_operand = (*(double*)ops.pop().lex);

				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else (*(double*)ops.top().lex) += r_operand;
				break;
			}

			case '-': {
				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else r_operand = (*(double*)ops.pop().lex);

				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else (*(double*)ops.top().lex) -= r_operand;
				break;
			}
			case '*': {
				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else r_operand = (*(double*)ops.pop().lex);

				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else (*(double*)ops.top().lex) *= r_operand;
				break;
			}
			case '/': {
				if (ops.isEmpty())
				{
					string except("There asren't enought operands entered for operation in position ");
					except += to_string(Rev_Pol_Notation[i].pos);
					throw invalid_argument(except);
				}
				else r_operand = (*(double*)ops.pop().lex);

				if (abs(r_operand) < 1e-10)
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
				else (*(double*)ops.top().lex) /= r_operand;
				break;
			}
			}
			break;
		}
		case 4: {																	//встречена переменная
			Lexeme tmp(7, arr_value_variable[*(size_t*)Rev_Pol_Notation[i].lex]);
			ops.push(move(tmp));
			break;
		}
		case 5: {																	//встречен унарный -
			if (ops.isEmpty())
			{
				string except("There asren't enought operands entered for operation in position ");
				except += to_string(Rev_Pol_Notation[i].pos);
				throw invalid_argument(except);
			}
			else
				(*(double*)ops.top().lex) *= -1;
			break;
		}
		case 6: {																	//встречена функция
			if (ops.isEmpty())
			{
				string except("There asren't enought operands entered for operation in position ");
				except += to_string(Rev_Pol_Notation[i].pos);
				throw invalid_argument(except);
			}
			else
			{
				r_operand = (*(double*)ops.top().lex);							//для читаемости
				if (*(int*)(Rev_Pol_Notation[i].lex) == 1)
					(*(double*)ops.top().lex) = sin(r_operand);

				else if (*(int*)(Rev_Pol_Notation[i].lex) == 2)
					(*(double*)ops.top().lex) = cos(r_operand);

				else if (*(int*)(Rev_Pol_Notation[i].lex) == 3)
					(*(double*)ops.top().lex) = tan(r_operand);

				else if (*(int*)(Rev_Pol_Notation[i].lex) == 4)
					(*(double*)ops.top().lex) = exp(r_operand);

				else if (*(int*)(Rev_Pol_Notation[i].lex) == 5)
					if (r_operand > 0)
						(*(double*)ops.top().lex) = log(r_operand);
					else {
						string except("Invalid argument for ln in position ");
						except += to_string(Rev_Pol_Notation[i].pos);
						throw invalid_argument(except);
					}
			}
			break;
		case 7: {//встречено число
			Lexeme tmp = Rev_Pol_Notation[i];
			ops.push(move(tmp));
			break;
		}
		}
		}
	}

	double res = *(double*)ops.pop().lex;

	if (ops.isEmpty())
		return res;
	else throw invalid_argument("There are extra operands with no operations in line");
}