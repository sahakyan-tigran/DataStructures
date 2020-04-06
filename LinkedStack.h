#pragma once

class LinkedStack {
public:
	struct Node {
		int m_info;
		Node* m_previous;

		Node(int info = 0) : m_info(info) , m_previous(nullptr) {}
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
	};

	LinkedStack();
	LinkedStack(const LinkedStack&);
	LinkedStack& operator=(const LinkedStack&);
	~LinkedStack();

	bool is_empty() const { return m_size == 0; }
	int size() const { return m_size; }
	int& top();
	const int& top() const;
	void push(int);
	void pop();

private:
	void deallocate();

private:
	int m_size;
	Node* m_top;
};