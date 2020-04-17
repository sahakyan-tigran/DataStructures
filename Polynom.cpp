#include "Polynom.h"

#include <cmath>


Polynom::Polynom() : m_head(nullptr) {
	Node* tmp = new Node(0, 0);
	m_head = tmp;
}

Polynom::Polynom(double* coefficents, int* exponents, int size) : m_head(nullptr) {
	Node* pointer1 = nullptr;
	m_head = new Node(0, 0);
	for (int i = 0; i < size; ++i) {
		Node* tmp = new Node(coefficents[i], exponents[i]);
		if (pointer1 == nullptr) { 
			if (exponents[i] == 0) {
				delete m_head;
				m_head = tmp;
			}
			else {
				m_head->m_next = tmp;
			}
		}
		if (pointer1 != nullptr) { pointer1->m_next = tmp; }
		pointer1 = tmp;
	}
}

Polynom::Polynom(const Polynom& object) : m_head(nullptr) {
	const Node* pointer1 = object.m_head;
	Node* pointer2 = nullptr;
	while (pointer1 != nullptr) {
		Node* tmp = new Node(pointer1->m_coefficient, pointer1->m_exponent);
		if (pointer2 == nullptr) { m_head = tmp; }
		if (pointer2 != nullptr) { pointer2->m_next = tmp; }
		pointer2 = tmp;
		pointer1 = pointer1->m_next;
	}
}

Polynom& Polynom::operator=(const Polynom& object) {
	if (this != &object) {
		deallocate();
		const Node* pointer1 = object.m_head;
		Node* pointer2 = nullptr;
		while (pointer1 != nullptr) {
			Node* tmp = new Node(pointer1->m_coefficient, pointer1->m_exponent);
			if (pointer2 == nullptr) { m_head = tmp; }
			if (pointer2 != nullptr) { pointer2->m_next = tmp; }
			pointer2 = tmp;
			pointer1 = pointer1->m_next;
		}
	}
	return *this;
}

Polynom::~Polynom() {
	deallocate();
}

Polynom& Polynom::operator+=(const Polynom& object) {
	const Node* pointer1 = object.m_head;
	Node* pointer2 = m_head;
	Node* real_head = m_head;
	while (pointer1 != nullptr) {
		if (find_exponent(pointer1->m_exponent)) {
			m_head->m_coefficient += pointer1->m_coefficient;
		}
		else {
			Node* tmp = new Node(pointer1->m_coefficient, pointer1->m_exponent);
			tmp->m_next = m_head->m_next;
			m_head->m_next = tmp;
		}
		m_head = real_head;
		pointer1 = pointer1->m_next;
	}
	return *this;
}

Polynom& Polynom::operator*=(const Polynom& object) {
	Polynom y;
	const Node* pointer1 = object.m_head;
	Node* pointer2 = m_head;
	while (pointer1 != nullptr) {
		Polynom x;
		Node* pointer3 = x.m_head;
		while (pointer2 != nullptr) {
			double coefficient = pointer1->m_coefficient * pointer2->m_coefficient;
			int exponent = pointer1->m_exponent + pointer2->m_exponent;
			Node* tmp = new Node(coefficient, exponent);
			pointer3->m_next = tmp;
			pointer3 = tmp;
			pointer2 = pointer2->m_next;
		}
		y += x;
		pointer1 = pointer1->m_next;
		pointer2 = m_head;
	}
	return *this = y;
}

Polynom& Polynom::operator*=(const double number) {
	Node* pointer1 = m_head;
	while (pointer1 != nullptr) {
		pointer1->m_coefficient *= number;
		pointer1 = pointer1->m_next;
	}
	return *this;
}

Polynom& Polynom::derivative() {
	Node* pointer1 = m_head->m_next;
	delete m_head;
	m_head = pointer1;
	while (pointer1 != nullptr) {
		pointer1->m_coefficient *= (pointer1->m_exponent)--;
		pointer1 = pointer1->m_next;
	}
	return *this;
}

double Polynom::count_value(double value) {
	double result = 0;
	Node* pointer1 = m_head;
	while (pointer1 != nullptr) {
		result += pointer1->m_coefficient * pow(value, pointer1->m_exponent);
		pointer1 = pointer1->m_next;
	}
	return result;
}


void Polynom::deallocate() {
	if ((m_head->m_coefficient == 0) && (m_head->m_exponent == 0)) {
		delete m_head;
		return;
	}
		Node* prev = m_head->m_next;
		while (prev != nullptr) {
			delete m_head;
			m_head = prev;
			prev = prev->m_next;
		}
		delete m_head;
}

bool Polynom::find_exponent(int exponent) {
	if (m_head->m_exponent == exponent) {
		return true;
	}
	while (m_head->m_next != nullptr) {
		if (m_head->m_next->m_exponent == exponent) {
			m_head = m_head->m_next;
			return true;
		}
		else {
			if (m_head->m_next->m_exponent > exponent) {
				return false;
			}
			m_head = m_head->m_next;
		}
	}
	return false;
}

Polynom operator+(Polynom object1,const Polynom& object2) {
	return object1 += object2;
}

Polynom operator*(Polynom object1,const Polynom& object2) {
	return object1 *= object2;
}

Polynom operator*(Polynom object1, const double number) {
	return object1 *= number;
}

std::ostream& operator<<(std::ostream& out, const Polynom& object)
{
	Polynom p(object);
	while (p.m_head != nullptr)
	{
		int pow = p.m_head->m_exponent;
		int coefficient = p.m_head->m_coefficient;
		if (coefficient == 0) {
			p.m_head = p.m_head->m_next;
			continue;
		}
		if (coefficient != 1) {
			out << coefficient;
		}
		out << "x^" << pow;
		if (p.m_head->m_next != nullptr) {
			out << " + ";
		}
		p.m_head = p.m_head->m_next;
	}
	out << std::endl;
	return out;
}