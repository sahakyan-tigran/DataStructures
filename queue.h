#pragma once

class Queue {	
public:
	Queue();
	Queue(const int*,int);	// unnecessary c-tor
	Queue(const Queue&);
	Queue& operator=(const Queue&);
	~Queue();
    
	int size() const;	
	bool is_empty() const { return size() == 0; }	
	int& front() { return m_front; }
	const int& front() const;

	void push(int);
	void pop();

private:
	int m_max_size;
	int m_front;
	int m_rear;
	int* m_data;
};
