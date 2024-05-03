// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.hpp"

double calculate_expr(const string &expr, istream& values_stream) {
	TPostfix<double> postfix;
	vector<string> lexems = arithmetic_to_lexems(expr);
	postfix.toPostfix(lexems);
	postfix.askOperands(values_stream);
	double res;
	res = postfix.calculate();
	return res;
}

double string_to_decimal(const string &expr) {
	double res = 0.0;
	if (expr.size() == 0) {
		return res;
	}
	for (size_t i = expr.size() - 1; i > 0; i--) {
		res += static_cast<double>(expr[i]) - static_cast<double>('0');
		res /= 10;
	}
	if (expr[0] == '-') {
		res *= -1;
	}
	else {
		res += static_cast<double>(expr[0]) - static_cast<double>('0');
		res /= 10;
	}
	return res;
}

int string_to_integer(const string &expr) {
	int res = 0;
	bool minus = false;
	if (expr.size() == 0) {
		return res;
	}
	size_t i = 0;
	if (expr[0] == '-') {
		minus = true;
		i++;
	}
	while (i < expr.size()) {
		res *= 10;
		res += static_cast<int>(expr[i]) - static_cast<int>('0');
		i++;
	}
	if (minus) {
		res *= -1;
	}
	return res;
}

double exp_form_to_double(const string &expr) {
	// init state machine matrix
	const size_t a_size = 6;
	const size_t s_size = 10;
	const size_t a0[a_size] = { 0, 0, 0, 0, 0, 0 };
	const size_t a1[a_size] = { 4, 3, 2, 6, 0, 0 };
	const size_t a2[a_size] = { 4, 3, 0, 6, 0, 0 };
	const size_t a3[a_size] = { 3, 3, 0, 5, 7, 0 };
	const size_t a4[a_size] = { 0, 0, 0, 5, 7, 0 };
	const size_t a5[a_size] = { 5, 5, 0, 0, 7, 0 };
	const size_t a6[a_size] = { 5, 5, 0, 0, 0, 0 };
	const size_t a7[a_size] = { 0, 0, 8, 0, 0, 8 };
	const size_t a8[a_size] = { 9, 9, 0, 0, 0, 0 };
	const size_t a9[a_size] = { 9, 9, 0, 0, 0, 0 };
	const size_t *states_array[s_size] = { a0, a1, a2, a3, a4, a5, a6, a7, a8, a9 };
	// get 3 nums
	string first_num = "";
	string mov = "";
	string second_num = "";
	size_t cur_state = 1;
	size_t cur_slot = 0;
	char item;
	for (size_t i = 0; i < expr.size(); i++) {
		// move state
		item = expr[i];
		if (item == '0') { cur_state = states_array[cur_state][0]; }
		else if (item >= '1' && item <= '9') { cur_state = states_array[cur_state][1]; }
		else if (item == '-') { cur_state = states_array[cur_state][2]; }
		else if (item == '.') { cur_state = states_array[cur_state][3]; }
		else if (item == 'e') { cur_state = states_array[cur_state][4]; }
		else if (item == '+') { cur_state = states_array[cur_state][5]; }
		else {
			//throw std::invalid_argument("Bad number");
			continue;
		}
		if (cur_state == 0) {
			break;
		}
		if (item == '.') {
			cur_slot = 1;
		}
		else if (item == 'e') {
			cur_slot = 2;
		}
		else if (item == '-' || (item >= '0' && item <= '9')) {
			// add to corresponding num
			switch (cur_slot) {
			case 0:
				first_num += item;
				break;
			case 1:
				second_num += item;
				break;
			case 2:
				mov += item;
				break;
			}
		}
	}
	// find result
	double res;
	res = string_to_integer(first_num) + string_to_decimal(second_num);
	res *= std::pow(10, string_to_integer(mov));
	return res;
}

size_t operator_priority(const string &expr) {
	if (expr == "+") { return 1; }
	else if (expr == "-") { return 1; }
	else if (expr == "*") { return 2; }
	else if (expr == "/") { return 2; }
	else if (expr == "~") { return 2; }
	else if (expr == "sin") { return 3; }
	else if (expr == "cos") { return 3; }
	else if (expr == "tan") { return 3; }
	else if (expr == "exp") { return 3; }
	else if (expr == "lg") { return 3; }
	else { return 0; }
}

vector<string> arithmetic_to_lexems(const string &expr) {
	vector<string> res;
	string buf = "";
	char item;
	// when +,- is part of number
	bool expcase;
	for (size_t i = 0; i < expr.size(); i++) {
		item = expr[i];
		expcase = ((i > 0) && (item == '+' || item == '-') && (expr[i - 1] == 'e'));
		if (is_arithmetical(item) && !expcase) {
			if (buf != "") {
				res.push_back(buf);
				buf = "";
			}
			if (item == '-' && ((i == 0) || (expr[i-1] == '('))) {
				buf += '~';
			}
			else {
				buf += item;
			}
			res.push_back(buf);
			buf = "";
		}
		else if (is_alphabet_or_numeric(item) || expcase) {
			buf += item;
		}
	}
	if (buf != "") {
		res.push_back(buf);
	}
	return res;
}

