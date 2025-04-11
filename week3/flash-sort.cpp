#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void flashSort(int arr[], int n) {
    if (n == 0) return;

    // Bước 1: Tìm min, max
    int minVal = arr[0], maxVal = arr[0], maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) {
            maxVal = arr[i];
            maxIndex = i;
        }
    }

    if (minVal == maxVal) return; // Đã sắp xếp

    // Bước 2: Tạo mảng lớp tĩnh
    int m = int(0.45 * n); // Số lớp
    int L[n] = {0};      // Mảng lớp tĩnh

    // Bước 3: Phân lớp
    for (int i = 0; i < n; i++) {
        int k = int((double)(m - 1) * (arr[i] - minVal) / (maxVal - minVal));
        L[k]++;
    }

    // Bước 4: Chuyển đổi thành vị trí bắt đầu mỗi lớp
    for (int i = 1; i < m; i++) {
        L[i] += L[i - 1];
    }

    // Bước 5: Đưa max về đầu
    swap(arr[maxIndex], arr[0]);

    // Bước 6: Phân phối
    int move = 0, j = 0, k = m - 1, flash;
    while (move < n - 1) {
        while (j >= L[k]) {
            j++;
            k = int((double)(m - 1) * (arr[j] - minVal) / (maxVal - minVal));
        }

        flash = arr[j];
        while (j != L[k]) {
            k = int((double)(m - 1) * (flash - minVal) / (maxVal - minVal));
            int temp = arr[--L[k]];
            arr[L[k]] = flash;
            flash = temp;
            move++;
        }
    }

    // Bước 7: Sắp xếp tinh chỉnh bằng insertion sort
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
