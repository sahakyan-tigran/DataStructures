#pragma once

class Stack {
public:
	Stack();
	Stack(const Stack&);
	Stack& operator=(const Stack&);
	~Stack();

	int size() const { return m_top + 1; }	 
	bool is_empty() const { return m_top == -1; }	
	int& top();
	const int& top() const;

	void push(int);
	void pop();

private:
	int m_top;
	int m_max_size;	
	int* m_data;
};

