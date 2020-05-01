#pragma once

#include "HeapTree.h"

template <typename T>
void HeapSort(T* data, int size) {
	HeapTree<T> h;
	for (int i = 0; i < size; ++i) {
		h.insert(data[i]);
	}
	for (int i = size - 1; i >= 0; --i) {
		data[i] = h.max_value();
		h.remove();
	}
}
