#include "LinkedStack.h"

#include <exception>

LinkedStack::LinkedStack() : m_size(0) , m_top(nullptr) {}

LinkedStack::LinkedStack(const LinkedStack& object) : m_size(object.m_size) , m_top(nullptr)
{
	if (object.m_size != 0) {
		int size = m_size - 1;
		Node* tmp = new Node(object.m_top->m_info);
		m_top = tmp;
		Node* pointer1 = object.m_top->m_previous;

		while (size != 0) {
			Node* new_tmp = new Node(pointer1->m_info);
			tmp->m_previous = new_tmp;
			tmp = new_tmp;
			pointer1 = pointer1->m_previous;
			--size;
		}
	}
}

LinkedStack& LinkedStack::operator=(const LinkedStack& object) {
	if ((this != &object) && (object.m_size != 0)) {
	    deallocate();
		m_size = object.m_size;
		int size = m_size - 1;
		Node* tmp = new Node(object.m_top->m_info);
		m_top = tmp;
		Node* pointer1 = object.m_top->m_previous;
    
		while (size != 0) {
			Node* new_tmp = new Node(pointer1->m_info);
			tmp->m_previous = new_tmp;
			tmp = new_tmp;
			pointer1 = pointer1->m_previous;
			--size;
		}
	}
	return *this;
}

LinkedStack::~LinkedStack() {
	deallocate();
}


int& LinkedStack::top() {
	if (!is_empty()) {
		return m_top->m_info;
	}
		throw std::exception("The stack is empty.");
}

const int& LinkedStack::top() const {
	if (!is_empty()) {
		return m_top->m_info;
	}
	throw std::exception("The stack is empty.");
}

void LinkedStack::push(int element) {
	Node* tmp = new Node(element);
	tmp->m_previous = m_top;
	m_top = tmp;
	++m_size;
}

void LinkedStack::pop() {
	if (m_size != 0) {
		Node* p = m_top->m_previous;
		delete m_top;
		m_top = p;
		--m_size;
		return;
	}
	throw std::exception("The stack is empty.");
}

void LinkedStack::deallocate() {
	if (m_size != 0) {
		Node* pointer1 = m_top;
		Node* pointer2 = m_top->m_previous;
		while (m_size != 0) {
			delete pointer1;
			pointer1 = pointer2;
			pointer2 = (m_size != 1) ? pointer1->m_previous : nullptr;
			--m_size;
		}
	}
}