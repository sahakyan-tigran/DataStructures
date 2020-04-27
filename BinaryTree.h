#pragma once

#include <stack>

#include <iostream>

#include <queue>

template <typename T>
struct Node {
	Node(const T& info = T()) : m_info(info), m_left(nullptr), m_right(nullptr) {}
	Node(const Node<T>&) = delete;
	Node<T>& operator=(const Node<T>&) = delete;
	virtual ~Node() {};

	bool is_leaf() const { return ((m_left == nullptr) && (m_right == nullptr)); }
	bool has_left() const { return (m_left != nullptr); }
	bool has_right() const { return (m_right != nullptr); }
	bool has_both() const { return ((m_left != nullptr) && (m_right != nullptr)); }

	T m_info;
	Node<T>* m_left;
	Node<T>* m_right;
};

template <typename T>
struct ExtendedNode : public Node<T> {
	ExtendedNode(const T& info = T()) : Node(info), m_father(nullptr) {}
	Node<T>* m_father;
};

template <typename T>
using FuncNode = void(*)(Node<T>*);

template <typename T>
using FuncExtendedNode = void(*)(ExtendedNode<T>*);

namespace tree_r {
	//there are only recursive functions in this namespace(tree_r) 

	template <typename T>
	int height(Node<T>* root) {
		if (root == nullptr || root->is_leaf()) { return 0; }
		else
		{
			int left = height(root->m_left);
			int right = height(root->m_right);
			if (left > right) { return left + 1; }
			else { return right + 1; }
		}
	}

	template <typename T>
	int leaves(Node<T>* root) {
		if (root == nullptr) { return 0; }
		if (root->is_leaf()) { return 1; }
		else { return leaves(root->m_left) + leaves(root->m_right); }
	}

	template <typename T>
	const T& find_max(Node<T>* root) {
		if (root->is_leaf()) { return root->m_info; }
		T result = root->m_info;
		T left = (root->has_left()) ? find_max(root->m_left) : root->m_info;
		T right = (root->has_right()) ? find_max(root->m_right) : root->m_info;
		if (left > result) { result = left; }
		if (right > result) { result = right; }
		return result;
	}

	template <typename T>
	int points(Node<T>* root) {
		if (root == nullptr) { return 0; }
		if (root->is_leaf()) { return 1; }
		return 1 + points(root->m_left) + points(root->m_right);
	}

	template <typename T>
	bool is_strict(Node<T>* root) {
		if (root == nullptr) { return false; }
		if (root->is_leaf()) { return true; }
		return is_strict(root->m_left) && is_strict(root->m_right);
	}

	template <typename T>
	void straight_traverse(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		visit(root);
		straight_traverse(root->m_left, visit);
		straight_traverse(root->m_right, visit);
	}

	template <typename T>
	void  symmetrical_traverse(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		symmetrical_traverse(root->m_left, visit);
		visit(root);
		symmetrical_traverse(root->m_right, visit);
	}

	template <typename T>
	void reverse_traverse(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		reverse_traverse(root->m_left, visit);
		reverse_traverse(root->m_right, visit);
		visit(root);
	}

	template <typename T>
	void print_i_level(Node<T>* root, int level, FuncNode<T> visit) {
		if (level == 0) {
			visit(root);
			return;
		}
		if (root->m_left != nullptr) {
			print_i_level(root->m_left, level - 1, visit);
		}
		if (root->m_right != nullptr) {
			print_i_level(root->m_right, level - 1), visit;
		}
	}

	template <typename T>
	void print_by_level(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) {
			return;
		}
		int h{ height(root) }, i{ 0 };
		while (i <= h) {
			print_i_level(root, i, visit);
			++i;
		}
	}
}

namespace tree_i {
	//there are only iterative functions in this namespace(tree_i) 

	template <typename T>
	ExtendedNode<T>* find_next_straight(ExtendedNode<T>* n)
	{
		if (n->has_left()) { return n->m_left; }
		if (n->has_right()) { return n->m_right; }
		while (n->m_father != nullptr && ((n->m_father->m_right == n) || ((n->m_father->m_left == n) && (n->m_father->m_right == nullptr)))) {
			n = n->m_father;
		}
		if (n->m_father == nullptr) { return nullptr; }
		return n->m_father->m_right;
	}

	template <typename T>
	ExtendedNode<T>* find_next_symmetrical(ExtendedNode<T>* n) {
		if (n->has_right()) {
			if (n->m_right->has_left()) {
				n = n->m_right;
				while (n->has_left()) {
					n = n->m_left;
				}
				return n;
			}
			return n->m_right;
		}
		while (n == n->m_father->m_right) {
			n = n->m_father;
		}
		return n->m_father;
	}

