#include <iostream>
using namespace std;
//Hàm tạo các chuỗi bit có độ dài n
void generateBinaryStrings(int n, string str)
{
    if (str.length() == n)
    {// nếu độ dài chuỗi bằng n thì in ra chuỗi
        cout << str << endl;
        return;
    }
    /*gọi đệ quy để thêm 0 hoặc 1 vào chuỗi*/
    generateBinaryStrings(n, str + "0");
    generateBinaryStrings(n, str + "1");
}
int main()
{
    int n;
    cin >> n;
    generateBinaryStrings(n, "");
    return 0;
}