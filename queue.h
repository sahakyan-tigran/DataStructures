#pragma once

#include <iostream>

class queue {
public:
	queue();
	queue(const int*,int);
	queue(const queue&);
	queue& operator=(const queue&);
	~queue();
    
	int size()const;
	bool is_empty() const { return size()== 0; }
	int front() const { return m_front; }

	void push(int);
	void pop();

private:
	int max_size;
	int m_front;
	int m_rear;
	int* m_data;





};