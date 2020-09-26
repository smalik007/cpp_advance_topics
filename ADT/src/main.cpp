#include <iostream>

#include "ADT.h"
using namespace std;

void testFunc() {
  int capacity = 3;
  int temp[] = {1, 3, 5};
  Array myVector(temp, (sizeof(temp) / sizeof(int)), capacity);

  cout << "Cap:" << myVector.getCapacity() << " size : " << myVector.size() << endl;
  myVector.display();
  myVector.push(6);
  myVector.push(9);
  myVector.display();

  myVector.insert(0, 7);
  myVector.display();
  myVector.insert(5, 8);
  myVector.display();

  cout << "pop : " << myVector.pop() << endl;
  myVector.display();

  cout << "removed : " << myVector.remove(2) << endl;
  myVector.display();

  cout << "Max: " << myVector.max() << " Min: " << myVector.min() << endl;
  cout << "Sum: " << myVector.sum() << " avg: " << myVector.avg() << endl;

  cout << "search 3 :  " << myVector.linearSearch(3) << endl;
  cout << "search 7 :  " << myVector.linearSearch(7) << endl;

  cout << "search 7 :  " << myVector.binarySearch(7) << endl;

  // Array mySortedVec(temp, (sizeof(temp) / sizeof(int)), capacity);
  // cout << "isSorted: " << mySortedVec.isSorted() << " " << mySortedVec.isSorted(Array::DISSENDING) << endl;
  // cout << "search 5 :  " << mySortedVec.binarySearch(5) << endl;
}

int main() {
  testFunc();
  return 0;
}
