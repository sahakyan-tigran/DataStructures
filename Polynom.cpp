#include "Polynom.h"

#include <cmath>


Polynom::Polynom() : m_exponent(-1), m_head(nullptr) {
	m_head = new Node(0, -1);
	m_head->m_next = m_head;
}

Polynom::Polynom(const Information& object) : m_exponent(-1), m_head(nullptr) {
	m_head = new Node(0, -1);
	m_head->m_next = m_head;
	Node* previous = m_head;
	Node* tmp = nullptr;
	for (int i = 0; i < object.size(); ++i) {
		tmp = new Node(object[i].first, object[i].second);
		previous->m_next = tmp;
		previous = previous->m_next;
	}
	if (tmp != nullptr) {
		tmp->m_next = m_head;
		m_exponent = object[0].second;
	}
}

Polynom::Polynom(const Polynom& object) : m_exponent(object.m_exponent), m_head(nullptr) {
	m_head = new Node(0, -1);
	m_head->m_next = m_head;
	const Node* objectptr = object.m_head->m_next;
	Node* thisptr = m_head;
	Node* tmp{};
	while (objectptr != object.m_head) {
		tmp = new Node(objectptr->m_coefficient, objectptr->m_exponent);
		thisptr->m_next = tmp;
		thisptr = tmp;
		objectptr = objectptr->m_next;
	}
	if (tmp != nullptr) {
		tmp->m_next = m_head;
	}
}

Polynom& Polynom::operator=(const Polynom& object) {
	if (this != &object) {
		deallocate();
		m_exponent = object.m_exponent;
		m_head = new Node(0, -1);
		m_head->m_next = m_head;
		const Node* objectptr = object.m_head->m_next;
		Node* thisptr = m_head;
		Node* tmp{};
		while (objectptr != object.m_head) {
			tmp = new Node(objectptr->m_coefficient, objectptr->m_exponent);
			thisptr->m_next = tmp;
			thisptr = tmp;
			objectptr = objectptr->m_next;
		}
		if (tmp != nullptr) {
			tmp->m_next = m_head;
		}
	}
	return *this;
}

Polynom::~Polynom() {
	deallocate();
}

Polynom& Polynom::operator+=(const Polynom& object) {
	const Node* object_ptr = object.m_head->m_next;
	Node* this_current = m_head->m_next;
	Node* previous = m_head;
	while (object_ptr != object.m_head) {
		if (this_current->m_exponent == object_ptr->m_exponent) {
			this_current->m_coefficient += object_ptr->m_coefficient;
			if (this_current->m_coefficient == 0) {
				previous->m_next = this_current->m_next;
				delete this_current;
				this_current = previous;
			}
			previous = this_current;
			this_current = this_current->m_next;
			object_ptr = object_ptr->m_next;
		}
		else {
			if (this_current->m_exponent < object_ptr->m_exponent) {
				Node* tmp = new Node(object_ptr->m_coefficient, object_ptr->m_exponent);
				previous->m_next = tmp;
				tmp->m_next = this_current;
				previous = tmp;
				object_ptr = object_ptr->m_next;
			}
			else {
				previous = this_current;
				this_current = this_current->m_next;
			}
		}
	}
	m_exponent = m_head->m_next->m_exponent;
	return *this;
}

Polynom& Polynom::operator*=(const Polynom& object) {
	Polynom y;
	const Node* pointer1 = object.m_head->m_next;
	Node* pointer2 = m_head->m_next;
	while (pointer1 != object.m_head) {
		Polynom x;
		Node* pointer3 = x.m_head;
		while (pointer2 != m_head) {
			double coefficient = pointer1->m_coefficient * pointer2->m_coefficient;
			int exponent = pointer1->m_exponent + pointer2->m_exponent;
			Node* tmp = new Node(coefficient, exponent);
			pointer3->m_next = tmp;
			tmp->m_next = x.m_head;
			pointer3 = tmp;
			pointer2 = pointer2->m_next;
		}
		y += x;
		pointer1 = pointer1->m_next;
		pointer2 = m_head->m_next;
	}
	m_exponent = y.m_exponent;
	return *this = y;
}

Polynom& Polynom::operator*=(const double number) {
	Node* pointer1 = m_head->m_next;
	while (pointer1 != m_head) {
		pointer1->m_coefficient *= number;
		pointer1 = pointer1->m_next;
	}
	return *this;
}

Polynom& Polynom::derivative() {
	Node* current = m_head->m_next;
	Node* previous = m_head;
	while (current != m_head) {
		if (current->m_exponent == 0) {
			delete current;
			previous->m_next = m_head;
			break;
		}
		current->m_coefficient *= (current->m_exponent)--;
		current = current->m_next;
		previous = previous->m_next;
	}
	--m_exponent;
	return *this;
}

double Polynom::count_value(double value) const {
	double result = 0;
	Node* pointer1 = m_head->m_next;
	while (pointer1 != m_head) {
		result += pointer1->m_coefficient * pow(value, pointer1->m_exponent);
		pointer1 = pointer1->m_next;
	}
	return result;
}

void Polynom::deallocate() {
	Node* previous = m_head;
	Node* current = m_head->m_next;
	while (current != m_head) {
		previous = current;
		current = current->m_next;
		delete previous;
	}
	delete m_head;
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
	Polynom::Node* pointer1 = object.m_head->m_next;
	while (pointer1 != object.m_head)
	{
		if (pointer1->m_coefficient != 1) {
			out << pointer1->m_coefficient;
		}
		out << "x^" << pointer1->m_exponent;
		if (pointer1->m_next->m_exponent != -1) {
			out << " + ";
		}
		pointer1 = pointer1->m_next;
	}
	out << std::endl;
	return out;
}