// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"
#include "stack.h"
#include <iostream>

std::string TPostfix::Error_string(const std::string& s, int i) {
	std::string tmp = "Error: ";
	if (i != s.size()) {
		for (int j = 0; j < i; j++) tmp += s[j];
		tmp = tmp + '\"' + s[i] + '\"';
		for (int j = i + 1; j < s.size(); j++) tmp += s[j];
		tmp += '\n';
	}
	else tmp = tmp + s + "\" \"\n";
	return tmp;
}

int TPostfix::get_prior(const std::string& s) noexcept {
	if (s == "+" || s == "-") return 1;
	if (s == "*" || s == "/") return 2;
	if (s == "~" || s == "sin" || s == "cos" || s == "tan" || s == "cot" || s == "exp" || s == "log") return 3;
	return 0;
}

int TPostfix::get_prior(char c) noexcept {
	if (c == '+' || c == '-') return 1;
	if (c == '*' || c == '/') return 2;
	if (c == '~') return 3;
	return 0;
}

double TPostfix::valid(const std::string& s) {
	double res = 0;
	int i = 0, mod = 0, pw = 0;
	while ((i != s.size()) && (s[i] != '.') && (s[i] != 'e')) {
		res *= 10;
		res += (int)s[i++] - 48;
	}
	int m = i;
	if (s[i] == '.') i++;
	while ((s[i] != 'e') && (i != s.size())) {
		res += ((int)s[i] - 48) * pow(10, m - i);
		i++;
	}
	if (s[i] == 'e') {
		i++;
		if (s[i] == '-') mod = -1;
		else mod = 1;
		i++;
	};
	while (i != s.size()) {
		pw *= 10;
		pw += (int)s[i++] - 48;
	}
	res *= pow(10, mod * pw);
	return res;
}
std::string TPostfix::number_check(const std::string& s, int& i) {
	std::string tmp;
	tmp = s[i++];
	while (i != s.size() && (s[i] >= '0' && s[i] <= '9')) tmp += s[i++];
	if (s[i] == '.') tmp += s[i++];
	while (i != s.size() && s[i] >= '0' && s[i] <= '9') tmp += s[i++];
	if (tmp == ".") throw std::invalid_argument(Error_string(s, i - 1) + "Writing a number in the form of \".\" is not possible");
	if (i != s.size() && s[i] == 'e') {
		tmp += s[i++];
		if ((i < s.size() - 1) && (s[i] == '+' || s[i] == '-')) {
			tmp += s[i++];
			if (s[i] < '1' || s[i]>'9')
				throw std::invalid_argument(Error_string(s, i) + "When specifying a number with \'e\', there must be a natural number after the \'+\' or \'-\' sign");
			tmp += s[i++];
		}
		else throw std::invalid_argument(Error_string(s, i) + "After \'e\' there should be a \'+\' or \'-\'");
	};
	while (i != s.size() && (s[i] >= '0' && s[i] <= '9')) tmp += s[i++];
	if (i != s.size() && !get_prior(s[i]) && s[i] != ')') throw std::invalid_argument(Error_string(s, i) + "The operand must be followed by an operator or a closing parenthesis");
	i--;
	return tmp;
}
TPostfix::TPostfix(const std::string& str) {
	int i = 0;
	std::string tmp, s;
	for (int j = 0; j < str.size(); j++) if (str[j] != ' ') s += str[j];
	if (s.size() == 0) throw std::invalid_argument("Nothing can be done with an empty string");
	TStack<std::string> St;
	TStack<int> bracket; //This stack is needed to indicate the first incorrectly plcaed bracket
	while (i < s.size()) {
		tmp = s[i];
		if (get_prior(s[i])) { //Work with operators
			if ( i == 0 || s[i - 1] == '(' || get_prior(s[i - 1])) {
				if (tmp == "-") tmp = "~";
				else throw std::invalid_argument(Error_string(s, i) + "Binary operators must be preceded by a closing bracket or an operand");
			}
			if (i == s.size() - 1 || s[i + 1] == ')') throw std::invalid_argument(Error_string(s, i+1) + "The operator must be followed by an operand or unary minus");
			while (!St.isEmpty() && St.top() != "("  && get_prior(tmp) != 3 && get_prior(St.top()) >= get_prior(tmp)) RPN.push_back(St.pop_back());
			St.push_back(tmp);
		}
		else if (s[i] == '(' && i < s.size() - 1 && s[i + 1] != ')') { //Work with opening bracket
			bracket.push_back(i);
			St.push_back(tmp);
		}
		else if (s[i] == ')') { //Work with closing bracket
			if (bracket.GetCount() == 0) throw std::invalid_argument(Error_string(s, i) + "The brackets are placed incorrectly");
			bracket.pop_back();
			if (i != s.size() - 1 && !get_prior(s[i + 1]) && s[i + 1] != ')') throw std::invalid_argument(Error_string(s, i + 1) + "The operand must be followed by an operator or a closing bracket");
			while (St.top() != "(") RPN.push_back(St.pop_back());
			St.pop_back();
		}
		else if (i < s.size() - 2 && s.size()>2 && get_prior(tmp + s[i + 1] + s[i + 2]) && 
				(s[i+3]< 'A' || s[i+3]>'Z') && (s[i + 3] < 'a' || s[i + 3]>'z') && (s[i + 3] < '0' || s[i + 3]>'9')) { //Work with functions
			if (i > s.size() - 4 || s.size() < 4 || s[i + 3] != '(') throw std::invalid_argument(Error_string(s, i + 3) + "After a function must be a \'(\'");
			tmp = tmp + s[i + 1] + s[i + 2];
			i += 2;
			St.push_back(tmp);
		}
		else if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') { //Work with numbers
			if (s[i] == '0'&& s[i+1] >= '0' && s[i+1] <= '9') throw std::invalid_argument(Error_string(s, i) + "A number cannot start with an insignificant \'0\'");
			RPN.push_back(number_check(s, i));
		}
		else if ((s[i] >= 'A' && s[i + 3]<='Z') || (s[i] >= 'a' && s[i + 3]<='z')) { //Work with polynomial names
			i++;
			while (i != s.size() && ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))) {
				tmp += s[i];
				i++;
			};
			while (i != s.size() && (s[i] >= '0' && s[i] <= '9')) {
				tmp += s[i];
				i++;
			};
			if (i != s.size() && !get_prior(s[i]) && s[i] != ')') throw std::invalid_argument(Error_string(s, i) + "You can't name polynomials this way");
			i--;
			RPN.push_back(tmp);
		}
		else throw std::invalid_argument(Error_string(s, i) + "This writing is not correct");
		i++;
	}
	if (bracket.GetCount() != 0) {
		if (bracket.GetCount() > 1) while (bracket.GetCount() != 1) bracket.pop_back();
		throw std::invalid_argument(Error_string(s, bracket.pop_back()) + "The brackets are placed incorrectly");
	}
	while (!St.isEmpty()) RPN.push_back(St.pop_back());
}

