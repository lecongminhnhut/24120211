#include <iostream>
using namespace std;
const int N = 8;
int board[N][N] = {0};
int solutions = 0;
// Hàm kiểm tra vị trí đặt con hậu ở hàng row, cột col có an toàn không (không bị hậu ở các hàng trên tấn công)
bool isSafe(int row, int col)
{
    for (int i=0; i < row; i++)
    {
        if (board[i][col] == 1) // kiểm tra có hậu nào được đặt ở cột col không
            return false;
        if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1) // kiểm tra có hậu nào được đặt ở chéo trái phía trên không
            return false;
        if (col + (row - i) < N && board[i][col + (row - i)] == 1 ) // kiểm tra có hậu nào được đặt ở chéo phải phía trên không
            return false;
        // không kiểm tra các phần tử trên đường chéo và nằm ở phía dưới vì sẽ trùng khi ta tăng i (tức i đi xuống dòng tiếp)    
    }
    return true;
}
void SolveNQueens(int row)
{
    if (row == N)
    {// số dòng đặt được hậu bằng N nghĩa là tồn tại 1 solution
        solutions++;
        return;
    }
    for (int col = 0; col < N; col++)
    {
        if (isSafe(row, col)) // kiểm tra hàng row, cột col có đặt được hậu không
        {
            board[row][col] = 1; // nếu an toàn đặt hậu
            SolveNQueens(row + 1); // gọi đệ quy để đặt hậu ở hàng tiếp theo
            board[row][col] = 0; // nếu bất cứ hàng nào không tồn tại cách đặt hậu thì quay lui, sau khi trở về từ đệ quy gỡ hậu, tiếp tục thử ở cột khác.
        }
    }
}
int main()
{
    SolveNQueens(0);
    cout << solutions << endl;
    return 0;
}