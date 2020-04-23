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
  int one{1};
  int two{2};

 public:
  void run() {
    int three{3};
    int four{4};

    /* you can't capture the private member directly, you have to use this reference, so now since it is captured by reference we can modify it.
    you can't use default =, this as this is not passed by value, however you can use &, this as both of them are passed by references  */
    auto lamda = [three, this, four]() {
      cout << three << endl;
      cout << four << endl;
      two = 5;
      cout << two << endl;
    };
    lamda();
  }
};

int main() {
  Test test;
  test.run();
  return 0;
}
