#include <iostream>	// unnecessary include, remove

#include "stack.h"

const int MAX_SIZE = 100;

Stack::Stack() 
	:m_top ( -1)	// add spaces after ":", "," and remove spaces befor and after "(" ")"
	,max_size(MAX_SIZE)
	,m_data(nullptr)
{
	m_data = new int [MAX_SIZE];	// add "{}" on every "new"
}	// add new line
Stack::Stack(int top, const int* data) 
	:m_top(top)
	,max_size((top>MAX_SIZE) ? 2 * top : MAX_SIZE)
	,m_data(nullptr)
{	
	m_data = new int[max_size];
	for (int i = 0;i < m_top + 1;++i) {
		m_data[i] = data[i];
	}
}	// remove the function
Stack::Stack(const Stack& obj) 
	:m_top (obj.m_top)
	,max_size(obj.max_size)
	,m_data(nullptr)
{
	m_data = new int[max_size];
	for (int i = 0;i < m_top + 1;++i) {	// add spaces
		m_data[i] = obj.m_data[i];
	}
}	// add new line
Stack& Stack::operator=(const Stack& obj)
{
	if (this != &obj) {
		delete[]m_data;
		m_top = obj.m_top;
		max_size = obj.max_size;
		m_data = new int[max_size];
		for (int i = 0;i < m_top + 1;++i)	// add spaces
		{
			m_data[i] = obj.m_data[i];
		}
	}
	return *this;
}	// add new line
Stack::~Stack() {
	delete[]m_data;
}	// add new line
void Stack::pop() {
	if (!is_empty()) {
		--m_top;
	}

}	// add new line
void Stack::push(int value) {
	if (m_top + 1 == max_size) {
		max_size *= 2;
		int* tmp = new int[max_size];
		for (int i = 0;i < m_top + 1;++i) {	// add spaces
			tmp[i] = m_data[i];
		}
		delete[]m_data;
		m_data = tmp;
	}
	m_data[++m_top] = value;
}	// add new line
