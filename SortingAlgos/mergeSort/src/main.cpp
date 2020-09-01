/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 *
 *  Like QuickSort, Merge Sort is a Divide and Conquer algorithm. It divides input array in two halves, calls itself for the two halves and then merges the two sorted halves. The merge() function is
 *  used for merging two halves. The merge(arr, l, m, r) is key process that assumes that arr[l..m] and arr[m+1..r] are sorted and merges the two sorted sub-arrays into one.
 *  Time Complexity - O(nlogn) in all cases
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

void merge(int arr[], int low, int mid, int high) {
  int i, j, k;

  /* size of first sub-array */
  int n1 = mid - low + 1;
  /* size of second sub-array */
  int n2 = high - mid;

  int left[n1], right[n2];

  /* Initially fill subarrays-unsorted  */
  for (i = 0; i < n1; i++) {
    left[i] = arr[low + i];
  }
  for (j = 0; j < n2; j++) {
    right[j] = arr[mid + 1 + j];
  }

  i = 0;
  j = 0;
  k = low;

  while (i < n1 && j < n2) {
    if (left[i] <= right[j]) {
      arr[k] = left[i];
      i++;
    } else {
      arr[k] = right[j];
      j++;
    }
    k++;
  }

  /* Copy remaining element */
  while (i < n1) {
    arr[k] = left[i++];
    k++;
  }

  while (j < n2) {
    arr[k] = right[j++];
    k++;
  }
}

void mergeSort(int arr[], int low, int high) {
  if (low < high) {
    int mid = (low + high) / 2;

    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
  }
}

int main() {
  int arr[] = {10, 8, 6, 2, 2, 1, 0, 4, 15, 3, 7};
  int arr_len = sizeof(arr) / sizeof(int);
  mergeSort(arr, 0, arr_len - 1);
  cout << "Sorted Array: ";
  printArray(arr, arr_len);

  return 0;
}
