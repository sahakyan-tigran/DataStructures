#pragma once

#include <exception>

template <typename T>
class Queue {
public:
	Queue();
	Queue(const Queue<T>&);
	Queue<T>& operator=(const Queue<T>&);
	~Queue();

	bool is_empty() const { return m_size == 0; }
	int size() const { return m_size; }
	T& front();
	const T& front() const;
	void push(T);
	void pop();

private:
	void resize();

private:
	static const int MAX_SIZE = 100;

	int m_max_size;
	int m_size;
	int m_front;
	int m_rear;
	T* m_data;
};

template <typename T>
Queue<T>::Queue() : m_max_size(MAX_SIZE), m_size(0), m_front(-1), m_rear(-1), m_data(nullptr) {
	m_data = new T[m_max_size]{};
}

template <typename T>
Queue<T>::Queue(const Queue<T>& object) {
	m_max_size = object.m_max_size;
	m_size = object.m_size;
	m_data = new T[m_max_size]{};
	if (object.m_rear >= object.m_front) {
		for (int i = 0; i < m_size; ++i) {
			m_data[i] = object.m_data[i];
		}
		m_front = object.m_front;
		m_rear = object.m_rear;
	}
	else {
		int i = 0;
		for (int j = m_front; j < m_max_size; ++j, ++i) {
			m_data[i] = object.m_data[j];
		}
		for (int j = 0; j <= m_rear; ++j, ++i) {
			m_data[i] = object.m_data[j];
		}
		m_front = 0;
		m_rear = m_size - 1;
	}
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& object) {
	if (this != &object) {
		delete[] m_data;
		m_max_size = object.m_max_size;
		m_size = object.m_size;
		m_data = new T[m_max_size]{};
		if (object.m_rear >= object.m_front) {
			for (int i = 0; i < m_size; ++i) {
				m_data[i] = object.m_data[i];
			}
			m_front = object.m_front;
			m_rear = object.m_rear;
		}
		else {
			int i = 0;
			for (int j = m_front; j < m_max_size; ++j, ++i) {
				m_data[i] = object.m_data[j];
			}
			for (int j = 0; j <= m_rear; ++j, ++i) {
				m_data[i] = object.m_data[j];
			}
			m_front = 0;
			m_rear = m_size - 1;
		}
	}
	return *this;
}

template <typename T>
Queue<T>::~Queue() {
	delete[] m_data;
}

template <typename T>
T& Queue<T>::front() {
	if (m_size != 0) {
		return m_data[m_front];
	}
	throw std::exception("The queue is empty.");
}

template <typename T>
const T& Queue<T>::front() const {
	if (m_size != 0) {
		return m_data[m_front];
	}
	throw std::exception("The queue is empty.");
}

template <typename T>
void Queue<T>::push(T element) {
	if (m_size == 0) {
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

template <typename T>
void Queue<T>::pop() {
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

template <typename T>
void Queue<T>::resize() {
	m_max_size *= 2;
	int* tmp = new T[m_max_size]{};
	if (m_rear > m_front) {
		for (int i = 0; i < m_size; ++i) {
			tmp[i] = m_data[i];
		}
	}
	else {
		int i = 0;
		for (int j = m_front; j < m_size; ++j, ++i) {
			tmp[i] = m_data[j];
		}
		for (int j = 0; j <= m_rear; ++j, ++i) {
			tmp[i] = m_data[j];
		}
		m_front = 0;
		m_rear = m_size - 1;
	}
	delete[] m_data;
	m_data = tmp;
}
