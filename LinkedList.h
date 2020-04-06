#pragma once

class LinkedList {
	struct Node {
		int m_info;
		Node* m_previous;
		Node* m_next;

		Node(int info = 0) : m_info(info) , m_previous(nullptr) , m_next(nullptr) {}
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
	};

	LinkedList();
	LinkedList(int, int*);
	LinkedList(const LinkedList&);
	LinkedList& operator=(const LinkedList&);
	~LinkedList();

	bool is_empty() const { return m_size == 0; }
	int size() const { return m_size; }
	void insert(int , int);
	void remove(int);

private:
	void deallocate();

private:
	int m_size;
	Node* m_head;
};
