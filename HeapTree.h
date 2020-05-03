#pragma once

#include <algorithm>

template <typename T>
class HeapTree {
public:
	HeapTree();
	HeapTree(const HeapTree<T>&);
	HeapTree<T>& operator=(const HeapTree<T>&);
	~HeapTree();

	bool empty() const { return m_size == 0; }
	int size() const { return m_size; }
	const T& max_value() const;
	void insert(const T&);
	void remove();

private:
	void allocate_and_initialize(const T* = nullptr);
	void deallocate();

private:
	static const int MAX_SIZE = 100;
	int m_max_size;
	int m_size;
	T* m_data;
};
	
template <typename T>
HeapTree<T>::HeapTree() : m_max_size(MAX_SIZE), m_size(0), m_data(nullptr) {
	allocate_and_initialize();
}

template <typename T>
HeapTree<T>::HeapTree(const HeapTree<T>& obj) 
	: m_max_size(obj.m_max_size)
	, m_size(obj.m_size)
	, m_data(nullptr) {
	allocate_and_initialize(obj.m_data);
}

template <typename T>
HeapTree<T>& HeapTree<T>::operator=(const HeapTree<T>& obj) {
	if (this != &obj) {
		deallocate();
		m_max_size = obj.m_max_size;
		m_size = obj.m_size;
		allocate_and_initialize(obj.m_data);
	}
}

template <typename T>
HeapTree<T>::~HeapTree() {
	deallocate();
}

template <typename T>
const T& HeapTree<T>::max_value() const {
	if (empty()) {
		throw std::exception("Heap is empty");
	}
	return m_data[1];
}

template <typename T>
void HeapTree<T>::insert(const T& element) {
	if (m_size + 1 == m_max_size) {
		m_max_size *= 2;
		T* tmp = new T[m_max_size];
		for (int i = 1; i <= m_size; ++i) {
			tmp[i] = m_data[i];
		}
		delete[] m_data;
		m_data = tmp;
	}
	m_data[++m_size] = element;
	int i = m_size;
	while (i != 1 && m_data[i] > m_data[i / 2]) {
		std::swap(m_data[i], m_data[i / 2]);
		i /= 2;
	}
}

template <typename T>
void HeapTree<T>::remove() {
	if (empty()) {
		return;
	}
	m_data[1] = m_data[m_size--];
	int current{ 1 }, child{ 2 * current };
	while (child <= m_size) {
		if (child + 1 <= m_size && m_data[child] < m_data[child + 1]) {
			++child;
		}
		if (m_data[child] > m_data[current]) {
			std::swap(m_data[child], m_data[current]);
			current = child;
			child = 2 * current;
		}
		else {
			break;
		}
	}
}

template <typename T>
void HeapTree<T>::allocate_and_initialize(const T* data) {
	m_data = new T[m_max_size]{};
	for (int i = 1; i <= m_size; ++i) {
		m_data[i] = data[i];
	}
}

template <typename T>
void HeapTree<T>::deallocate() {
	delete[] m_data;
}