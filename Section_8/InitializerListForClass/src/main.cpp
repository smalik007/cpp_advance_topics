/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <initializer_list>
#include <iostream>
using namespace std;

template <typename T>
class Test {
 private:
  initializer_list<T> _item;

 public:
  Test(initializer_list<T> item) : _item(item) {}
  void print() {
    for (auto it : _item) {
      cout << it << endl;
    }
  }
  void print(initializer_list<T> item) {
    _item = item;
    for (auto it : _item) {
      cout << it << endl;
    }
  }
};

int main() {
  /* Like a vector initlializer list with using {}, we can also create our own custom class using initializer_list */
  Test<string> fruits{"apple", "banana", "orange"};
  fruits.print();

  cout << endl;
  fruits.print({"one", "two", "three"});

  cout << endl;
  fruits.print();

  return 0;
}
