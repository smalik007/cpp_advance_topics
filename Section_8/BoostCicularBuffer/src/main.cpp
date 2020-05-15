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

RingBuffer<string> myBuffer(15);
std::atomic<bool> flagRead(false);

void readBuffer() {
  string ptr;
  while (true) {
    // cout << "waiting for dataCondition" << endl;
    if (flagRead) {
      myBuffer.popBack(ptr);
      cout << ptr << endl;
    }
  }
}

int main() {
  std::thread myThread(readBuffer);

  // string names[]{"Mike", "Joey", "Monica"};
  string names[]{"Mike", "Joey", "Monica", "Ross", "Chandler"};
  for (auto name : names) {
    myBuffer.pushFront(name);
  }

  //   myBuffer.clear();

  for (int i = 0; i < 10; i++) {
    cout << i << endl;
    usleep(10000);
  }
  flagRead = true;
  myThread.join();

  //   while (myBuffer.isNotEmpty()) {
  //     string ptr;
  //     myBuffer.popBack(ptr);

  //     cout << ptr << endl;
  //   }

  return 0;
}
