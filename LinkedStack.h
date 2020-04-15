#pragma once

#include <exception>

template <typename T>
class LinkedStack {
public:
	LinkedStack();
	LinkedStack(const LinkedStack<T>&);
	LinkedStack<T>& operator=(const LinkedStack<T>&);
	~LinkedStack();

	bool is_empty() const { return m_size == 0; }
	int size() const { return m_size; }
	T& top();
	const T& top() const;
	void push(const T&);
	void pop();

private:
	template <typename T>
	struct Node {
		T m_info;
		Node<T>* m_previous;

		Node(const T& info = T()) : m_info(info), m_previous(nullptr) {}
		Node(const Node<T>&) = delete;
		Node<T>& operator=(const Node<T>&) = delete;
	};
	void deallocate();

private:
	int m_size;
	Node<T>* m_top;
};

template <typename T>
LinkedStack<T>::LinkedStack() : m_size(0), m_top(nullptr) {}

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& object) : m_size(object.m_size), m_top(nullptr)
{
	const Node<T>* pointer1 = object.m_top;
	Node<T>* pointer2 = nullptr;
	while (pointer1 != nullptr) {
		Node<T>* tmp = new Node<T>(pointer1->m_info);
		if (pointer1 == object.m_top) { m_top = tmp; }
		if (pointer2 != nullptr) { pointer2->m_previous = tmp; }
		pointer2 = tmp;
		pointer1 = pointer1->m_previous;
	}
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& object) {
	if (this != &object) {
		deallocate();
		m_size = object.m_size;
	    const Node<T>* pointer1 = object.m_top;
		Node<T>* pointer2 = nullptr;
		while (pointer1 != nullptr) {
			Node<T>* tmp = new Node<T>(pointer1->m_info);
			if (pointer1 == object.m_top) { m_top = tmp; }
			if (pointer2 != nullptr) { pointer2->m_previous = tmp; }
			pointer2 = tmp;
			pointer1 = pointer1->m_previous;
		}
	}
	return *this;
}

template <typename T>
LinkedStack<T>::~LinkedStack() {
	deallocate();
}

template <typename T>
T& LinkedStack<T>::top() {
	if (!is_empty()) {
		return m_top->m_info;
	}
	throw std::exception("The stack is empty.");
}

template <typename T>
const T& LinkedStack<T>::top() const {
	if (!is_empty()) {
		return m_top->m_info;
	}
	throw std::exception("The stack is empty.");
}

template <typename T>
void LinkedStack<T>::push(const T& element) {
	Node<T>* tmp = new Node<T>(element);
	tmp->m_previous = m_top;
	m_top = tmp;
	++m_size;
}

template <typename T>
void LinkedStack<T>::pop() {
	if (m_size != 0) {
		Node<T>* p = m_top->m_previous;
		delete m_top;
		m_top = p;
		--m_size;
		return;
	}
	throw std::exception("The stack is empty.");
}

template <typename T>
void LinkedStack<T>::deallocate() {
	if (m_size != 0) {
		Node<T>* pointer1 = m_top;
		Node<T>* pointer2 = m_top->m_previous;
		while (m_size != 0) {
			delete pointer1;
			pointer1 = pointer2;
			pointer2 = (m_size != 1) ? pointer1->m_previous : nullptr;
			--m_size;
		}
	}
}
