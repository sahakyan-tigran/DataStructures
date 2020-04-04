#pragma once

class Queue {
public:
	Queue();
	Queue(const Queue&);
	Queue& operator=(const Queue&);
	~Queue();

	int size() const { return m_size; }
	bool is_empty() const { return m_size == 0; }
	int& front();
	const int& front() const;

	void push(int);
	void pop();

private:
	void resize();

private:
	int m_size;
	int m_max_size;
	int m_front;
	int m_rear;
	int* m_data;
};
