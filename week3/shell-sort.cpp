#include <iostream>
using namespace std;

void ShellSort(int* a, int n) {
	// Pick a gap which is larger than 1, it often equals than n / 2
	// Arrange elements which are spaced apart 'gap' by InsertionSort
	// Reducing gap by a rule (divide 2)
	// When gap is 1, InsertionSort but the array is almost sorted so it's faster than
	// normal insertion sort.
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			int temp = a[i];
			int j;
			for (j = i; j >= gap && a[j - gap] > temp; j -= gap) {
				a[i] = a[j - gap];
			}
			a[j] = temp;
		}
	}
}
