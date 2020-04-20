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
  int size;
  string* myString;

 public:
  explicit Test(int s) : size(s) { myString = new string[size]; }
};

int main() {
  cout << "Hello\n";
  return 0;
}
