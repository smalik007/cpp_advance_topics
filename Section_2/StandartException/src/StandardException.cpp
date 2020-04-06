/*
 * Description - StandardException.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

class CanGoWrong {
 public:
  CanGoWrong() {
    // assign memory which can't be possible to assign
    char* pMemory = new char[9999999999999];
    delete[] pMemory;
  }
};

int main() {
  cout << "Hello\n";
  try {
    CanGoWrong wrong;
  } catch (bad_alloc& e) {
    cout << "Caught Exception : " << e.what() << endl;
  }
  return 0;
}