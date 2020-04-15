#pragma once

#include <exception>

template <typename T>
class Stack {
public:
	Stack();
	Stack(const Stack<T>&);
	Stack& operator=(const Stack<T>&);
	~Stack();

	bool is_empty() const { return  m_top == -1; }
	int size() const { return (m_top + 1); }
	T& top();
	const T& top() const;
	void push(T);
	void pop();

private:
	static const int MAX_SIZE = 100;

	int m_max_size;
	int m_top;
	T* m_data;
};

template <typename T>
Stack<T>::Stack() : m_max_size(MAX_SIZE), m_top(-1), m_data(nullptr) {
	m_data = new T[m_max_size]{};
}

template <typename T>
Stack<T>::Stack(const Stack<T>& object) : m_max_size(object.m_max_size), m_top(object.m_top), m_data(nullptr) {
	m_data = new T[m_max_size]{};
	for (int i = 0; i <= m_top; ++i) {
		m_data[i] = object.m_data[i];
	}
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& object) {
	if (this != &object) {
		delete[] m_data;
		m_top = object.m_top;
		m_max_size = object.m_max_size;
		m_data = new T[m_max_size]{};
		for (int i = 0; i <= m_top; ++i) {
			m_data[i] = object.m_data[i];
		}
	}
	return *this;
}

template <typename T>
Stack<T>::~Stack() {
	delete[] m_data;
}

template <typename T>
T& Stack<T>::top() {
	if (!is_empty()) {
		return m_data[m_top];
	}
	throw std::exception("The stack is empty.");
}

template <typename T>
const T& Stack<T>::top() const {
	if (!is_empty()) {
		return m_data[m_top];
	}
	throw std::exception("The stack is empty.");
}

template <typename T>
void Stack<T>::push(T element) {
	if (m_top + 1 == m_max_size) {
		m_max_size *= 2;
		T* tmp = new T[m_max_size]{};
		for (int i = 0; i <= m_top; ++i) {
			tmp[i] = m_data[i];
		}
		delete[] m_data;
		m_data = tmp;
	}
	++m_top;
	m_data[m_top] = element;
}

template <typename T>
void Stack<T>::pop() {
	if (!is_empty()) {
		--m_top;
	}
	throw std::exception("The stack is empty.");
}
