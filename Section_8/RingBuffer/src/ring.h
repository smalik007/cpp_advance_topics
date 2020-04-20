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

  /* iterator is a nested class but it has no way to access the private members of ring class, so we would need to pass a reference of ring here */
  iterator begin() {
    /* here is 0 is first index position */
    return iterator(0, *this);
  }

  iterator end() {
    /* here _size is the last element + 1 index */
    return iterator(_size, *this);
  }
};

// class ring::iterator {
//  public:
//   void print() { cout << "Hello from iterator" << endl; }
// };

template <class T>
class ring<T>::iterator {
 private:
  uint _pos;
  ring& _buffer;

 public:
  iterator(uint pos, ring& ref) : _pos(pos), _buffer(ref) {}

  /* There are two version of ++ operator, prefix and postfix, below is for prefix ++ operator */
  iterator& operator++() {
    _pos++;
    return *this;
  }

  /* Posfix look like this, taking a extra parameter in bracket */
  iterator& operator++(int) {
    _pos++;
    return *this;
  }

  /* Dereference operator */
  T& operator*() { return _buffer.get(_pos); }

  /* overloading ! operator */
  bool operator!=(const iterator& end) const { return (_pos != end._pos); }

  void print() { cout << "Hello from iterator" << endl; }
};