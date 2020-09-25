/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 *
 * 1: Iterate from arr[1] to arr[n] over the array.
   2: Compare the current element (key) to its predecessor.
   3: If the key element is smaller than its predecessor, Use binary search to find the index where it should be placed
   4: put the element on searched index and rearrange the array to +1 index after that
 *
 * Time Complexity
 * Best and average case O(log (n))
 * worst case O(n^2)
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

/* return the index where the item should be placed */
int binarySearch(int arr[], int low, int high, int item) {
  if (high <= low) {
    return (item > arr[low] ? (low + 1) : low);
  }

  int mid = high + low / 2;
  if (item == arr[mid]) return (mid + 1);

  if (item > arr[mid]) {
    /* if item > arr[mid] search on the right side of the array */
    return binarySearch(arr, mid + 1, high, item);
  } else {
    /* if item > arr[mid] search on the left side of the array */
    return binarySearch(arr, low, mid - 1, item);
  }
}

void binaryInsertionSort(int arr[], int len) {
  int i = 0, j = 0, index = 0;
  for (i = 1; i < len; i++) {
    int item = arr[i];
    j = i - 1;

    if (arr[i] < arr[i - 1]) {
      index = binarySearch(arr, 0, j, item);

      /* Rearrange all elements */
      while (j >= index) {
        swap(&arr[j], &arr[j + 1]);
        j--;
      }
    }
  }
}

int main() {
  int arr[] = {10, 8, 6, 2, 2, 1, 0, 4, 15, 3, 7};
  int arr_len = sizeof(arr) / sizeof(int);
  binaryInsertionSort(arr, arr_len);
  cout << "Sorted Array: ";
  printArray(arr, arr_len);

  return 0;
}
