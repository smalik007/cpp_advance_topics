/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 *
 *  Quick sort is a recursive algorithm (Divide and conquer, divide element about the pivot element)
 *
 *  1. Choose Pivot element (could be first element last element or even mid)
 *  2. Sort element about pivot (smaller to the left, bigger to right)
 *  3. Recurse step 2.
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

int partition_with_pivot_last(int arr[], int low, int high) {
  /* Take last element as the pivot */
  int pivot = arr[high];

  int index_low = low; /* index of the smaller elements to be stored on left of pivot element */

  /* iterate upto high - 1 (one less than the pivot element*/
  /* Initial array */
  /* [10, 8, 6, 2, 4, 15, 3, 7(p)]   p-> pivot element*/

  /* [ 10, 8, 6, 2, 4, 15, 3, 7]  [i = 0, index_low = 0 ]  No swap as 10 > 7*/
  /* [ 10, 8, 6, 2, 4, 15, 3, 7]  [i = 1, index_low = 0 ]  No swap as 8 > 7*/
  /* [ 6, 8, 10, 2, 4, 15, 3, 7]  [i = 2, index_low = 0++ ]  Swap 6 with 10 , as 6 < 7 */
  /* [ 6, 2, 10, 8, 4, 15, 3, 7]  [i = 3, index_low = 1++ ]  Swap 2 with 8 , as 2 < 7 */
  /* [ 6, 2, 4, 8, 10, 15, 3, 7]  [i = 4, index_low = 2++ ]  Swap 4 with 10 , as 4 < 7 */
  /* [ 6, 2, 4, 8, 10, 15, 3, 7]  [i = 5, index_low = 2 ]  No swap , as 15 > 7 */
  /* [ 6, 2, 4, 3, 10, 15, 8, 7]  [i = 5, index_low = 3++ ]  Swap 3 with 8 as 3 < 7*/

  for (int i = low; i <= high - 1; i++) {
    if (arr[i] < pivot) {
      /* swap all elements less than pivot to left */
      swap(&arr[index_low], &arr[i]);
      index_low++;
    }
  }

  /* [ 6, 2, 4, 3, 10, 15, 8, 7]  [index_low = 4 ]  Swap 7 with 10 as all the element lower to 7 has their 1st
  first place and 7 position would be now the index pointing by index_low, So after swapping we would have the 7
  alligned at correct position and have pivot index which devides the array in 2 part */
  /* [ 6, 2, 4, 3, 7, 15, 8, 10]  [index_low = 4 = pivot_index ] */
  swap(&arr[index_low], &arr[high]);
  return (index_low);
}

int partition_with_pivot_first(int arr[], int low, int high) {
  /* Take first element as the pivot */
  int pivot = arr[low];
  int index_high = high; /* index of the higher elements to be stored on right of pivot element */

  /* iterate upto low + 1 (one less than the pivot element*/
  /* Initial array */
  /* [10(p), 8, 6, 2, 4, 15, 3, 7]   p-> pivot element*/

  /* [ 10, 8, 6, 2, 4, 15, 3, 7]  [i = high = 7, index_high = 7 ]  No swap as 7 < 10*/
  /* [ 10, 8, 6, 2, 4, 15, 3, 7]  [i = 6, index_low = 7 ]  No swap as 3 < 10*/
  /* [ 10, 8, 6, 2, 4, 7, 3, 15]  [i = 5, index_low = 7-- ]  Swap 15 with 7, as 15 > 10 */
  /* [ 10, 8, 6, 2, 4, 7, 3, 7]  [i = 4, index_low = 6 ]  No swap , as 4 < 10 */
  /* [ 10, 8, 6, 2, 4, 7, 3, 15]  [i = 3, index_low = 6 ]  No swap , as 2 < 10 */
  /* [ 10, 8, 6, 2, 4, 7, 3, 15]  [i = 2, index_low = 6 ]  No swap , as 6 < 10 */
  /* [ 10, 8, 6, 2, 4, 7, 3, 15]  [i = 1, index_low = 6 ]  No swap,  as 8 < 10*/

  for (int i = high; i >= low + 1; i--) {
    if (arr[i] > pivot) {
      /* swap all elements higher than pivot to right */
      swap(&arr[index_high], &arr[i]);
      index_high--;
    }
  }

  /* [ 10, 8, 6, 2, 4, 7, 3, 15]  [index_high = 6 ]  Swap 3 with 10 as all the element higher to 10 has their 1st
  first place and 10 position would be now the index pointing by index_high, So after swapping we would have the 7
  alligned at correct position and have pivot index which devides the array in 2 part */
  /* [3, 8, 6, 2, 4, 7, 10, 15]  [index_low = 6 = pivot_index ] */
  swap(&arr[index_high], &arr[low]);
  return (index_high);
}

