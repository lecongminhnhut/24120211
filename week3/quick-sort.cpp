#include <iostream>
using namespace std;
#include <algorithm>


// Quick sort



int partition(int* a, int left, int right) {
	int pivotIndex = left + rand() % (right - left+1);
	swap(a[pivotIndex],a[right]);
	int pivot = a[right];
	int i = left - 1;
	for (int j = left; j < right; j++) {
		if (a[j] < pivot) {
			// swap them
			i++;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[right]);
	return i + 1;
}// This is a sorting function which can give the position of pivot

void quickSort(int* a, int left, int right) {
	if (left < right) {
		int pivot = partition(a, left, right);
		quickSort(a, left, pivot - 1);
		quickSort(a, pivot + 1, right);
	}
}
