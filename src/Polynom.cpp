#include "Polynom.h"
#include <iostream>

const double eps = std::pow(10, -10);

const int max_deg = 10;

std::string Polynom::Error_string(const std::string& s, int i) const {
	std::string tmp = "Error: ";
	if (i != s.size()) {
		for (int j = 0; j < i; j++) tmp += s[j];
		tmp = tmp + '\"' + s[i] + '\"';
		for (int j = i + 1; j < s.size(); j++) tmp += s[j];
		tmp += '\n';
	}
	else tmp = tmp + s + "\" \"\n";
	return tmp;
};

std::string Polynom::number_check(const std::string& s, int& i) const {
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
	i--;
	return tmp;
};

double Polynom::valid(const std::string& s) const {
	double res = 0;
	int i = 0, sign = 0, pw = 0;
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
		if (s[i] == '-') sign = -1;
		else sign = 1;
		i++;
	};
	while (i != s.size()) {
		pw *= 10;
		pw += (int)s[i++] - 48;
	}
	res *= pow(10, sign * pw);
	return res;
};

int Polynom::count_deg(const std::string& s, int& i) const {
	int res = 0, num, deg;
	while (s[i] == 'x' || s[i] == 'y' || s[i] == 'z') {
		switch (s[i])
		{
		case ('x'): num = max_deg*max_deg;
			break;
		case ('y'): num = max_deg;
			break;
		case('z'): num = 1;
		}
		i++;
		if (s[i] != '^') deg = 1;
		else {
			i++;
			if (s[i] >= '0' && s[i] <= '9') deg = (int)s[i] - 48;
			else throw std::invalid_argument(Error_string(s, i) + "Deg of each monom can be only a {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}");
			i++;
		}
		if (res % (num * max_deg) - res % num + deg * num < num * max_deg) res += deg * num;
		else throw std::invalid_argument("Deg of each variable can't be greater than 9");
	}
	if (s[i] >= '0' && s[i] <= '9' && s[i - 1] >= '0' && s[i - 1] <= '9')
		throw std::invalid_argument(Error_string(s, i) + "Deg of each monom can be only a {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}");
	if (i < s.size() && (s[i] != '+' && s[i] != '-')) throw std::invalid_argument(Error_string(s, i) + "This writing is not correct");
	i--;
	return res;
};

Polynom::Polynom() {
	add_head(); //dummy head (for convenience)
};

Polynom::Polynom(const Polynom& p) {
	add_head();
	Node* tmp1 = head, * tmp2 = p.head->next;
	while (tmp2) {
		add(tmp1, tmp2->data);
		tmp2 = tmp2->next;
		tmp1 = tmp1->next;
	}
};

Polynom::Polynom(const std::string& str) {
	add_head();
	std::string s;
	std::pair<double, int> tmp;
	int sign = 1;
	for (int i = 0; i < str.size(); i++) if (str[i] != ' ') s += str[i];
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '-') {
			sign = -1;
			i++;
		}
		else if (s[i] == '+') {
			if (i == 0) throw std::invalid_argument(Error_string(s, i) + "String can't be started from \'+\'");
			sign = 1;
			i++;
		}
		if ((s[i] >= '0' && s[i] <= '9')) {
			if (s[i]== '0' && s[i + 1] >= '0' && s[i + 1] <= '9') throw std::invalid_argument(Error_string(s, i) + "A number cannot start with an insignificant \'0\'");
			tmp.first = sign * valid(number_check(s, i));
			i++;
			if (s[i] == 'x' || s[i] == 'y' || s[i] == 'z') tmp.second = count_deg(s, i);
			else {
				tmp.second = 0;
				i--;
			}
		}
		else if (s[i] == 'x' || s[i] == 'y' || s[i] == 'z') {
			tmp.first = sign;
			tmp.second = count_deg(s, i);
		}
		else throw std::invalid_argument(Error_string(s, i) + "This writing is not correct");
		if (abs(tmp.first) < eps) continue;
		Node* this_ = head;
		while (this_->next && this_->next->data.second > tmp.second) this_ = this_->next; //Looking for the right place for monom
		if (this_->next != nullptr && this_->next->data.second == tmp.second) 
			if (abs(this_->next->data.first + tmp.first) > eps) this_->next->data.first += tmp.first; else del(this_);
		else add(this_, tmp); 
	};
};

Polynom::Polynom(const double& a) {
	add_head();
	add(head, std::pair<double, int>(a, 0));
}

bool Polynom::operator==(const Polynom& p) const noexcept {
	return (this->List<std::pair<double, int>>::operator==(p));
}

bool Polynom::operator!=(const Polynom& p) const noexcept {
	return !(*this == p);
}

