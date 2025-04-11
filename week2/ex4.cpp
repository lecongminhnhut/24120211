#include <iostream>
using namespace std;
// chia khối lượng cho các ngày 
int Ship(int arr[], int n, int days, int result, int day[])
{
    int count = 0; int ndays = 1;
    for (int i = 0; i < days ; i++ )
    {
        for (int j = count; j < n; j++)
        {
            if (day[i] <= result - arr[j]) // nếu khối lượng vận chuyển ngày thứ i + cho thêm khối lượng thứ j bé hơn khối lượng có thể thì cộng vào
                day[i]  = day[i] + arr[j];
            else //ngược lại thì gán count bằng j để giữ vị trí đầu mà chưa vận chuyển
                {
                    count = j;
                    ndays++; // số ngày đã sử dụng
                    break;
                }
        }
    }
    return ndays;
}
int Ship_n_days(int arr[], int n, int days)
{
    int sum = 0;
    for (int i = 0; i < n ; i++)
    {
        sum  = sum + arr[i]; 
    }
    int result = sum / days; // chia đều khối lượng cho các ngày
    int day[days] = {0};
    int ndays = Ship(arr, n, days, result, day); // gọi hàm ship để lấy số ngày đã dùng
    while (ndays != days) // nếu số ngày đã dùng khác (lớn hơn) số ngày cho phép thì tăng số ngày cho phép và gọi lại hàm ship để kiểm tra
    {
       int day[days] = {0};
        result++;
        ndays = Ship(arr, n, days, result, day);
    }
    return result;
}
int main()
{
    int n, d;
    cout << "n=";
    cin >> n;
    cout << "days=";
    cin >> d;
    int weight[n];
    for (int i = 0; i < n; i++)
    {
        cin >> weight[i];
    }
    cout << endl << Ship_n_days(weight, n, d);
    return 0;
}