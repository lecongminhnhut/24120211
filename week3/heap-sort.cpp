#include <iostream>
using namespace std;
#include <algorithm>
//
void heapify(int* a, int n, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && a[left] > a[largest])
		largest = left;

	if (right < n && a[right] > a[largest])
		largest = right;

	if (largest != i) {
		swap(a[i], a[largest]);
		heapify(a, n, largest);
	}
}

void HeapSort(int* a, int n) {
	//dem = 0;
	for (int i = n / 2; i >= 0; i--) heapify(a, n, i);
	// Heapify all roots

	for (int i = n - 1; i > 0; i--) {
		//swap(a[i], a[0]);
		int temp = a[i];
		a[i] = a[0];
		a[0] = temp;
		// Move the largest element to the end
		heapify(a, i, 0); // Heapify the reduced heap
	}
}


