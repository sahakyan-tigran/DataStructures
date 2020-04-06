#pragma once

class LinkedQueue {
public:
	struct Node {
		int m_info;
		Node* m_next;

		Node(int info = 0) : m_info(info), m_next(nullptr) {}
		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;
	};

	LinkedQueue();
	LinkedQueue(const LinkedQueue&);
	LinkedQueue& operator=(const LinkedQueue&);
	~LinkedQueue();

	bool is_empty() const { return m_size == 0; }
	int size() const { return m_size; }
	int& front();
	const int& front() const;
	void push(int);
	void pop();

private:
	void deallocate();

private:
	int m_size;
	Node* m_front;
	Node* m_rear;
};
