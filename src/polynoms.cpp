#include "polynoms.hpp"

Polynom fill_polynom() {
	size_t amount;
	double tmpcoef;
	char tmpdeg[VARS];
	Monom tmpmonom;
	List<Monom> monoms;
	std::cout << "Enter amount of monoms: ";
	get_var(amount);
	for (size_t i = 0; i < amount; i++) {
		std::cout << "Enter coefficient: ";
		get_var(tmpcoef);
		for (size_t i = 0; i < VARS; i++) {
			std::cout << "Enter " << i + 1 << " degree (0-9): ";
			get_var(tmpdeg[i]);
			tmpdeg[i] -= '0';
		}
		try {
			tmpmonom = Monom(tmpcoef, tmpdeg);
		}
		catch (const std::exception &e) {
			std::cout << e.what() << std::endl;
			continue;
		}
		monoms.push_back(tmpmonom);
	}
	return Polynom(monoms);
}

Monom::Monom(double inpcoef, const char *inpdegs) : coef(inpcoef) {
	for (size_t i = 0; i < VARS; i++) {
		if (inpdegs[i] >= 0 && inpdegs[i] <= 9) {
			degs[i] = inpdegs[i];
		}
		else {
			throw std::invalid_argument("Degrees should be >= 0 and <= 9");
		}
	}
}

Monom::Monom(double inpcoef, unsigned int inpdegs) : coef(inpcoef) {
	if (inpdegs >= std::pow(10, VARS)) {
		throw std::invalid_argument("Invalid degs number");
	}
	for (size_t i = 0; i < VARS; i++) {
		degs[VARS - i - 1] = inpdegs % 10;
		inpdegs /= 10;
	}
}

std::ostream &operator<<(std::ostream &stream, const Monom &m) {
	bool coef_is_one = false;
	bool all_degs_are_one = true;
	if (std::abs(std::abs(m.coef) - 1.0) < eps) {
		coef_is_one = true;
		bool sgn = m.coef > 0.0 ? true : false;
		if (!sgn) {
			stream << '-';
		}
	}
	for (size_t i = 0; i < VARS; i++) {
		if (m.degs[i] != 0) {
			all_degs_are_one = false;
			break;
		}
	}
	if (!coef_is_one || (coef_is_one && all_degs_are_one)) {
		stream << m.coef;
	}
	for (size_t i = 0; i < VARS; i++) {
		if (m.degs[i] != 0 && !(coef_is_one)) {
			stream << '*';
		}
		if (m.degs[i] != 0 && coef_is_one) { coef_is_one = false; }
		switch (m.degs[i]){
		case 0:
			break;
		case 1:
			stream << static_cast<char>('x' + i);
			break;
		default:
			stream << static_cast<char>('x' + i) << '^' << static_cast<int>(m.degs[i]);
		}
	}
	return stream;
}

bool Monom::can_sum(const Monom &sec) const noexcept {
	for (size_t i = 0; i < VARS; i++) {
		if (degs[i] != sec.degs[i]) {
			return false;
		}
	}
	return true;
}

Monom Monom::operator*(const Monom &sec) const {
	char resdegs[3];
	for (size_t i = 0; i < VARS; i++) {
		resdegs[i] = degs[i] + sec.degs[i];
	}
	try {
		return Monom(coef * sec.coef, resdegs);
	}
	catch (const std::exception &e) {
		throw std::runtime_error("Degrees overflow in multiplication");
	}
}

bool Monom::operator==(const Monom &sec) const noexcept {
	if ((can_sum(sec)) && (std::abs(coef - sec.coef) < eps)) {
		return true;
	}
	return false;
}

Polynom::Polynom(const List<Monom> &inpmonoms) : monoms(inpmonoms) {
	if (monoms.get_size() > 0) {
		merge_sorting(monoms, 0, monoms.get_size() - 1);
	}
	List<Monom>::iterator curnode(monoms);
	size_t id = 0;
	while (!curnode.is_end()) {
		if (std::abs((*curnode).get_coef()) < eps) {
			curnode++;
			monoms.pop(id);
			continue;
		}
		curnode++;
		id++;
	}
}

