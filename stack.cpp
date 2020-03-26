#include <iostream>

#include "stack.h"

const int MAX_SIZE = 100;

Stack::Stack() 
	:m_top ( -1)
	,max_size(MAX_SIZE)
	,m_data(nullptr)
{
	m_data = new int [MAX_SIZE];
}
Stack::Stack(int top, const int* data) 
	:m_top(top)
	,max_size((top>MAX_SIZE) ? 2 * top : MAX_SIZE)
	,m_data(nullptr)
{	
	m_data = new int[max_size];
	for (int i = 0;i < m_top + 1;++i) {
		m_data[i] = data[i];
	}
}
Stack::Stack(const Stack& obj) 
	:m_top (obj.m_top)
	,max_size(obj.max_size)
	,m_data(nullptr)
{
	m_data = new int[max_size];
	for (int i = 0;i < m_top + 1;++i) {
		m_data[i] = obj.m_data[i];
	}
}
Stack& Stack::operator=(const Stack& obj)
{
	if (this != &obj) {
		delete[]m_data;
		m_top = obj.m_top;
		max_size = obj.max_size;
		m_data = new int[max_size];
		for (int i = 0;i < m_top + 1;++i)
		{
			m_data[i] = obj.m_data[i];
		}
	}
	return *this;
}
Stack::~Stack() {
	delete[]m_data;
}
void Stack::pop() {
	if (!is_empty()) {
		--m_top;
	}

}
void Stack::push(int value) {
	if (m_top + 1 == max_size) {
		max_size *= 2;
		int* tmp = new int[max_size];
		for (int i = 0;i < m_top + 1;++i) {
			tmp[i] = m_data[i];
		}
		delete[]m_data;
		m_data = tmp;
	}
	m_data[++m_top] = value;
}
