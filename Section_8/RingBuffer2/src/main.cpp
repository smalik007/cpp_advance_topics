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
  RingBuffer<string>::RingBufferSPtrType pString;
  pString = make_shared<RingBuffer<string>>(3);

  pString->write("Mike");
  pString->write("Joey");
  pString->write("Monica");

  string getStr{};
  pString->read(getStr);
  cout << getStr << endl << endl;

  pString->write("heym");

  while (!pString->empty()) {
    string getStr{};
    pString->read(getStr);
    cout << getStr << endl;
  }

  return 0;
}
