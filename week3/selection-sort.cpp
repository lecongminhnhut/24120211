#include <iostream>
using namespace std;
#include <algorithm>
#include "DataGenerator.cpp"

int findmin(int arr[], int low, int n)
{
    int min = low;
    for (int i = low + 1; i < n; i++)
    {
        if (arr[i] < arr[min])
            min = i;
    }
    return min;
}
void Selection_Sort(int arr[], int low, int n)
{
    for (int i = low; i < n; i++)
    {   
        int min = findmin(arr, i, n);
        swap(arr[i], arr[min]);
    }
}


