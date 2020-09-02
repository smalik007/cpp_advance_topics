/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 *
 * 1: Iterate from arr[1] to arr[n] over the array.
   2: Compare the current element (key) to its predecessor.
   3: If the key element is smaller than its predecessor, compare it to the elements before.
    Move the greater elements one position up to make space for the swapped element.
 *
 * Time Complexity
 * Best Case O(n) -> when the array is already sorted, inner while loop inside the for loop woudn't execute
 * In all cases O(n^2)
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

void insertionSort(int arr[], int len) {
  int i = 0, j = 0, key = 0;
  for (i = 1; i < len; i++) {
    key = arr[i];
    j = i - 1;

    while (j >= 0 && arr[j] > key) {
      swap(&arr[j], &arr[j + 1]);
      j--;
    }
  }
}

int main() {
  int arr[] = {10, 8, 6, 2, 2, 1, 0, 4, 15, 3, 7};
  int arr_len = sizeof(arr) / sizeof(int);
  insertionSort(arr, arr_len);
  cout << "Sorted Array: ";
  printArray(arr, arr_len);

  return 0;
}
