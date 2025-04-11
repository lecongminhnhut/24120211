#include <iostream>
using namespace std;
//Sử dụng thuật toán linearSearch
int linearSearch(int arr[], int n, int k)
{
   for (int i = 0; i < n; i++) //duyệt mảng
   {
    if (arr[i] == k)
        return i; // trả về vị trí của phần tử vừa tìm được
   }
   return -1; // trường hợp không tìm được phần tử nào hết
}
int main()
{
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]); 
    int k = 5;
    cout << linearSearch(arr, n, k);
    return 0;
}