Polynom TPostfix::count(const UnorderedTable<std::string, Polynom>& T1,
					   const OrderedTable<std::string, Polynom>& T2,
					   const HashTable& T3) {
	TStack<Polynom> St;
	int j = 0;
	for (int i = 0; i < RPN.size(); i++) {
		if (get_prior(RPN[i])) {
			if (RPN[i] == "+") St.push_back(St.pop_back() + St.pop_back());
			else if (RPN[i] == "-") St.push_back(St.pop_back() * (-1) + St.pop_back());
			else if (RPN[i] == "*") St.push_back(St.pop_back() * St.pop_back());
			else if (RPN[i] == "/") St.push_back(Polynom(1 / St.pop_back().Pol_to_double()) * St.pop_back());
			else if (RPN[i] == "~") St.top() = St.top() * (-1);
			else if (RPN[i] == "sin") St.push_back(sin(St.pop_back().Pol_to_double()));
			else if (RPN[i] == "cos") St.push_back(cos(St.pop_back().Pol_to_double()));
			else if (RPN[i] == "tan") St.push_back(tan(St.pop_back().Pol_to_double()));
			else if (RPN[i] == "cot") St.push_back((1 / tan(St.pop_back().Pol_to_double())));
			else if (RPN[i] == "exp") St.push_back(exp(St.pop_back().Pol_to_double()));
			else St.push_back(log(St.pop_back().Pol_to_double()));
		}
		else { 
			if (RPN[i][0] < '0' || RPN[i][0]> '9') {
				T1.find(RPN[i]);
				T2.find(RPN[i]);
				St.push_back(T3.find(RPN[i]));
			}
			else St.push_back(valid(RPN[i]));
		}
	}
	return St.pop_back();
}