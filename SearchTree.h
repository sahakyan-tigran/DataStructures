#pragma once

#include "BinaryTree.h"

template <typename T>
class SearchTree {
public:
	SearchTree() : m_root(nullptr) {}
	SearchTree(const SearchTree<T>&);
	SearchTree<T>& operator=(const SearchTree<T>&);
	virtual ~SearchTree();

	bool empty() { return m_root = nullptr; }
	BinaryTree::Node<T>* find(const T&);
	const BinaryTree::Node<T>* find(const T&) const;

	void insert(const T&);
	void remove(const T&);

private:
	void allocate(const SearchTree<T>&);
	void allocate_help(BinaryTree::Node<T>*, BinaryTree::Node<T>*);
	void deallocate(BinaryTree::Node<T>*);

	BinaryTree::Node<T>* find_father(const T&);

private:
	BinaryTree::Node<T>* m_root;
};

template <typename T>
SearchTree<T>::SearchTree(const SearchTree<T>& obj) : m_root(nullptr) {
	allocate(obj);
}

template <typename T>
SearchTree<T>& SearchTree<T>::operator=(const SearchTree& obj) {
	if (this != &obj) {
		deallocate(m_root);
		allocate(obj);
	}
	return *this;
}

template <typename T>
SearchTree<T>::~SearchTree() {
	deallocate(m_root);
}

template <typename T>
BinaryTree::Node<T>* SearchTree<T>::find(const T& element) {
	if (m_root == nullptr) {
		return nullptr;
	}
	BinaryTree::Node<T>* pointer = m_root;
	while (pointer != nullptr && pointer->m_info != element) {
		if (pointer->m_info > element) {
			pointer = pointer->m_left;
		}
		else {
			pointer = pointer->m_right;
		}
	}
	return pointer;
}

template <typename T>
const BinaryTree::Node<T>* SearchTree<T>::find(const T& element) const {
	if (m_root == nullptr) {
		return nullptr;
	}
	const BinaryTree::Node<T>* pointer = m_root;
	while (pointer != nullptr && pointer->m_info != element) {
		if (pointer->m_info > element) {
			pointer = pointer->m_left;
		}
		else {
			pointer = pointer->m_right;
		}
	}
	return pointer;
}

template <typename T>
void SearchTree<T>::insert(const T& element) {
	if (m_root == nullptr) {
		m_root = new BinaryTree::Node<T>(element);
		return;
	}
	BinaryTree::Node<T>* pointer = m_root;
	while (!pointer->is_leaf()) {
		if (pointer->m_info >= element) {
			if (!pointer->has_left()) {
				break;
			}
			pointer = pointer->m_left;
		}
		else {
			if (!pointer->has_right()) {
				break;
			}
			pointer = pointer->m_right;
		}
	}
	if (pointer->m_info >= element) {
		pointer->m_left = new BinaryTree::Node<T>(element);
	}
	else {
		pointer->m_right = new BinaryTree::Node<T>(element);
	}
}

template <typename T>
void SearchTree<T>::remove(const T& element) {
	BinaryTree::Node<T>* father = find_father(element);
	BinaryTree::Node<T>* child = find(element);
	if (child == nullptr) {
		return;
	}
	while (child->has_both()) {
		T tmp = child->m_info;
		child->m_info = child->m_right->m_info;
		child->m_right->m_info = tmp;
		father = child;
		child = child->m_right;
	}
	if (child->is_leaf()) {
		if (child == m_root) {
			delete child;
			return;
		}
		if (father->m_left == child) {
			father->m_left = nullptr;
		}
		else {
			father->m_right = nullptr;
		}
	}
	else {
		if (child == m_root) {
			m_root = (child->has_left()) ? child->m_left : child->m_right;
			delete child;
			return;
		}
		if (father->m_left == child) {
			father->m_left = (child->has_left()) ? child->m_left : child->m_right;
		}
		else {
			father->m_right = (child->has_left()) ? child->m_left : child->m_right;
		}
	}
	delete child;
}

template <typename T>
void SearchTree<T>::allocate(const SearchTree<T>& obj) {
	if (obj.empty()) {
		return;
	}
	m_root = new BinaryTree::Node<T>(obj.m_root->m_info);
	allocate_help(m_root, obj.m_root);
}

template <typename T>
void SearchTree<T>::allocate_help(BinaryTree::Node<T>* root1, BinaryTree::Node<T>* root2) {
	if (root2->has_left()) {
		root1->m_left = new BinaryTree::Node<T>(root2->m_left->m_info);
		allocate_help(root1->m_left, root2->m_left);
	}
	if (root2->has_right()) {
		root1->m_right = new BinaryTree::Node<T>(root2->m_right->m_info);
		allocate_help(root1->m_right, root2->m_right);
	}
}

template <typename T>
void SearchTree<T>::deallocate(BinaryTree::Node<T>* root) {
	if (root == nullptr) {
		return;
	}
	BinaryTree::Node<T>* left = root->m_left;
	BinaryTree::Node<T>* right = root->m_right;
	delete root;
	if (left != nullptr) {
		deallocate(left);
	}
	if (right != nullptr) {
		deallocate(right);
	}
}

template <typename T>
BinaryTree::Node<T>* SearchTree<T>::find_father(const T& element) {
	if (m_root == nullptr) {
		return nullptr;
	}
	BinaryTree::Node<T>* pointer = m_root;
	BinaryTree::Node<T>* pointer1 = m_root;
	while (pointer != nullptr && pointer->m_info != element) {
		pointer1 = pointer;
		if (pointer->m_info > element) {
			pointer = pointer->m_left;
		}
		else {
			pointer = pointer->m_right;
		}
	}
	return (pointer == nullptr) ? nullptr : pointer1;
}