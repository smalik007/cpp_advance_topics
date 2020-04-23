/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

class Test {
 private:
  /* default initialization to all objects */
  int a{3};
  string str{"Mike"};

 public:
  /* equivalent to empty curly braces */
  Test() = default;

  /* ovverride the default value for integer */
  Test(const Test& other) = default;

  /* overloading = operator and assigning default to use defa */
  Test& operator=(const Test& other) = default;

  /* exlicity defining copy constructor */
  explicit Test(int n) : a(n) {}
  void print() { cout << a << ":" << str << endl; }
};

int main() {
  Test test1;
  test1.print();

  Test test2(5);
  test2.print();

  /* Below uses copy initialization and use copy constructor */
  /* Try to set the copy constructor to delete and this line will give you an error */
  Test test3 = test1;
  test3.print();

  /* This will invoke the assignment operator */
  test3 = test2;
  test3.print();

  return 0;
}