Polynom Polynom::operator+ (const Polynom& p) const {
	Polynom res;
	Node* tmp1 = head->next, * tmp2 = p.head->next, * tmp3 = res.head;
	while (tmp1 || tmp2) {
		if (tmp1 != nullptr && (tmp2 == nullptr || tmp1->data.second > tmp2->data.second)) {
			res.add(tmp3, tmp1->data);
			tmp1 = tmp1->next;
			tmp3 = tmp3->next;
		}
		else if ((tmp1 != nullptr && tmp2 != nullptr) && tmp1->data.second == tmp2->data.second) {
				if (abs(tmp1->data.first + tmp2->data.first) >= eps) {   //don't save the value if it is 0
					res.add(tmp3, std::pair<double, int>(tmp1->data.first + tmp2->data.first, tmp1->data.second));
					tmp3 = tmp3->next;
				}
				tmp1 = tmp1->next;
				tmp2 = tmp2->next;
		} else {
			res.add(tmp3, tmp2->data);
			tmp2 = tmp2->next;
			tmp3 = tmp3->next;
		}
	}
	return res;
};

Polynom Polynom::operator+(const double& a) const {
	Polynom res(*this), tmp;
	tmp.add(tmp.head, std::pair<double, int>(a, 0));
	return res + tmp;
};

Polynom Polynom::operator*(const Polynom& p) const {
	Node* tmp = head->next;
	Polynom p_res;
	int n=0;
	while (tmp) {
		tmp = tmp->next;
		n++;
	};
	if (n != 0) {
		tmp = head->next;
		Polynom* res = new Polynom[n]{};
		for (int i = 0; i < n; i++, tmp = tmp->next) {
			res[i] = p * tmp->data.first;
			Node* tmp2 = res[i].head->next;
			while (tmp2) {
				if (tmp->data.second % max_deg + tmp2->data.second % max_deg < max_deg &&
					(tmp->data.second / max_deg) % max_deg + (tmp2->data.second / max_deg) % max_deg < max_deg &&
					tmp->data.second / (max_deg * max_deg) + tmp2->data.second / (max_deg * max_deg) < max_deg)
					tmp2->data.second += tmp->data.second;
				else throw std::invalid_argument("The sum of the powers of monomes when multiplying polynomials should not be greater than 9");
				tmp2 = tmp2->next;
			}
		}
		for (int i = 2; i < 2 * n; i *= 2)
			for (int j = 0; j < n - i / 2; j += i)
				res[j] = res[j] + res[j + i / 2];
		p_res = res[0];
		delete[] res;
	}
	return p_res;
}

Polynom Polynom::operator* (const double& a) const {
	Polynom res;
	if (abs(a) < eps) return res;
	Node* tmp1 = head->next, * tmp2 = res.head;
	while (tmp1) {
		if (abs(a* tmp1->data.first) >= eps) res.add(tmp2, std::pair<double, int>(tmp1->data.first * a, tmp1->data.second));
		tmp2 = tmp2->next;
		tmp1 = tmp1->next;
	}
	return res;
};

Polynom Polynom::operator- (const Polynom& p) const {
	return Polynom(*this + p * (-1));
};

Polynom Polynom::operator- (const double& a) const {
	return Polynom(*this + (-a));
};

double Polynom::Pol_to_double() const {
	if (head->next && head->next->data.second != 0) throw std::invalid_argument("This polynom cannot be turned into a number");
	if (head->next) return head->next->data.first;
	return 0;
};

std::ostream& operator<<(std::ostream& ostr, const Polynom& p) {
	List<std::pair<double, int>>::Node* tmp = p.head->next;
	if (tmp == nullptr) ostr << 0;
	while (tmp)
	{
		std::pair< double, int > pr = tmp->data;
		if (abs(pr.first - 1) < eps && pr.second != 0) {} //if coefficient is equal to 1 or -1, don't write it
		else if (abs(pr.first + 1) < eps && pr.second != 0) ostr << "-";
		else ostr << pr.first;
		if (pr.second / (max_deg * max_deg) != 0) {
			if (pr.second / (max_deg * max_deg) == 1) ostr << "x";
			else ostr << "x^" << pr.second / (max_deg * max_deg);
		}
		if ((pr.second/max_deg)%max_deg != 0) {
			if ((pr.second / max_deg) % max_deg == 1) ostr << "y";
			else ostr << "y^" << (pr.second / max_deg) % max_deg;
		}
		if (pr.second % max_deg != 0) {
			if (pr.second % max_deg == 1) ostr << "z";
			else ostr << "z^" << pr.second % max_deg;
		}
		tmp = tmp->next;
		if (tmp && tmp->data.first > 0) ostr << "+";
	}
	return ostr;
};

std::istream& operator>>(std::istream& istr, Polynom& p) {
	std::string str;
	istr >> str;
	Polynom pol(str);
	p = pol;
	return istr;
};