	template <typename T>
	ExtendedNode<T>* find_next_reverse(ExtendedNode<T>* n) {
		if (n->m_father != nullptr) {
			if ((n == n->m_father->m_left) && (n->m_father->m_right != nullptr)) {
				if (n->m_father->m_right->m_left != nullptr) {
					n = n->m_father->m_right;
					while (n->has_left()) {
						n = n->m_left;
					}
					return n;
				}
				return n->m_father->m_right;
			}
		}
		return n->m_father;
	}

	template <typename T>
	void straight_traverse(ExtendedNode<T>* root, FuncExtendedNode<T> visit) {
		if (root == nullptr) { return; }
		visit(root);
		ExtendedNode<T>* tmp = find_next_straight(root);
		while (tmp != nullptr) {
			visit(tmp);
			tmp = find_next_straight(tmp);
		}
	}

	template <typename T>
	void symmetrical_traverse(ExtendedNode<T>* root, FuncExtendedNode<T> visit) {
		if (root == nullptr) { return; }
		while (root->has_left()) {
			root = root->m_left;
		}
		visit(root);
		ExtendedNode<T>* tmp = find_next_symmetrical(root);
		while (tmp != nullptr) {
			visit(tmp);
			tmp = find_next_symmetrical(tmp);
		}
	}

	template <typename T>
	void reverse_traverse(ExtendedNode<T>* root, FuncExtendedNode<T> visit) {
		if (root == nullptr) { return; }
		while (root->m_left != nullptr || root->m_right != nullptr) {
			while (root->m_left != nullptr) {
				root = root->m_left;
			}
			if (root->m_right != nullptr) {
				root = root->m_right;
			}
		}
		visit(root);
		ExtendedNode<T>* tmp = find_next_reverse(root);
		while (tmp != nullptr) {
			visit(tmp);
			tmp = find_next_reverse(tmp);
		}
	}

	template <typename T>
	void print_by_level(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) { return; }
		std::queue<Node<T>*> q;
		q.push(root);
		while (!q.empty()) {
			visit(q.front());
			if (q.front()->m_left != nullptr) {
				q.push(q.front()->m_left);
			}
			if (q.front()->m_right != nullptr) {
				q.push(q.front()->m_right);
			}
			q.pop();
		}
	}

	template <typename T>
	void straight_with_stack(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) { return; }
		std::stack<Node<T>*> s;
		s.push(root);
		while (!s.empty()) {
			visit(s.top());
			Node<T>* tmp = s.top();
			s.pop();
			if (tmp->has_right()) {
				s.push(tmp->m_right);
			}
			if (tmp->has_left()) {
				s.push(tmp->m_left);
			}
		}
	}

	template <typename T>
	void symmetrical_with_stack(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) { return; }
		std::stack<Node<T>*> s;
		Node<T>* tmp = root;
		while (tmp != nullptr || !s.empty())
		{
			while (tmp != nullptr)
			{
				s.push(tmp);
				tmp = tmp->m_left;
			}
			tmp = s.top();
			s.pop();
			visit(tmp);
			tmp = tmp->m_right;
		}
	}

	template <typename T>
	void reverse_with_stack(Node<T>* root, FuncNode<T> visit) {
		if (root == nullptr) { return; }
		std::stack<Node<T>*> s1, s2;
		s1.push(root);
		Node<T>* tmp;
		while (!s1.empty()) {
			tmp = s1.top();
			s2.push(tmp);
			s1.pop();
			if (tmp->has_left()) {
				s1.push(tmp->m_left);
			}
			if (tmp->has_right()) {
				s1.push(tmp->m_right);
			}
		}
		while (!s2.empty()) {
			visit(s2.top());
			s2.pop();
		}
	}
}

void f(Node<int>* root) {
	std::cout << root->m_info << ' ';
}

int main() {
	Node<int>* root = new Node<int>(0);
	Node<int>* root1 = new Node<int>(1);
	Node<int>* root2 = new Node<int>(2);
	Node<int>* root3 = new Node<int>(3);
	Node<int>* root4 = new Node<int>(4);
	Node<int>* root5 = new Node<int>(5);
	Node<int>* root6 = new Node<int>(6);
	Node<int>* root7 = new Node<int>(7);
	Node<int>* root8 = new Node<int>(8);
	Node<int>* root9 = new Node<int>(9);
	root->m_left = root1;
	root->m_right = root4;
	root1->m_left = root2;
	root2->m_left = root3;
	root1->m_right = root5;
	root3->m_right = root7;
	root7->m_left = root8;
	root8->m_left = root9;
	tree_r::reverse_traverse(root, f);
	std::cout << std::endl;
	tree_i::reverse_with_stack(root, f);
	return 0;
}