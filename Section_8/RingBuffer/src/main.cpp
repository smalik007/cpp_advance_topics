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
  shared_ptr<ring<string>> ptrBuffer;
  ptrBuffer = make_shared<ring<string>>(10);

  // ring<string> myBuffer(3);

  // myBuffer.add("one");
  // myBuffer.add("two");
  // myBuffer.add("three");
  // myBuffer.add("four"); /* will overwrite the the first value as it's a ring buffer */

  // for (uint i = 0; i < myBuffer.size(); i++) {
  //   cout << myBuffer.get(i) << endl;
  // }

  ptrBuffer->add("one");
  ptrBuffer->add("two");
  ptrBuffer->add("three");
  ptrBuffer->add("four");

  // for (uint i = 0; i < ptrBuffer->size(); i++) {
  //   cout << ptrBuffer->get() << endl;
  // }

  cout << endl;

  cout << "output using iterator" << endl;
  ring<string>::iterator it = ptrBuffer->begin();
  /* Try and use prefix/postfix notation */
  for (; it != ptrBuffer->end(); it++) {
    cout << *it << endl;
  }
  cout << endl;

  /* Now the iterator is implemented, you can also use auto range based loop*/

  cout << "output usin range based loop" << endl;

  /* Here I used unique pointer and derefrenced it to get the class intance type */
  /* Auto uses prefix notation */
  for (auto itr : *ptrBuffer) {
    cout << itr << endl;
  }

  cout << endl;
  ptrBuffer.reset();
  cout << "Above was explicit call" << endl;

  return 0;
}
