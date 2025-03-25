#include <iostream>
using namespace std;
//Hàm tính giai thừa
int factorial(int n){
    if (n==0) return 1;// giá trị cơ sở
    if (n==1) return 1;// giá trị cơ sở
    return factorial(n-1)*n;// gọi đệ quy hàm tính giai thừa
}
int main()
{
    int n;
    cin >> n;
    cout << factorial(n);
    return 0;
}