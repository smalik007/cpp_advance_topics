/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 *
 *  Selection Sort is an iterative algorithm, which loops on the array and select the least element in array and places it at the beginning
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

void selectSort(int arr[], int len) {
  /* Time Complexity is O(n^2) in all cases */
  for (int j = 0; j < len; j++) {
    int min = arr[j];
    int min_idx = j;

    for (int i = j + 1; i < len; i++) {
      if (arr[i] < min) {
        min = arr[i];
        min_idx = i;
      }
    }

    if (j != min_idx) swap(&arr[j], &arr[min_idx]);
  }
}

int main() {
  int arr[] = {10, 8, 6, 2, 2, 1, 0, 4, 15, 3, 7};
  int arr_len = sizeof(arr) / sizeof(int);
  selectSort(arr, arr_len);
  cout << "Sorted Array: ";
  printArray(arr, arr_len);

  return 0;
}
