#pragma once

#include "BinaryTree.h"

#include <stack>

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

	const BinaryTree::Node<T>* str_first() const { return m_root; }
	void str_next(std::stack<const BinaryTree::Node<T>*>&) const;

private:
	void allocate(const SearchTree<T>&);
	void allocate_help(BinaryTree::Node<T>*, BinaryTree::Node<T>*);
	void deallocate(BinaryTree::Node<T>*);

	BinaryTree::Node<T>* find_father(const T&);
	BinaryTree::Node<T>* next(BinaryTree::Node<T>*);
	BinaryTree::Node<T>* child_search(BinaryTree::Node<T>*, const T&);
	void delete_node(BinaryTree::Node<T>*, BinaryTree::Node<T>*);

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
	BinaryTree::Node<T>* child = child_search(father, element);
	if (child == nullptr) {
		return;
	}
	if (child->has_both()) {
		father = next(child);
		child = child_search(father, element);
	}
	delete_node(father, child);
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

template <typename T>
BinaryTree::Node<T>* SearchTree<T>::next(BinaryTree::Node<T>* current) {
	BinaryTree::Node<T>* to_remove = current;
	BinaryTree::Node<T>* curr_father = current;
	current = current->m_right;
	while (current->has_left()) {
		curr_father = current;
		current = current->m_left;
	}
	std::swap(current->m_info, to_remove->m_info);
	return curr_father;
}

template <typename T>
BinaryTree::Node<T>* SearchTree<T>::child_search(BinaryTree::Node<T>* father, const T& element) {
	if (father == nullptr) { return nullptr; }
	if (father == m_root && (father->is_leaf() || father->m_info == element)) { return father; }
	if (father->has_left() && father->m_left->m_info == element) { return father->m_left; }
	return father->m_right;
}

template <typename T>
void SearchTree<T>::delete_node(BinaryTree::Node<T>* father, BinaryTree::Node<T>* child) {
	if (child->is_leaf()) {
		if (child == m_root) {
			m_root = nullptr;
			delete child;
			return;
		}
		if (child == father->m_left) {
			father->m_left = nullptr;
		}
		if (child == father->m_right) {
			father->m_right = nullptr;
		}
	}
	else {
		if (child == m_root) {
			m_root = (m_root->has_left()) ? m_root->m_left : m_root->m_right;
			delete child;
			return;
		}
		if (father->m_left == child) {
			father->m_left = (child->has_left()) ? child->m_left : child->m_right;
		}
		if (father->m_right == child) {
			father->m_right = (child->has_left()) ? child->m_left : child->m_right;
		}
	}
	delete child;
}

template <typename T>
void SearchTree<T>::str_next(std::stack<const BinaryTree::Node<T>*>& s) const {
	const BinaryTree::Node<T>* tmp = s.top();
	s.pop();
	if (tmp->has_right()) {
		s.push(tmp->m_right);
	}
	if (tmp->has_left()) {
		s.push(tmp->m_left);
	}
}

