#include "Queue.h"

const int MAX_SIZE = 100;

Queue::Queue()
	: m_size(0)
	, m_max_size(MAX_SIZE)
	, m_front(-1)
	, m_rear(-1)
	, m_data(nullptr) {
	m_data = new int[m_max_size] {};
}

Queue::Queue(const Queue& object) {
		m_size = object.m_size;
		m_max_size = object.m_max_size;
		m_data = new int[m_max_size] {};
		if (object.m_rear >= object.m_front) {
			for (int i = 0; i < m_size; ++i) {
				m_data[i] = object.m_data[i];
			}
		}
		else {
			int i = 0;
			for (int j = object.m_front; j < m_max_size; ++j, ++i) {
				m_data[i] = object.m_data[j];
			}
			for (int j = 0; j <= object.m_rear; ++j, ++i) {
				m_data[i] = object.m_data[j];
			}

		}
		m_front = 0;
		m_rear = m_size - 1;

	}


Queue& Queue::operator=(const Queue& object) {
	if (this != &object) {
		delete[] m_data;
		m_size = object.m_size;
		m_max_size = object.m_max_size;
		m_data = new int[m_max_size] {};
		if (object.m_rear >= object.m_front) {
			for (int i = 0; i < m_size; ++i) {
				m_data[i] = object.m_data[i];
			}
		}
		else {
			int i = 0;
			for (int j = object.m_front; j < m_max_size; ++j, ++i) {
				m_data[i] = object.m_data[j];
			}
			for (int j = 0; j <= object.m_rear; ++j, ++i) {
				m_data[i] = object.m_data[j];
			}

		}
		m_front = 0;
		m_rear = m_size - 1;
		
	}
	return *this;
}	

Queue::~Queue() {
	delete[] m_data;
}

int& Queue::front() {
	if (!is_empty()) {
		return m_data[m_front];
	}
}

const int& Queue::front() const {
	if (!is_empty()) {
		return m_data[m_front];
	}
}

		void Queue::push(int element) {
			if (m_size==0) {
				m_front = 0;
				m_rear = -1;
			}
			if (m_size == m_max_size) {
				resize();
				
			}
			if (m_rear == m_max_size - 1) {
				m_rear = -1;
			}
				m_data[++m_rear] = element;
				++m_size;
			}	

		void Queue::pop() {
			if (m_size == 0) {
				return;
			}
			if (m_front == m_max_size - 1) {
				m_front = 0;
			}
			else {
				++m_front;
			}
			--m_size;
			if (m_rear == m_front) {
				m_rear = 0;
				m_data[0] = m_data[m_front];
				m_front = 0;
			}
		}
		
		void Queue::resize() {
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
		}
