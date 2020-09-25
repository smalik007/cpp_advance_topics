#include <iostream>
using namespace std;

/* 0, 1, 1, 2, 3, 5, 8, 13, 21 ....

    f(n) = 0 , n = 0
    f(n) = 1 , n = 1
    f(n) = f(n-2) + f(n-1) n > 1

    Time complexity : 2 fibRecurse (2 recrsive calls when n > 1, and recusive call will be an exponent of n) -> O(2^n)
 */

int fibRecurse(int n) {
  if (n <= 1) {
    return n;
  }

  return fibRecurse(n - 2) + fibRecurse(n - 1);
}

/* we can use technique of memorization to store the values that function has find out and avoid excessive recursive call  */
/* Time Complexity : for n there would be n+1 recursice call using this function, so O(n) */

#define MAX_FIBONACCI_USING_THIS_FUNC 50
int fib[MAX_FIBONACCI_USING_THIS_FUNC];  // For Memorization

int fibRecurseBetter(int n) {
  if (n <= 1) {
    fib[n] = n;
    return n;
  }

  if (fib[n - 2] == -1) {
    fib[n - 2] = fibRecurseBetter(n - 2);
  }
  if (fib[n - 1] == -1) {
    fib[n - 1] = fibRecurseBetter(n - 1);
  }

  return fib[n - 2] + fib[n - 1];
}

/* using Loop
    Time complexity : O(n)
 */

int fibLoop(int n) {
  int i = 0;
  int fibPrev = 0;
  int fibCurr = 1;
  int temp = 0;

  if (n <= 1) {
    return n;
  }

  for (i = 2; i <= n; i++) {
    temp = fibCurr;
    fibCurr += fibPrev;
    fibPrev = temp;
  }

  return fibCurr;
}

int main() {
  int n = 0;

  for (int i = 0; i < MAX_FIBONACCI_USING_THIS_FUNC; i++) {
    fib[i] = -1;
  }

  cin >> n;
  cout << fibRecurse(n) << endl;
  cout << fibLoop(n) << endl;
  cout << fibRecurseBetter(n) << endl;
  return 0;
}