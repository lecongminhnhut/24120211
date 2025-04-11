#include <iostream>
using namespace std;
#include <algorithm>

void Shaker_sort(int arr[], int n)
{
    int left = 0;
    int right = n - 1;
    while (left < right) {
        // Di chuyển từ trái sang phải
        for (int i = left; i < right; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
            }
        }
        right--;

        // Di chuyển từ phải sang trái
        for (int i = right; i > left; --i) {
            if (arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);
            }
        }
        left++;
    }
}
