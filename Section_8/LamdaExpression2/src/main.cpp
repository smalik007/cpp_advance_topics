/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

void test(void (*pFunc)(string)) { pFunc("Bob"); }

double runDivide(double (*pFunc)(double, double)) { return pFunc(10, 5); }

int main() {
  /* lambda with param */
  auto pGreet = [](string name) { cout << "Hello " << name << endl; };

  pGreet("Mike");

  test(pGreet);

  /* lambda with return type, By default return type it can take as if it is consistent, like here the return type would be a double */
  auto pDivide = [](double a, double b) -> double {
    if (b == 0) {
      /* here we are returning and int hence compiler will give error on second return type to as double, c++ does not explicity type cast this to double as it doesn't know yet what all return
       * type to be casted to. To solve this problem we need to add a trailing return type to it */
      return 0;
    }
    return a / b;
  };
  cout << pDivide(6, 2) << endl;
  cout << pDivide(6, 0) << endl;

  cout << runDivide(pDivide) << endl;

  return 0;
}
