#include "LinkedList.h"

#include <exception>

LinkedList::LinkedList() : m_size(0) , m_head(nullptr) {}

LinkedList::LinkedList(int size, int* data) : m_size(size), m_head(nullptr) {
	Node* tmp_first = new Node(data[0]);
	m_head = tmp_first;

	for (int i = 1;i < size;++i) {
		Node* tmp = new Node(data[i]);
		tmp_first->m_next = tmp;
		tmp->m_previous = tmp_first;
		tmp_first = tmp;
	}
}

LinkedList::LinkedList(const LinkedList& object) : m_size(object.m_size), m_head(nullptr) {
	if (m_size != 0) {
		int size = m_size - 1;
		Node* tmp = new Node(object.m_head->m_info);
		m_head = tmp;
		Node* pointer1 = object.m_head->m_next;
		while (size != 0) {
			Node* new_tmp = new Node(pointer1->m_info);
			tmp->m_next = new_tmp;
			new_tmp->m_previous = tmp;
			tmp = new_tmp;
			pointer1 = pointer1->m_next;
			--size;
		}
	}
}

LinkedList& LinkedList::operator=(const LinkedList& object) {
	if ((object.m_size != 0) && (this != &object)) {
		deallocate();
		m_size = object.m_size;
		int size = m_size - 1;
		Node* tmp = new Node(object.m_head->m_info);
		m_head = tmp;
		Node* pointer1 = object.m_head->m_next;
		while (size != 0) {
			Node* new_tmp = new Node(pointer1->m_info);
			tmp->m_next = new_tmp;
			new_tmp->m_previous = tmp;
			tmp = new_tmp;
			pointer1 = pointer1->m_next;
			--size;
		}
	}
	return *this;
}

LinkedList::~LinkedList() {
	deallocate();
}

void LinkedList::insert(int index, int element) {
	if (index <= 0) {
		throw std::exception("wrong index");
	}
	if (index > m_size + 1) { index = m_size + 1; }
	Node* new_tmp = new Node(element);
	if (index == 1) {
		if (m_size != 0) {
			new_tmp->m_next = m_head;
			m_head->m_previous = new_tmp;
		}
		m_head = new_tmp;
		++m_size;
		return;
	}
	Node* tmp = m_head;
	int i = 1;
	for (; i < index - 1; ++i) {
		tmp = tmp->m_next;
	}
	if (index == m_size + 1) {
		new_tmp->m_previous = tmp;
		tmp->m_next = new_tmp;
		++m_size;
		return;
	}
	Node* pointer1 = tmp->m_next;
	tmp->m_next = new_tmp;
	new_tmp->m_previous = tmp;
	new_tmp->m_next = pointer1;
	pointer1->m_previous = new_tmp;
	++m_size;
}

void LinkedList::remove(int index) {
	if (index <= 0) {
		throw std::exception("wrong index");
	}
	if (index > m_size ) { index = m_size ; }
	if (m_size != 0) {
		throw std::exception("index is less than 0");
	}
	Node* tmp = m_head;
	if (index == 1) {
		if (m_size != 1) {
			m_head->m_next->m_previous = nullptr;
			m_head = m_head->m_next;
		}
		delete tmp;
		--m_size;
		return;
	}
	int i = 1;
	for (; i < index ; ++i) {
		tmp = tmp->m_next;
	}
	if (index == m_size) {
		tmp->m_previous->m_next = nullptr;
		delete tmp;
		--m_size;
		return;
	}
	tmp->m_next->m_previous = tmp->m_previous;
	tmp->m_previous->m_next = tmp->m_next;
	--m_size;
	delete tmp;
}

void LinkedList::deallocate() {
	if (m_size != 0) {
		Node* pointer1 = m_head;
		Node* pointer2 = m_head->m_next;
		while (m_size != 0) {
			delete pointer1;
			pointer1 = pointer2;
			pointer2 = (m_size == 1) ? nullptr : pointer2->m_next;
			--m_size;
		}
	}
}