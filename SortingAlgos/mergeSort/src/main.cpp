/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 *
 *  Like QuickSort, Merge Sort is a Divide and Conquer algorithm. It divides input array in two halves, calls itself for the two halves and then merges the two sorted halves. The merge() function is
 *  used for merging two halves. The merge(arr, l, m, r) is key process that assumes that arr[l..m] and arr[m+1..r] are sorted and merges the two sorted sub-arrays into one.
 *
 *
 *
 *
 */

#include <iostream>
using namespace std;

void printArray(int arr[], int n);

void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void printArray(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << std::endl;
}

void mergeSort(int arr[], int len) {}

int main() {
  int arr[] = {10, 8, 6, 2, 2, 1, 0, 4, 15, 3, 7};
  int arr_len = sizeof(arr) / sizeof(int);
  mergeSort(arr, arr_len);
  cout << "Sorted Array: ";
  printArray(arr, arr_len);

  return 0;
}
