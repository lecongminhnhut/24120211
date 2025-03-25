#include <iostream>
using namespace std;
//Hàm kiểm tra mảng có được sắp xếp tăng dần hay chưa
bool isSorted(int arr[], int n)
{
    if (n == 0 || n == 1) // mảng không có phần tử nào hoặc chỉ có duy nhất 1 phần tử hiển nhiên là đã được sắp xếp.
        return true; 
    if (arr[0] > arr[1]) // nếu phần tử arr[0] > arr[1] nghĩa là mảng chưa được sắp xếp tăng dần.
        return false;
    return isSorted(arr + 1, n-1); // gọi đệ quy với mảng giảm đi 1 phần tử đầu mảng, nếu đến khi mảng chỉ còn xét với 1 phần thì là mảng đã được sắp xếp.
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (isSorted(arr, n))
        cout << "The array is sorted.\n";
    else 
        cout << "The array is NOT sorted.\n";
    return 0;
}