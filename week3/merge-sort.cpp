#include <iostream>
using namespace std;
#include <algorithm>

void merge(int arr[], int left, int mid, int right)
{
    int i = left; 
    int j = mid + 1;
    int k = 0; 
    int temp[right - left + 1];
    while (i <= mid && j <= right)
    {   
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }
    while (j <= right)
    {
        temp[k++] = arr[j++];
    }
    for (int x = 0; x < k; x++)
    {
        arr[left + x] = temp[x];
    }
}
void Merge_sort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left)/2;
        Merge_sort(arr, left, mid);
        Merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
