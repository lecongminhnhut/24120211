#include <iostream>
using namespace std;
// Bài toán tháp Hà Nội
void towerOfHaNoi (int n, char from_rod, char to_rod, char aux_rod)
{
    if (n==1)
    {// nếu n=1 chỉ cần chuyển đĩa 1 từ cột nguồn tới cột đích.
        cout << "Move disk 1 from " << from_rod << " to " << to_rod << endl;
        return;
    }
    // gọi đệ quy để chyển n-1 đĩa từ cột nguồn đến cột trung gian bằng cách sử dụng cột đích làm trung gian.
    towerOfHaNoi(n-1, from_rod, aux_rod, to_rod);
    cout << "Move disk " << n << " from " << from_rod << " to " << to_rod << endl;
    // gọi đệ quy để chuyển n-1 đĩa từ cột trung gian đến cột đích (sau khi cột đích đã có đĩa n trước đó) bằng cách sử dụng cột nguồn làm trung gian
    towerOfHaNoi(n-1, aux_rod, to_rod, from_rod);
}
int main()
{
    int n;
    cin >> n;
    towerOfHaNoi(n, 'A', 'C', 'B');// chuyển đĩa từ cột A->C với B là cột trung gian.
    return 0;
}