/* TODO: correct below function */
int partition_with_pivot_mid(int arr[], int low, int high) {
  /* Take mid element as the pivot */
  int mid_indx = (high + low) / 2;
  int pivot = arr[mid_indx];

  int index_low = low; /* index of the smaller elements to be stored on left of pivot element */

  /* iterate upto high - 1 (one less than the pivot element*/
  /* Initial array */
  /* [10, 8, 6, 2(p), 4, 15, 3, 7]   p-> pivot element*/

  /* [ 10, 8, 6, 2, 4, 15, 3, 7]  [i = 0, index_low = 0 ]  No swap as 10 > 7*/
  /* [ 10, 8, 6, 2, 4, 15, 3, 7]  [i = 1, index_low = 0 ]  No swap as 8 > 7*/
  /* [ 6, 8, 10, 2, 4, 15, 3, 7]  [i = 2, index_low = 0++ ]  Swap 6 with 10 , as 6 < 7 */
  /* [ 6, 2, 10, 8, 4, 15, 3, 7]  [i = 3, index_low = 1++ ]  Swap 2 with 8 , as 2 < 7 */
  /* [ 6, 2, 4, 8, 10, 15, 3, 7]  [i = 4, index_low = 2++ ]  Swap 4 with 10 , as 4 < 7 */
  /* [ 6, 2, 4, 8, 10, 15, 3, 7]  [i = 5, index_low = 2 ]  No swap , as 15 > 7 */
  /* [ 6, 2, 4, 3, 10, 15, 8, 7]  [i = 5, index_low = 3++ ]  Swap 3 with 8 as 3 < 7*/

  for (int i = low; i <= high; i++) {
    if (arr[i] < pivot) {
      /* swap all elements less than pivot to left */
      if (i != mid_indx) {
        swap(&arr[index_low], &arr[i]);
        index_low++;
      }
    }
  }

  /* [ 6, 2, 4, 3, 10, 15, 8, 7]  [index_low = 4 ]  Swap 7 with 10 as all the element lower to 7 has their 1st
  first place and 7 position would be now the index pointing by index_low, So after swapping we would have the 7
  alligned at correct position and have pivot index which devides the array in 2 part */
  /* [ 6, 2, 4, 3, 7, 15, 8, 10]  [index_low = 4 = pivot_index ] */
  swap(&arr[index_low], &arr[mid_indx]);
  printArray(arr, high);
  return (index_low);
}



void quickSort(int arr[], int low, int high) {
  if (low < high) {
    int pivot_index = partition_with_pivot_first(arr, low, high);
    // int pivot_index = partition_with_pivot_last(arr, low, high);
    // int pivot_index = partition_with_pivot_mid(arr, low, high);
    quickSort(arr, low, pivot_index - 1);
    quickSort(arr, pivot_index + 1, high);
  }
}

void printArray(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << std::endl;
}

int main() {
  int arr[] = {10, 8, 6, 2, 4, 15, 3, 7};
  int arr_len = sizeof(arr) / sizeof(int);
  quickSort(arr, 0, arr_len - 1);
  cout << "Sorted Array: ";
  printArray(arr, arr_len);

  return 0;
}

/* Time complexity analysis */

/* Best Case [O(nlog(n)] : If array is such that partition always devide the array from the
 mid (or the pivot is chosen such that it always devide the array in half)

 fact: Achiving a best case would require the partion should be done at the middle element and it should
  be the median in each recursive step of partioning, which is not easily possible if the list is unsorted
  it may randomly happen, but it mostly not possible to achive best case in quick sort
  https://www.youtube.com/watch?v=-qOVVRIZzao&t=23s

  e.g let say arr consist no. 1-15 in unsorted way [1......15]

                        [     1-15    ]                       - O(n) for partition funtion sorting traverse
                      /        8       \
                   [ 1-7 ]              [ 9-15  ]             - O(n) for partition funtion sorting traverse
                 /   4   \             /   12    \
              [ 1,3 ]   [ 5,7 ]      [9-11]       [13-15]     - O(n) for partition funtion sorting traverse
             /  2  \    /  6  \      / 10  \       /  14  \
           [1]     [3]  [5]   [7]   [9]    [11]  [13]    [15] - O(n) for partition funtion sorting traverse

          Now we find the depth : How many times(recursive) it took to reach the array with single element

          we are actully deviding n by 2 here in each step until it reaches 1: that would be n/2/2/2/2/2... = n/2^k

          n/2^k = 1 =>  2^k = n => k = log(n)  -> (base of log is 2)

          O(T) = O(n*logn)

  worst case O(n^2): If the list is already sorted and the pivot is chosen as the first element or the last element, then the time complexity of quick sort is O(n^2)

  consider already sorted list = [1, 2, 3, 4, 5 ,6] let's choose last element 6 as pivot

                        [1-6]        - n steps to traverse
                      / 6
                   [1-5]             - n - 1 steps to traverse
                 / 5
            [1-4]                   - n - 2 steps to traverse
            / 4
        [1-3]                       - ....
        / 3
      [1-2]                         - 2  steps
      / 2
    [1]                             - 1  steps

    O(n) = 1 + 2 + 3 + ... + (n-2) + (n-1) + (n) = sum of A.P = n(l + a)/2 = n(n + 1)/2 = O(n^2)

  To solve this we can choose middle element as a pivot then the worst case would become best case, in some other sample of input it may even go to O(n^2)

*/