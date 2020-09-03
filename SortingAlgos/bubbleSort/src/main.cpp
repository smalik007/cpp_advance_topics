/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 *  Bubble Sort is the simplest sorting algorithm that works by repeatedly swapping the adjacent elements if they are in wrong order.
 *
 * first pass
 *  5 1 4 2 8 - > 1 5 4 2 8
 *  1 5 4 2 8 - > 1 4 5 2 8
 *  1 4 5 2 8 - > 1 4 2 5 8
 *  1 4 2 5 8 - > 1 4 2 5 8  (no swap)
 *
 *  second pass
 *  1 4 2 5 8  - > 1 4 2 5 8 (no swap)
 *  1 4 2 5 8 - >  1 2 4 5 8
 *  1 2 4 5 8 - > 1 2 4 5 8 (no swap)
 *  1 2 4 5 8 -> 1 2 4 5 8  (no swap)
 *
 *  In Third swap all the 4 step with be no swap (as the array already go sorted, but this third pass would
 * again run redundantly and break out of loop when no swap was done)
 *
 *  Time Complexity
 *   Best O(n) -> when array is already sorted
 *   In all other cases -> O(n^2)
 *
 * /

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

void bubbleSort(int arr[], int len) {
  for (int j = 0; j < len - 1; j++) {
    bool is_swap = false;

    /* After each iteration the largest element would get at the end, so we can reduce the no of iteration by (len - j -1) */
for (int i = 0; i < len - j - 1; i++) {
  int k = i + 1;
  if (arr[i] > arr[k]) {
    swap(&arr[i], &arr[k]);
    is_swap = true;
  }
}
if (is_swap == false) {
  /* if no swap is done in inside the ith iteration that means array got sorted and don't need to further iterate  */
  break;
}
}
}

int main() {
  int arr[] = {10, 8, 6, 2, 2, 1, 0, 4, 15, 3, 7};
  int arr_len = sizeof(arr) / sizeof(int);
  bubbleSort(arr, arr_len);
  cout << "Sorted Array: ";
  printArray(arr, arr_len);

  return 0;
}
