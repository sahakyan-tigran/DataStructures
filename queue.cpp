#include "queue.h"

const int MAX_SIZE = 100;

queue::queue() 
	: max_size(MAX_SIZE)
	, m_front(-1)
	,m_rear(-1)
	, m_data(nullptr) {
	m_data = new int[max_size] {};
}

queue::queue(const int* data, int size) 
	: max_size((size > MAX_SIZE) ? size : MAX_SIZE)
	,m_front(0)
	,m_rear(size - 1)
	,m_data(nullptr) {
	m_data = new int[max_size] {};
	for (int i = 0; i <= m_rear; ++i) {
		m_data[i] = data[i];
	}
}

queue::queue(const queue& object) 
	: max_size(object.max_size)
	, m_front(object.m_front)
	,m_rear(object.m_rear)
	,m_data(nullptr) {
	m_data = new int[max_size] {};
	for (int i = 0; i < max_size; ++i) {
		m_data[i] = object.m_data[i];
	}
}

queue& queue::operator=(const queue& object) {
	if (this != &object) {
		delete[] m_data;
		max_size = object.max_size;
		m_front = object.m_front;
		m_rear = object.m_rear;
		m_data = new int[max_size] {};
		for (int i = 0; i < max_size; ++i) {
			m_data[i] = object.m_data[i];
		}
	}
	return *this;
}

queue::~queue() {
	delete[] m_data;
}

int queue::size() const {
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
		return max_size - (m_front - m_rear - 1);
	}
}

void queue::push(int element) {
	if (is_empty()) {
		m_front = 0;
		m_rear = 0;
		m_data[0] = element;
		return;
	}
	if (size() == max_size) {
		int* tmp = new int[2 * max_size];
		if (m_rear > m_front) {
			for (int i = 0; i < max_size; ++i) {
				tmp[i] = m_data[i];
			}
		}
		else {
			int i = 0;
			for (int j = m_front; j < max_size; ++j, ++i) {
				tmp[i] = m_data[j];
			}
			for (int j = 0; j <= m_rear; ++j, ++i) {
				tmp[i] = m_data[j];
			}
			m_front = 0;
			m_rear = max_size - 1;
		}
		max_size *= 2;
		delete[] m_data;
		m_data = tmp;
		m_data[++m_rear] = element;
		return;
	}
	if (m_rear >= m_front) {
		if (m_rear == max_size - 1) {
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
}

void queue::pop() {
	if (is_empty()) {
		return;
	}
	if (m_rear == m_front) {
		m_front = -1;
		m_rear = 0;
		return;
	}
	if (m_front == max_size - 1) {
		m_front = 0;
	}
	else {
		++m_front;
	}
}