Polynom Polynom::operator+(const Polynom &sec) const {
	List<Monom>::iterator ptr1(monoms);
	List<Monom>::iterator ptr2(sec.monoms);
	List<Monom> res;
	while (!ptr1.is_end() && !ptr2.is_end()) {
		if ((*ptr1).get_degs() > (*ptr2).get_degs()) {
			res.push_back(*ptr1);
			ptr1++;
		}
		else if ((*ptr1).get_degs() < (*ptr2).get_degs()) {
			res.push_back(*ptr2);
			ptr2++;
		}
		else {
			double newcoef = (*ptr1).get_coef() + (*ptr2).get_coef();
			if (std::abs(newcoef) >= eps) {
				Monom tmp(*ptr1);
				tmp.set_coef(newcoef);
				res.push_back(tmp);
			}
			ptr1++;
			ptr2++;
		}
	}
	while (!ptr1.is_end()) {
		res.push_back(*ptr1);
		ptr1++;
	}
	while (!ptr2.is_end()) {
		res.push_back(*ptr2);
		ptr2++;
	}
	return Polynom(res);
}

Polynom Polynom::operator*(const Polynom &sec) const {
	Polynom res;
	List<Monom>::iterator curnode(sec.monoms);
	while (!curnode.is_end()) {
		res = res + *this * (*curnode);
		curnode++;
	}
	return res;
}

std::ostream &operator<<(std::ostream &stream, const Polynom &poly) {
	if (poly.monoms.get_size() == 0) {
		stream << '0';
		return stream;
	}
	bool sgn;
	List<Monom>::iterator curnode(poly.monoms);
	stream << *curnode++;
	for (size_t i = 1; i < poly.monoms.get_size(); i++) {
		sgn = (*curnode).get_coef() > 0.0 ? true : false;
		if (sgn) {
			stream << " + ";
			stream << *curnode;
		}
		else {
			stream << " - ";
			stream << -(*curnode);
		}
		curnode++;
	}
	return stream;
}

// Merge Sort

void merging(List<Monom> &list, size_t l, size_t m, size_t r) {
	List<Monom>::Node *ptr1 = list.get_node(l);
	List<Monom>::Node *ptr2 = list.get_node(m + 1);
	List<Monom>::Node *curnode = ptr1->prev;
	List<Monom>::Node *lastnode = list.get_node(r)->next;
	size_t pi1 = l;
	size_t pi2 = m + 1;
	if (ptr1 == list.head && pi1 <= m && pi2 <= r) {
		if (ptr1->value.get_degs() > ptr2->value.get_degs()) {
			curnode = ptr1;
			ptr1 = ptr1->next;
			pi1++;
		}
		else if (ptr1->value.get_degs() < ptr2->value.get_degs()) {
			ptr2->prev = nullptr;
			curnode = ptr2;
			list.head = ptr2;
			ptr2 = ptr2->next;
			pi2++;
		}
		else {
			curnode = ptr1;
			ptr1->value.set_coef(ptr1->value.get_coef() + ptr2->value.get_coef());
			ptr2->value.set_coef(0.0);
			ptr1 = ptr1->next;
			pi1++;
		}
	}
	while (pi1 <= m && pi2 <= r) {
		if (ptr1->value.get_degs() > ptr2->value.get_degs()) {
			curnode->next = ptr1;
			ptr1->prev = curnode;
			curnode = ptr1;
			ptr1 = ptr1->next;
			pi1++;
		}
		else if (ptr1->value.get_degs() < ptr2->value.get_degs()) {
			curnode->next = ptr2;
			ptr2->prev = curnode;
			curnode = ptr2;
			ptr2 = ptr2->next;
			pi2++;
		}
		else {
			curnode->next = ptr1;
			ptr1->prev = curnode;
			curnode = ptr1;
			ptr1->value.set_coef(ptr1->value.get_coef() + ptr2->value.get_coef());
			ptr2->value.set_coef(0.0);
			ptr1 = ptr1->next;
			pi1++;
		}
	}
	if (pi1 <= m) {
		curnode->next = ptr1;
		ptr1->prev = curnode;
		curnode = ptr1;
		ptr1 = ptr1->next;
		pi1++;
	}
	while (pi1 <= m) {
		curnode = ptr1;
		ptr1 = ptr1->next;
		pi1++;
	}
	if (pi2 <= r) {
		curnode->next = ptr2;
		ptr2->prev = curnode;
		curnode = ptr2;
		ptr2 = ptr2->next;
		pi2++;
	}
	while (pi2 <= r) {
		curnode = ptr2;
		ptr2 = ptr2->next;
		pi2++;
	}
	curnode->next = lastnode;
	if (lastnode != nullptr) {
		lastnode->prev = curnode;
	}
	else {
		list.tail = curnode;
	}
}

void merge_sorting(List<Monom> &list, size_t l, size_t r) {
	size_t m = l + (r - l) / 2;
	if (l == r) {
		return;
	}
	merge_sorting(list, l, m);
	merge_sorting(list, m + 1, r);
	merging(list, l, m, r);
}
