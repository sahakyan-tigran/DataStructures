#pragma once

#include <iostream>	// unnecessary include, remove

class Stack {
public:
	Stack();
	Stack(int, const int*);	// unnecessary c-tor
	Stack(const Stack&);
	Stack& operator=(const Stack&);
	~Stack();

	int get_size()const { return m_top+1; }	// add spaces between operands of "+", before "const". name the function "size"
	bool is_empty()const { return m_top < 0; }	// return m_top == -1
	int get_top()const { return m_top; };	// remove ";", should return m_data[m_top], there must be a check if the stack is not empty
						// name the function "top"
						// top() shoud return value "int&" in order to change the element on top of the stack
						// also add top() function for constant objects

	void push(int);
	void pop();

private:
	int m_top;
	int max_size;	// use the same naming (maybe "m_max_size")
	int* m_data;
};
