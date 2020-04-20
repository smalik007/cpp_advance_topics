/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <memory>

#include "ring.h"
using namespace std;

int main() {
  shared_ptr<ring<string>> ptr;
  ptr = make_shared<ring<string>>(3);
  // ring<string> myBuffer(3);

  // myBuffer.add("one");
  // myBuffer.add("two");
  // myBuffer.add("three");
  // myBuffer.add("four"); /* will overwrite the the first value as it's a ring buffer */

  // for (uint i = 0; i < myBuffer.size(); i++) {
  //   cout << myBuffer.get(i) << endl;
  // }

  ptr->add("one");
  ptr->add("two");
  ptr->add("three");
  ptr->add("four");

  for (uint i = 0; i < ptr->size(); i++) {
    cout << ptr->get(i) << endl;
  }

  ptr.reset();
  cout << "Above was explicit call" << endl;

  return 0;
}
