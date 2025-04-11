#include <iostream>
using namespace std;

// Counting sort
void countingSort(int* arr, int n) {
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > max)
			max = arr[i];
	} // Tim max

	int* count = new int[max + 1] {0};

	for (int i = 0; i < n; i++) {
		count[arr[i]]++;
	} // Count the number of each value in array (count[i] is the number of value i)

	int index = 0;
	for (int i = 0; i <= max; i++) {
		while (count[i] > 0) {
			arr[index++] = i;
			count[i]--;
		}
		// Run from 0, if count[i] is bigger than 0, assign value i to 
	}

	delete[] count;
}
