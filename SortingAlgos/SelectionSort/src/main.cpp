/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 *
 *  Quick sort is a recursive algorithm (Divide and conquer, divide element about the pivot element)
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

int main() {
  int arr[] = {10, 8, 6, 2, 4, 15, 3, 7};
  int arr_len = sizeof(arr) / sizeof(int);
  // quickSort(arr, 0, arr_len - 1);
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