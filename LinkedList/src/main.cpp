#include <iostream>

#include "LinkedList.h"

using namespace std;

void test_code() {
  LinkedList myNumbers;
  cout << "Size: " << myNumbers.size() << endl;
  cout << "empty ? : " << myNumbers.empty() << endl;
  myNumbers.push_back(2);
  myNumbers.push_back(5);
  myNumbers.push_back(6);
  myNumbers.push_back(9);
  myNumbers.push_back(10);

  cout << "empty ? : " << myNumbers.empty() << endl;
  cout << "Size: " << myNumbers.size() << ", " << myNumbers;
  cout << "Max : " << myNumbers.max() << " Min : " << myNumbers.min() << endl;
  cout << "Pop from head: " << myNumbers.pop_front() << endl;
  cout << "Size: " << myNumbers.size() << ", " << myNumbers;

  myNumbers.push_front(3);
  cout << "Size: " << myNumbers.size() << ", " << myNumbers;

  cout << "Pop from tail: " << myNumbers.pop_back() << endl;
  cout << "Size: " << myNumbers.size() << ", " << myNumbers;
  cout << "Max : " << myNumbers.max() << " Min : " << myNumbers.min() << endl;

  cout << "Find 3? : " << myNumbers.linearSearch(3) << endl;
  cout << "Find 100? : " << myNumbers.linearSearch(100) << endl;

  myNumbers.insert(1, 0);
  cout << "Insert at Beg, Size : " << myNumbers.size() << ", " << myNumbers << endl;

  myNumbers.insert(10, myNumbers.size());
  cout << "Insert at last :  Size : " << myNumbers.size() << ", " << myNumbers << endl;

  myNumbers.insert(10, 3);
  cout << "Insert at Beg :  Size : " << myNumbers.size() << ", " << myNumbers << endl;

  /* Invalid index */
  myNumbers.insert(10, 100);
  cout << "Insert at Beg :  Size : " << myNumbers.size() << ", " << myNumbers << endl;
}

void test_code2() {
  LinkedList myNumbers;
  myNumbers.insertSort(5);
  myNumbers.insertSort(6);
  myNumbers.insertSort(9);
  myNumbers.insertSort(10);
  myNumbers.insertSort(7);
  myNumbers.insertSort(11);
  myNumbers.insertSort(1);
  myNumbers.insertSort(2);

  cout << "sorted list : " << myNumbers << " , Size :" << myNumbers.size() << endl;

  cout << "Delete(0) : " << myNumbers.deleteItem(0) << " , " << myNumbers;
  cout << "Size :" << myNumbers.size() << endl;

  cout << "Delete(4) : " << myNumbers.deleteItem(4) << " , " << myNumbers;
  cout << "Size :" << myNumbers.size() << endl;

  cout << "Delete(5) : " << myNumbers.deleteItem(5) << " , " << myNumbers;
  cout << "Size :" << myNumbers.size() << endl;

  cout << "Delete(50) : " << myNumbers.deleteItem(50) << " , " << myNumbers;
  cout << "Size :" << myNumbers.size() << endl;

  cout << "Delete(-10) : " << myNumbers.deleteItem(-10) << " , " << myNumbers;
  cout << "Size :" << myNumbers.size() << endl;

  cout << "isSorted: " << myNumbers.isSorted() << endl;
  // myNumbers.push_back(1);
  myNumbers.push_front(10);
  cout << myNumbers;
  cout << "isSorted: " << myNumbers.isSorted() << endl;

  myNumbers.pop_front();
  cout << myNumbers;
  cout << "isSorted: " << myNumbers.isSorted() << endl;

  myNumbers.reverse();
  cout << "reverse: " << myNumbers;

  myNumbers.reverse();
  cout << "reverseAgain: " << myNumbers;

  LinkedList second;
  second.push_back(0);
  second.push_back(3);
  second.push_back(4);
  second.push_back(11);

  cout << "second: " << second;
  cout << "size : " << second.size() << endl;

  myNumbers.merge(second);

  cout << "newMergedList: " << myNumbers;
  cout << "size : " << myNumbers.size() << endl;

  {
    /* Check destructor is working */
    LinkedList third;
    third.push_back(0);
    third.push_back(3);
    third.push_back(4);
    third.push_back(11);
  }
}

void test_code3() {
  DoubleLinkedList biDirList;
  biDirList.push_back(1);
  biDirList.push_back(4);
  biDirList.push_back(6);
  biDirList.push_back(8);
  biDirList.push_back(10);
  biDirList.push_back(12);
  biDirList.push_front(0);
  cout << biDirList;
  cout << "Size : " << biDirList.size() << endl;
  biDirList.displayRevers();

  cout << "pop front : " << biDirList.pop_front() << endl;
  cout << "pop back : " << biDirList.pop_back() << endl;

  cout << biDirList;
  cout << "Size : " << biDirList.size() << endl;
  biDirList.displayRevers();

  biDirList.insert(0, 0);
  biDirList.insert(5, 3);

  cout << biDirList;
  cout << "Size : " << biDirList.size() << endl;
  biDirList.displayRevers();

  cout << biDirList.deleteItem(1) << endl;
  cout << biDirList.deleteItem(5) << endl;

  cout << biDirList;
  cout << "Size : " << biDirList.size() << endl;
  biDirList.displayRevers();
}

int main() {
  // test_code();
  // test_code2();
  test_code3();
  return 0;
}
