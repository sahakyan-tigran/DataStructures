#include "stack.h"

const int MAX_SIZE = 100;

Stack::Stack() 
	: m_top(-1)	
	, m_max_size(MAX_SIZE)
	, m_data(nullptr)
{
	m_data = new int [MAX_SIZE]{};	
}	

Stack::Stack(const Stack& obj) 
	: m_top (obj.m_top)
	, m_max_size(obj.m_max_size)
	, m_data(nullptr)
{
	m_data = new int[m_max_size]{};
	for (int i = 0; i < m_top + 1; ++i) {	
		m_data[i] = obj.m_data[i];
	}
}	

Stack& Stack::operator=(const Stack& obj)
{
	if (this != &obj) {
		delete[]m_data;
		m_top = obj.m_top;
		m_max_size = obj.m_max_size;
		m_data = new int[m_max_size]{};
		for (int i = 0; i < m_top + 1; ++i)	
		{
			m_data[i] = obj.m_data[i];
		}
	}
	return *this;
}	

Stack::~Stack() {
	delete[]m_data;
}	


int& Stack::top() { 
	if(!is_empty()) {
	return m_data[m_top];
}
const int& Stack::top() const {
	if(!is_empty()) {
	return m_data[m_top];
}

void Stack::pop() {
	if (!is_empty()) {
		--m_top;
	}

}	
	
void Stack::push(int value) {
	if (m_top + 1 == m_max_size) {
		m_max_size *= 2;
		int* tmp = new int[m_max_size];
		for (int i = 0; i < m_top + 1; ++i) {	
			tmp[i] = m_data[i];
		}
		delete[]m_data;
		m_data = tmp;
	}
	m_data[++m_top] = value;
}
	
	
	
	
