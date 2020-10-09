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
}

int main() {
  test_code();
  return 0;
}
