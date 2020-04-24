#include <iostream>

#include <queue>

struct Node {
	Node(int info = 0) : m_info(info), m_left(nullptr), m_right(nullptr), m_father(nullptr) {}
	Node(const Node&) = delete;
	Node& operator=(const Node&) = delete;

	int m_info;
	Node* m_left;
	Node* m_right;
	Node* m_father;
};

namespace tree_r {
	//there are only recursive functions in this namespace(tree_r) 

	int height(Node* root) {
		if (root == nullptr || (root->m_left == nullptr && root->m_right == nullptr)) { return 0; }
		else
		{
			int left = height(root->m_left);
			int right = height(root->m_right);
			if (left > right) { return left + 1; }
			else { return right + 1; }
		}
	}

	int leaves(Node* root) {
		if (root == nullptr) { return 0; }
		if (root->m_left == nullptr && root->m_right == nullptr) { return 1; }
		else { return leaves(root->m_left) + leaves(root->m_right); }
	}

	int find_max(Node* root) {
		if (root->m_left == nullptr && root->m_right == nullptr) { return root->m_info; }
		int result = root->m_info;
		int left = (root->m_left != nullptr) ? find_max(root->m_left) : root->m_info;
		int right = (root->m_right != nullptr) ? find_max(root->m_right) : root->m_info;
		if (left > result) { result = left; }
		if (right > result) { result = right; }
		return result;
	}

	int points(Node* root) {
		if (root == nullptr) { return 0; }
		if (root->m_left == nullptr && root->m_right == nullptr) { return 1; }
		return 1 + points(root->m_left) + points(root->m_right);
	}

	bool is_strict(Node* root) {
		if (root == nullptr) { return false; }
		if (root->m_left == nullptr && root->m_right == nullptr) { return true; }
		return is_strict(root->m_left) && is_strict(root->m_right);
	}

	void straight_traverse(Node* root) {
		if (root == nullptr) {
			return;
		}
		std::cout << root->m_info << std::endl;
		straight_traverse(root->m_left);
		straight_traverse(root->m_right);
	}

	void  symmetrical_traverse(Node* root) {
		if (root == nullptr) {
			return;
		}
		symmetrical_traverse(root->m_left);
		std::cout << root->m_info << std::endl;
		symmetrical_traverse(root->m_right);
	}

	void reverse_traverse(Node* root) {
		if (root == nullptr) {
			return;
		}
		reverse_traverse(root->m_left);
		reverse_traverse(root->m_right);
		std::cout << root->m_info << std::endl;
	}

	void print_i_level(Node* root, int level) {
		if (level == 0) {
			std::cout << root->m_info << std::endl;
			return;
		}
		if (root->m_left != nullptr) {
			print_i_level(root->m_left, level - 1);
		}
		if (root->m_right != nullptr) {
			print_i_level(root->m_right, level - 1);
		}
	}

	void print_by_level(Node* root) {
		if (root == nullptr) {
			return;
		}
		int h{ height(root) }, i{ 0 };
		while (i <= h) {
			print_i_level(root, i);
			++i;
		}
	}
}

namespace tree_i {
	//there are only iterative functions in this namespace(tree_i) 
	
	Node* find_next_straight(Node* n)
	{
		if (n->m_left != nullptr) { return n->m_left; }
		if (n->m_right != nullptr) { return n->m_right; }
		while (n->m_father != nullptr && ((n->m_father->m_right == n) || ((n->m_father->m_left == n ) && (n->m_father->m_right == nullptr)))) {
			n = n->m_father;
		}
		if (n->m_father == nullptr) { return nullptr; }
		return n->m_father->m_right;
	}

	Node* find_next_symmetrical(Node* n) {
		if (n->m_right != nullptr) {
			if (n->m_right->m_left != nullptr) {
				n = n->m_right;
				while (n->m_left != nullptr) {
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

	Node* find_next_reverse(Node* n) {
		if (n->m_father != nullptr) {
			if ((n == n->m_father->m_left) && (n->m_father->m_right != nullptr)) {
				if (n->m_father->m_right->m_left != nullptr) {
					n = n->m_father->m_right;
					while (n->m_left != nullptr) {
						n = n->m_left;
					}
					return n;
				}
				return n->m_father->m_right;
			}
		}
		return n->m_father;
	}

	void straight_traverse(Node* root) {
		if (root == nullptr) { return; }
		std::cout << root->m_info << std::endl;
		Node* tmp = find_next_straight(root);
		while (tmp != nullptr) {
			std::cout << tmp->m_info << std::endl;
			tmp = find_next_straight(tmp);
		}
	}

	void symmetrical_traverse(Node* root) {
		if (root == nullptr) { return; }
		while (root->m_left != nullptr) {
			root = root->m_left;
		}
		std::cout << root->m_info << std::endl;
		Node* tmp = find_next_symmetrical(root);
		while (tmp != nullptr) {
			std::cout << tmp->m_info << std::endl;
			tmp = find_next_symmetrical(tmp);
		}
	}

	void reverse_traverse(Node* root) {
		if (root == nullptr) { return; }
		while (root->m_left != nullptr || root->m_right != nullptr) {
			while (root->m_left != nullptr) {
				root = root->m_left;
			}
			if (root->m_right != nullptr) {
				root = root->m_right;
			}
		}
		std::cout << root->m_info << std::endl;
		Node* tmp = find_next_reverse(root);
		while (tmp != nullptr) {
			std::cout << tmp->m_info << std::endl;
			tmp = find_next_reverse(tmp);
		}
	}

	void print_by_level(Node* root) {
		if (root == nullptr) { return; }
		std::queue<Node*> q;
		q.push(root);
		while (!q.empty()) {
			std::cout << q.front()->m_info;
			if (q.front()->m_left != nullptr) {
				q.push(q.front()->m_left);
			}
			if (q.front()->m_right != nullptr) {
				q.push(q.front()->m_right);
			}
			q.pop();
		}
	}
}

int main() {
	Node* root = new Node(0);
	Node* root1 = new Node(1);
	Node* root2 = new Node(2);
	Node* root3 = new Node(3);
	Node* root4 = new Node(4);
	Node* root5 = new Node(5);
	Node* root6 = new Node(6);
	Node* root7 = new Node(7);
	Node* root8 = new Node(8);
	Node* root9 = new Node(9);
	root->m_left = root1;
	//root1->m_father = root;
	root1->m_right = root5;
	root->m_right = root4;
	root1->m_left = root2;
	root2->m_left = root3;
	root1->m_father = root;
	root5->m_father = root1;
	root4->m_father = root;
	root2->m_father = root1;
	root3->m_father = root2;
/*	root3->m_right = root9;
	root9->m_father = root3;
	root9->m_right = root8;
	root8->m_father = root9;
	root9->m_left = root7;
	root7->m_father = root9;
	//root5->m_right = root6;
	//root6->m_father = root5;
	//root3->m_right = root9;
	//root9->m_father = root3;
	//root9->m_left = root8;
	//root9->m_right = root7;
	//root8->m_father = root9;
	//root7->m_father = root9;*/
	root4->m_right = root7;
	root7->m_father = root4;
	//tree_r::reverse_traverse(root);
	tree_r::print_by_level(root);
	return 0;

}