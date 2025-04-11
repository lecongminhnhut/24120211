#include <iostream>
using namespace std;
int exist_two_numbers_equals_target(int arr[], int n, int target)
{
    int left = 0;
    int right = n-1;
    // sử dụng hai vị trí left và right
    while (left < right)
    {
        if (left + right < target)
        {
            left++;// tăng left để tăng sum nếu sum < target vì mảng đã được sắp xếp
        }
        else 
        {
        if (left + right > target)
        {
            right--;// giảm right để giảm sum nếu sum > target vì mảng đã được sắp xếp
        }
        else
            return 1; // sum = target tức tìm được
        }
    }
    return 0; // không tìm được
}
int main()
{
    int nums[] = {1, 2, 3, 4, 6};
    int n = sizeof(nums) / sizeof(nums[0]);
    int target = 5;
    if (exist_two_numbers_equals_target(nums, n, target) == 1)
    {
        cout << "YES";
    }
    else cout << "NOT EXIST";
    return 0;
}