#include <iostream>
#include <algorithm>
using namespace std;
int Min_Len(int arr[], int n, int target)
{
    int left = 0, sum = 0;// giữ vị trí đầu
    int l = n + 1; // gán độ dài bằng n+1 lớn hơn độ dài mảng
    for (int right = 0; right < n; right++)
    {
        sum += arr[right];
        while (sum >= target) // nếu sum lớn hơn hoặc bằng giá trị yêu cầu thì lấy độ dài nhỏ nhất mới, bỏ đi phần tử left để tìm dộ dài nhỏ hơn nếu tồn tại
        {
            l = min(l, right - left + 1);
            sum -= arr[left];
            left++;
        }
    } 
    if (l > n)
        return 0;
    return l;
}
int main()
{
    int nums[] = {2, 3, 1, 2, 4, 3};
    int n = sizeof(nums) / sizeof(nums[0]);
    int target = 7;
    cout << Min_Len(nums, n, target);
    return 0;
}