#pragma once

#include <iostream>

class Stack {
public:
	Stack();
	Stack(int, const int*);
	Stack(const Stack&);
	Stack& operator=(const Stack&);
	~Stack();

	int get_size()const { return m_top+1; }
	bool is_empty()const { return m_top < 0; }
	int get_top()const { return m_top; };

	void push(int);
	void pop();

private:
	int m_top;
	int max_size;
	int* m_data;
};