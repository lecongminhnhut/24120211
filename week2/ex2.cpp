#include <iostream>
using namespace std;
// sử dụng thuật toán sentinelLinearSearch
int sentinelLinearSearch (int arr[], int n, int k)
{
    // giữ lại giá trị của phần tử cuối
    int last = arr[n-1];
    // đặt khóa ở vị trí cuối
    arr[n-1] = k;
    int i = 0;
    // tăng i cho đến khi nào gặp k
    while (arr[i] != k)
    {
        i++;
    }
    // trả lại giá trị cho phần tử cuối
    arr[n-1] = last;
    // nếu i tìm được không phải vị trí cuối, hoặc là vị trí cuối và phần tử đó bằng k thì trả về i 
    if (i < n-1 || arr[n-1] == k)
        return i;
    return -1; // trường hợp không tìm được
}
int main()
{
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 5;
    cout << sentinelLinearSearch(arr, n, k);
    return 0;
}