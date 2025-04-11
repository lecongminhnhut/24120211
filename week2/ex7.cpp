#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
void Triplets(int arr[], int n)
{   
    sort(arr, arr + n); // sắp xếp mảng để có thể làm tương tự ex6
    for (int i=0; i < n-2; i++) // i chỉ có thể đến n-3 vì để không trùng nhau ta chừa ít nhất 2 vị trí cho j,k
    {
        if (i > 0 && arr[i] == arr[i-1]) continue; // bỏ đi các giá trị trùng để không bị xuất trùng nhiều lần
        int j = i + 1;
        int k = n - 1;
        while (j < k)
        {
            int sum = arr[i] + arr[j] + arr[k];
            if (sum == 0)
            {
                cout << "[" << arr[i] << setw(1) << "," << arr[j] << setw(1) << "," << arr[k] << setw(1) << "]" << endl;
                while (j < k && arr[j] == arr[j+1])
                {
                    j++; //bỏ đi các giá trị trùng để không bị xuất trùng nhiều lần
                }
                while (j < k && arr[k] == arr[k-1])
                {
                    k--; //bỏ đi các giá trị trùng để không bị xuất trùng nhiều lần
                }
                j++;
                k--;
            }
            if (sum < 0) 
            {
                j++; // tăng j để tăng sum nếu sum < 0 vì mảng đã được sắp xếp
            }
            if (sum > 0) 
            {
                k--;// giảm k để giảm sum nếu sum > 0 vì mảng đã được sắp xếp
            }
        }
    }
}

int main()
{
    int nums[] = {-1, 0, 1, 2, -1, 4};
    int n = sizeof(nums) / sizeof(nums[0]);
    Triplets(nums, n);
    return 0;
}