#pragma once

#include <iostream>	// unnecessary include, remove

class queue {	// let's name type names with uppercase
public:
	queue();
	queue(const int*,int);	// unnecessary c-tor
	queue(const queue&);
	queue& operator=(const queue&);
	~queue();
    
	int size()const;	// add space befor "const"
	bool is_empty() const { return size()== 0; }	// add space
	int front() const { return m_front; }	// The same comment for "front" function. See top() for stack

	void push(int);
	void pop();

private:
	int max_size;	// the same comment for naming. see stack
	int m_front;
	int m_rear;
	int* m_data;
	// so many unnecessary lines




};
