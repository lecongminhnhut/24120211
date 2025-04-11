#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "sort.cpp"
using namespace std;
void sort_array(int arr[], int n, const string& sort_name)
{
    if (sort_name == "buble-sort") 
    {
        Buble_sort(arr, n);
    }
    else if (sort_name == "counting-sort")
    {
        countingSort(arr, n);
    }
    else if (sort_name == "flash-sort")
    {
        flashSort(arr, n);
    }
    else if (sort_name == "heap-sort")
    {
        HeapSort(arr, n);
    }
    else if (sort_name == "insertion-sort")
    {
        InsertionSort(arr, n);
    }
    else if (sort_name == "merge-sort")
    {
        Merge_sort(arr,0, n-1);
    }
    else if (sort_name == "quick-sort")
    {
        quickSort(arr, 0, n-1);
    }
    else if (sort_name == "radix-sort")
    {
        radix_sort(arr, n);
    }
    else if (sort_name == "selection-sort")
    {
        Selection_Sort(arr, 0, n);
    }
    else if (sort_name == "shaker-sort")
    {
        Shaker_sort(arr, n);
    }
    else if (sort_name == "shell-sort")
    {
        ShellSort(arr, n);
    }
    else 
    {
        cerr << "Unknown algorithm: " << sort_name << endl;
        exit(1);
    }
}
int main(int argc, char* argv[])
{
//nhap dung cau truc 
    if (argc != 7) {
        cerr << "Usage: " << argv[0] << " -a <algorithm> -i <input_file> -o <output_file>\n";
        return 1;
    }
//khai bao cac bien tham so 
    string algorithm, inputFileName, outputFileName;
//Doc cac tham so dong lenh
    for (int i = 1; i < argc; i += 2) {
        string flag = argv[i];
        if (flag == "-a") algorithm = argv[i + 1];
        else if (flag == "-i") inputFileName = argv[i + 1];
        else if (flag == "-o") outputFileName = argv[i + 1];
        else {
            cerr << "Invalid option: " << flag << endl;
            return 1;
        }
}
// Input File
ifstream inputFile(inputFileName);
    if (!inputFile) {
        cerr << "Can't open input file.\n";
        return 1;
    }

    int n;
    inputFile >> n;
    int arr[n];
    for (int i = 0; i < n; ++i) {
        inputFile >> arr[i];
    }
    inputFile.close();
// Sort
sort_array(arr, n, algorithm);
//Output
ofstream outputFile(outputFileName);
    if (!outputFile) {
        cerr << "Can't open output file.\n";
        return 1;
    }

    outputFile << n << endl;
    for (int i = 0; i < n; ++i) {
        outputFile << arr[i] << " ";
    }
    outputFile << endl;
    outputFile.close();
return 0;
}