/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <atomic>
#include <iostream>
#include <memory>
#include <thread>

#include "ring.h"
using namespace std;

// RingBuffer<string> myBuffer(15);
// RingBuffer<string> myBufferCopy(15);
// RingBuffer<string>* myBuffer;
// RingBuffer<string>* myBufferCopy;
std::atomic<bool> flagRead(false);

RingBuffer<string>::RingBufferSPtrType stringBuff;
RingBuffer<string>::RingBufferSPtrType shallowBuff;

// void readBuffer() {
//   string ptr;
//   while (true) {
//     // cout << "waiting for dataCondition" << endl;
//     if (flagRead) {
//       myBuffer->popBack(ptr);
//       cout << ptr << endl;
//     }
//   }
// }

int main() {
  // std::thread myThread(readBuffer);

  std::unique_ptr<RingBuffer<string>> myBuffer(new RingBuffer<string>(15));
  std::unique_ptr<RingBuffer<string>> myBufferCopy(new RingBuffer<string>(15));

  stringBuff = std::make_shared<RingBuffer<string>>(5);
  shallowBuff = std::make_shared<RingBuffer<string>>(15);
  // myBuffer = new RingBuffer<string>(15);
  // myBufferCopy = new RingBuffer<string>(15);

  // string names[]{"Mike", "Joey", "Monica"};
  string names[]{"Mike", "Joey", "Monica", "Ross", "Chandler"};
  for (auto name : names) {
    // myBuffer.pushFront(name);
    myBuffer->pushFront(name);
    stringBuff->pushFront(name);
  }

  // string temp;
  // stringBuff->popBack(temp);

  myBuffer->move(myBufferCopy.get());
  stringBuff->move(shallowBuff.get());
  cout << "Copied in shallow buff" << std::endl;

  while (myBufferCopy->isNotEmpty()) {
    string ptr;
    myBufferCopy->popBack(ptr);

    cout << ptr << endl;
  }

  cout << endl;

  while (myBuffer->isNotEmpty()) {
    string ptr;
    myBuffer->popBack(ptr);

    cout << ptr << endl;
  }

  cout << endl;

  //   myBuffer.clear();

  // for (int i = 0; i < 10; i++) {
  //   cout << i << endl;
  //   usleep(10000);
  // }
  // flagRead = true;
  // myThread.join();

  while (shallowBuff->isNotEmpty()) {
    string ptr;
    shallowBuff->popBack(ptr);

    cout << ptr << endl;
  }
  cout << endl;
  while (stringBuff->isNotEmpty()) {
    string ptr;
    stringBuff->popBack(ptr);

    cout << ptr << endl;
  }

  // delete myBuffer;
  // delete myBufferCopy;

  return 0;
}
