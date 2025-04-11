#include <iostream>
using namespace std;
//Insertion Sort
void InsertionSort(int* a, int n) {
	// Run from i = 0 to n -1
	// Use invarible loop, when i = j, the invarible loop is from 0 to j - 1. (sorted)
	for (int i = 0; i < n; i++) {
		int j = i - 1;
		int temp = a[i];
		while (j >= 0 && a[j] > temp) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = temp;
		
	}
}
