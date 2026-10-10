#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;     
    int j = mid + 1;  
    int k = left;      

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= mid)  temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];


    for (int p = left; p <= right; ++p)
        arr[p] = temp[p];
}


void mergeSort(vector<int>& arr, vector<int>& temp, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, temp, left, mid);
    mergeSort(arr, temp, mid + 1, right);
    merge(arr, temp, left, mid, right);
}


void allDistinct(const vector<vector<int>>& a) {
    int m = a.size();
    if (m == 0) 
        cout << "yes ";
    int n = a[0].size();
    int total = m * n;

    vector<int> arr(total);
    int k = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            arr[k++] = a[i][j];


    vector<int> temp(total);
    mergeSort(arr, temp, 0, total - 1);

    for (int i = 1; i < total; ++i) {
        if (arr[i] == arr[i - 1])
            cout << "no";
    }
    cout << "yes";       
}
