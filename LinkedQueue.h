#pragma once

#include <exception>

template <typename T>
class LinkedQueue {
public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue<T>&);
	LinkedQueue<T>& operator=(const LinkedQueue<T>&);
	~LinkedQueue();

	bool is_empty() const { return m_size == 0; }
	int size() const { return m_size; }
	T& front();
	const T& front() const;
	void push(const T&);
	void pop();

private:
	template <typename T>
	struct Node {
		T m_info;
		Node<T>* m_next;

		Node(const T& info = T()) : m_info(info), m_next(nullptr) {}
		Node(const Node<T>&) = delete;
		Node<T>& operator=(const Node<T>&) = delete;
	};
	void deallocate();

private:
	int m_size;
	Node<T>* m_front;
	Node<T>* m_rear;
};

template <typename T>
LinkedQueue<T>::LinkedQueue() : m_size(0), m_front(nullptr), m_rear(nullptr) {}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& object) : m_size(object.m_size), m_front(nullptr), m_rear(nullptr)
{
	const Node<T>* pointer1 = object.m_front;
	Node<T>* pointer2 = nullptr;
	while (pointer1 != nullptr) {
		Node<T>* tmp = new Node<T>(pointer1->m_info);
		if (pointer1 == object.m_front) { m_front = tmp; }
		if (pointer2 != nullptr) { pointer2->m_next = tmp; }
		pointer2 = tmp;
		pointer1 = pointer1->m_next;
	}
	m_rear = pointer2;
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& object) {
	if (this != &object) {
		deallocate();
		m_size = object.m_size;
		const Node<T>* pointer1 = object.m_front;
		Node<T>* pointer2 = nullptr;
		while (pointer1 != nullptr) {
			Node<T>* tmp = new Node<T>(pointer1->m_info);
			if (pointer1 == object.m_front) { m_front = tmp; }
			if (pointer2 != nullptr) { pointer2->m_next = tmp; }
			pointer2 = tmp;
			pointer1 = pointer1->m_next;
		}
		m_rear = pointer2;
	}
	return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
	deallocate();
}

template <typename T>
T& LinkedQueue<T>::front() {
	if (m_size != 0) {
		return m_front->m_info;
	}
	throw std::exception("The queue is empty.");
}

template <typename T>
const T& LinkedQueue<T>::front() const {
	if (m_size != 0) {
		return m_front->m_info;
	}
	throw std::exception("The queue is empty.");
}

template <typename T>
void LinkedQueue<T>::push(const T& element) {
	Node<T>* tmp = new Node<T>(element);
	(m_size == 0) ? m_front = tmp : m_rear->m_next = tmp;
	m_rear = tmp;
	++m_size;
}

template <typename T>
void LinkedQueue<T>::pop() {
	if (m_size != 0) {
		Node<T>* pointer1 = m_front->m_next;
		delete m_front;
		m_front = pointer1;
		--m_size;
		return;
	}
	throw std::exception("The queue is empty.");
}

template <typename T>
void LinkedQueue<T>::deallocate() {
	if (m_size != 0) {
		Node<T>* pointer1 = m_front;
		Node<T>* pointer2 = m_front->m_next;
		while (m_size != 0) {
			delete pointer1;
			pointer1 = pointer2;
			pointer2 = (m_size != 1) ? pointer1->m_next : nullptr;
			--m_size;
		}
	}
}
