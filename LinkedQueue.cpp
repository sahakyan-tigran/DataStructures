#include "LinkedQueue.h"

#include <exception>

LinkedQueue::LinkedQueue() : m_size(0), m_front(nullptr), m_rear(nullptr) {}

LinkedQueue::LinkedQueue(const LinkedQueue& object) : m_size(object.m_size), m_front(nullptr) , m_rear(nullptr)
{
	if (object.m_size != 0) {
		int size = m_size - 1;
		Node* tmp = new Node(object.m_front->m_info);
		m_front = tmp;
		Node* pointer1 = object.m_front->m_next;

		while (size != 0) {
			Node* new_tmp = new Node(pointer1->m_info);
			tmp->m_next = new_tmp;
			tmp = new_tmp;
			pointer1 = pointer1->m_next;
			--size;
		}
		m_rear = tmp;
	}
} 

LinkedQueue& LinkedQueue::operator=(const LinkedQueue& object) {
	if ((this != &object) && (object.m_size != 0)) {
		deallocate();
		m_size = object.m_size;
		int size = m_size - 1;
		Node* tmp = new Node(object.m_front->m_info);
		m_front = tmp;
		Node* pointer1 = object.m_front->m_next;

		while (size != 0) {
			Node* new_tmp = new Node(pointer1->m_info);
			tmp->m_next = new_tmp;
			tmp = new_tmp;
			pointer1 = pointer1->m_next;
			--size;
		}
		m_rear = tmp;
	}
	return *this;
}

LinkedQueue::~LinkedQueue() {
	deallocate();
}

int& LinkedQueue::front() {
	if (m_size != 0) {
		return m_front->m_info;
	}
	throw std::exception("The queue is empty.");
}

const int& LinkedQueue::front() const {
	if (m_size != 0) {
		return m_front->m_info;
	}
	throw std::exception("The queue is empty.");
}

void LinkedQueue::push(int element) {
	Node* tmp = new Node(element);
	(m_size == 0) ? m_front = tmp : m_rear->m_next = tmp;
	m_rear = tmp;
	++m_size;
}

void LinkedQueue::pop() {
	if (m_size != 0) {
		Node* pointer1 = m_front->m_next;
		delete m_front;
		m_front = pointer1;
		--m_size;
		return;
	}
	throw std::exception("The queue is empty.");
}

void LinkedQueue::deallocate() {
	if (m_size != 0) {
		Node* pointer1 = m_front;
		Node* pointer2 = m_front->m_next;
		while (m_size != 0) {
			delete pointer1;
			pointer1 = pointer2;
			pointer2 = (m_size != 1) ? pointer1->m_next : nullptr;
			--m_size;
		}
	}
}