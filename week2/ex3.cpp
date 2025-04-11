#include <iostream>
using namespace std;
int findMin(int arr[],int left, int right)
{
    int mid = 0;
    while (left < right)
    { 
        mid = (left + right) / 2;
        if (arr[mid] < arr[right])
            {   
                right = mid; // khi mà arr[mid] < arr[right] thì có nghĩa phần tử nhỏ nhất đang ở bên trái mid hoặc là chính mid
            }
        else 
            {
                left = mid + 1;// ngược lại arr[mid]>= right thì có nghĩa phần tử nhỏ nhất đang ở bên phải mid, nếu mid nhỏ nhất thì right cũng là nhỏ nhất
            }
    }
    return arr[left];
}
int main()
{
    int arr[] = {3,4,5,1,2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i=0;
    cout << findMin(arr, 0, n-1,i);
    return 0; 
}