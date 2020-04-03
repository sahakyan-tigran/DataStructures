#include "Queue.h"

const int MAX_SIZE = 100;

Queue::Queue() 
	: m_max_size(MAX_SIZE)
	, m_front(-1)
	, m_rear(-1)
	, m_data(nullptr) {
	m_data = new int[m_max_size] {};
}

Queue::Queue(const int* data, int size) 
	: m_max_size((size > MAX_SIZE) ? size : MAX_SIZE)
	, m_front(0)
	, m_rear(size - 1)
	, m_data(nullptr) {
	m_data = new int[m_max_size] {};
	for (int i = 0; i <= m_rear; ++i) {
		m_data[i] = data[i];
	}
}	// remove

Queue::Queue(const queue& object) 
	: m_max_size(object.m_max_size)
	, m_front(object.m_front)
	, m_rear(object.m_rear)
	, m_data(nullptr) {
	m_data = new int[m_max_size] {};
	for (int i = 0; i < m_max_size; ++i) {
		m_data[i] = object.m_data[i];
	}
}	// let's talk about this during lesson

Queue& Queue::operator=(const queue& object) {
	if (this != &object) {
		delete[] m_data;
		m_max_size = object.m_max_size;
		m_front = object.m_front;
		m_rear = object.m_rear;
		m_data = new int[m_max_size] {};
		for (int i = 0; i < m_max_size; ++i) {
			m_data[i] = object.m_data[i];
		}
	}
	return *this;
}	// let's talk about this during lesson

Queue::~Queue() {
	delete[] m_data;
}

int Queue::size() const {
	if (m_rear == m_front) {
		if (m_rear == -1) {
			return 0;
		}
		return 1;
	}
	if (m_rear > m_front) {
		return m_rear - m_front + 1;
	}
	else {
		return m_max_size - (m_front - m_rear - 1);
	}
}	// maybe it would be better to have a member m_size

int& Queue::front() {
	if(!is_empty()) {
	       return m_data[m_front];
	}  
const int& Queue::front() {
	if(!is_empty()) {
	       return m_data[m_front];
	}  
void Queue::push(int element) {
	if (is_empty()) {
		m_front = 0;
		m_rear = 0;
		m_data[0] = element;
		return;
	}
	if (size() == m_max_size) {
		int* tmp = new int[2 * m_max_size]{};
		if (m_rear > m_front) {
			for (int i = 0; i < m_max_size; ++i) {
				tmp[i] = m_data[i];
			}
		}
		else {
			int i = 0;
			for (int j = m_front; j < m_max_size; ++j, ++i) {
				tmp[i] = m_data[j];
			}
			for (int j = 0; j <= m_rear; ++j, ++i) {
				tmp[i] = m_data[j];
			}
			m_front = 0;
			m_rear = m_max_size - 1;
		}
		m_max_size *= 2;
		delete[] m_data;
		m_data = tmp;
		m_data[++m_rear] = element;
		return;
	}
	if (m_rear >= m_front) {
		if (m_rear == m_max_size - 1) {
			m_rear = 0;
			m_data[m_rear] = element;
		}
		else {
			m_data[++m_rear] = element;
		}
	}
	else {
		m_data[++m_rear] = element;
	}
}	// function is too long

void Queue::pop() {
	if (is_empty()) {
		return;
	}
	if (m_rear == m_front) {
		m_front = -1;
		m_rear = 0;
		return;
	}
	if (m_front == m_max_size - 1) {
		m_front = 0;
	}
	else {
		++m_front;
	}
}
// maybe you need full function


