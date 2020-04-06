/*
 * Description - Basic Exception.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <vector>
using namespace std;

int main() {
  // cout << "Hello\n";
  // presize = 20 , initialize all elements to 0
  vector<double> number(20, 0);
  // vector<double> number(0);
  cout << "Size : " << number.size() << endl;
  uint capacity = number.capacity();

  cout << "Capacity : " << capacity << endl;

  // The idea of the vectors is that, it hold all the elements in array with some size, and every time new elements is is pushed, where the
  // the defined size exceed, it initializes another array of bigger size(usually doubles it) and copy the elements to this bigger array and deletes old one.
  // Hence the size increases exponentially for a vector, doubling when the capacity breaches.
  for (int i = 0; i < 1000; i++) {
    if (number.capacity() != capacity) {
      capacity = number.capacity();
      cout << "New Capacity : " << capacity << " at iteration " << i << endl;
    }
    number.push_back(i);
  }

  // Some other functions for vector
  number.clear();  // clears all the elements in the vector, size will become 0 but capacity would not change(not changing the internal array).
  cout << "Size : " << number.size() << endl;
  cout << "Capacity : " << number.capacity() << endl;

  return 0;
}
