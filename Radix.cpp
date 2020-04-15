#include "Queue.h"

#include <iostream>

int f(int n, int k) {
	return (n >> k) & 1;
}

void Radix_Sort(int* data, int size) {
	Queue<int> Q[2];
	int p = sizeof(int) * 8;
	for (int i = 0; i < p; ++i) {
		for (int j = 0; j < size; ++j) {
			Q[f(data[j], i)].push(data[j]);
		}
		for (int i = 0, j = 0;j < 2;++j) {
			while (!Q[j].is_empty()) {
				data[i++] = Q[j].front();
				Q[j].pop();
			}
		}
	}
}

int main() {
	int a[8] = { 7,4,3,5,8,0,1,6 };
	Radix_Sort(a, 8);
	for (int i = 0; i < 8; ++i) {
		std::cout << a[i] << std::endl;
	}
}