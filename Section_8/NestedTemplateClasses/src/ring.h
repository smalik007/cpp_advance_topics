/*
 * Description - ring.h
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-16 23:39:52
 *
 */

#include <iostream>
using namespace std;

class ring {
 public:
  /* you can declare class any where in c++. Here in this case it is an example of nested classes where we are declaring it under the public scope of class ring */
  // class iterator {
  //  public:
  //   void print() { cout << "Hello from iterator" << endl; }
  // };

  /* As above syntax look like ugly, and as it grows with more methods it alss looses readability, So it's a good practice to fwd declare the class here and define it later */
  class iterator;
};

class ring::iterator {
 public:
  void print() { cout << "Hello from iterator" << endl; }
};
