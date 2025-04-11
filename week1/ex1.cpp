#include <iostream>
using namespace std;
// Hàm fibonacci
int fibonacci (int n){
    if (n==0) return 0; // giá trị cơ sở
    if (n==1) return 1; // giá trị cơ sở
    return fibonacci(n-1) + fibonacci(n-2); // gọi đệ quy
}
int main()
{
    int n;
    cin >> n;
for (int i=0; i < n; i++)
{// xuất dãy fibonacci từ 0 tới n-1
   cout << fibonacci(i) << " ";
}
return 0;
}