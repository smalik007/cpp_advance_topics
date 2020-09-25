#include <iostream>

/* Taylor series
    f(x,n) = 1 + x/1 + x^2/2! + x^3/3! + x^4/4! + .... + n terms

    time complexity O(n^2) */

float taylorSeries(int x, int n) {
  static float pow = 1, fact = 1;
  float r;
  if (n == 0)
    return 1;

  else {
    r = taylorSeries(x, n - 1);
    pow = pow * x;
    fact = fact * n;
    return r + pow / fact;
  }
}

/* f(x,n) = 1 + x/1 + x^2/2! + x^3/3! + x^4/4! + ....
          = 1 + x[1 + x/2 + x^2/3! + x^3/4! + ....]
          = 1 + x[ 1 + x/2[1 + x/3 + x^2/(3*4) + ....]]

    Time Complexity = O(n)  */

float iTaylorSeries(int x, int n) {
  float s = 1;
  for (; n > 0; n--) {
    s = 1 + (x * s / n);
  }
  return s;
}

int main() {
  std::cout << taylorSeries(3, 10) << std::endl;
  std::cout << iTaylorSeries(3, 10) << std::endl;
}