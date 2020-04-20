/*
 * Description - ring.h
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-16 23:39:52
 *
 */

#include <iostream>
using namespace std;

// template<typename T>  /* can also use this syntax aswell */
template <class T>
class ring {
 private:
  uint _size;
  T* _values;
  uint pos;

 public:
  class iterator;

 public:
  ring(uint size) : _size(size), _values(nullptr), pos(0) { _values = new T[size]; }
  ~ring() {
    cout << "Destructor is called" << endl;
    delete[] _values;
  }

  uint size() { return _size; }
  void add(T value) {
    _values[pos++] = value;
    if (pos == _size) {
      pos = 0;
    }
  }

  T& get(int pos) { return _values[pos]; }
};

// class ring::iterator {
//  public:
//   void print() { cout << "Hello from iterator" << endl; }
// };

template <class T>
class ring<T>::iterator {
 public:
  void print() { cout << "Hello there " << endl; }
};