bool check_infix_correctness(const vector<string> &lexems) {
	// init state machine matrix
	const size_t a_size = 6;
	const size_t s_size = 7;
	const size_t a0[a_size] = { 0, 0, 0, 0, 0, 0 };
	const size_t a1[a_size] = { 0, 1, 2, 4, 0, 3 };
	const size_t a2[a_size] = { 6, 0, 0, 0, 5, 0 };
	const size_t a3[a_size] = { 0, 1, 2, 4, 0, 0 };
	const size_t a4[a_size] = { 0, 1, 0, 0, 0, 0 };
	const size_t a5[a_size] = { 6, 0, 0, 0, 5, 0 };
	const size_t a6[a_size] = { 0, 1, 2, 4, 0, 0 };
	const size_t *states_array[s_size] = { a0, a1, a2, a3, a4, a5, a6 };
	// check
	string lexem;
	size_t cur_state = 1;
	for (size_t i = 0; i < lexems.size(); i++) {
		// move state
		lexem = lexems[i];
		if ((operator_priority(lexem) == 1 || operator_priority(lexem) == 2) && lexem != "~") { cur_state = states_array[cur_state][0]; }
		else if (lexem == "(") { cur_state = states_array[cur_state][1]; }
		else if (operator_priority(lexem) == 3) { cur_state = states_array[cur_state][3]; }
		else if (lexem == ")") { cur_state = states_array[cur_state][4]; }
		else if (lexem == "~") { cur_state = states_array[cur_state][5]; }
		else { cur_state = states_array[cur_state][2]; }
		if (cur_state == 0) {
			return false;
		}
	}
	if (cur_state == 2 || cur_state == 5) {
		return true;
	}
	else {
		return false;
	}
}

template<>
void TPostfix<Polynom>::askOperands(istream& from, ostream& log) {
	bool is_monom;
	bool is_numeric;
	char elem;
	char degs[3];
	string buf_to_ignore;
	// ask operands
	for (auto it = operands.begin(); it != operands.end(); it++) {
		degs[0] = 0; degs[1] = 0; degs[2] = 0;
		is_monom = true;
		is_numeric = true;
		for (size_t i = 0; i < it->first.size(); i++) {
			elem = it->first[i];
			if ((elem < '0' || elem > '9') && elem != '.' && elem != 'e' && elem != '+' && elem != '-') {
				is_numeric = false;
			}
		}
		if (is_numeric) {
			it->second = Monom(1, degs) * exp_form_to_double(it->first);
		}
		else {
			if (it->first.size() == 1) {
				if (it->first[0] >= 'x' && it->first[0] <= 'z') {
					degs[it->first[0] - 'x'] = 1;
				}
				else {
					is_monom = false;
				}
			}
			else if (it->first.size() == 3) {
				if (it->first[0] >= 'x' && it->first[0] <= 'z' && it->first[1] == '^' && it->first[2] >= '0' && it->first[2] <= '9') {
					degs[it->first[0] - 'x'] = it->first[2] - '0';
				}
				else {
					is_monom = false;
				}
			}
			else {
				is_monom = false;
			}
			if (is_monom) {
				it->second = Polynom(Monom(1, degs));
			}
			else {
				log << "\"" << it->first << "\": ";
				it->second = fill_polynom();
				//from.clear();
				//getline(from, buf_to_ignore);
			}
		}
	}
}

template<>
Polynom TPostfix<Polynom>::calculate() {
	if (postfix_lexems.size() == 0) {
		throw exception("Postfix: No expression to solve");
	}
	TStack<Polynom> vars;
	Polynom arg1;
	Polynom arg2;
	for (size_t i = 0; i < postfix_lexems.size(); i++) {
		if (postfix_lexems[i] == "+") {
			arg1 = vars.pop(); arg2 = vars.pop();
			vars.push(arg2 + arg1);
		}
		else if (postfix_lexems[i] == "-") {
			arg1 = vars.pop(); arg2 = vars.pop();
			vars.push(arg2 - arg1);
		}
		else if (postfix_lexems[i] == "*") {
			arg1 = vars.pop(); arg2 = vars.pop();
			vars.push(arg2 * arg1);
		}
		else if (postfix_lexems[i] == "~") {
			arg1 = vars.pop();
			vars.push(arg1 * (-1));
		}
		else {
			vars.push(operands[postfix_lexems[i]]);
		}
	}
	return vars.pop();
}
