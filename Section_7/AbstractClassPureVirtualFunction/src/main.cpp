/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

class Animal {
 public:
  /* Declaring a funtion and assigning = 0 with no implementaion make the method a purely virtual method and the class an asbstract class, You can create an intace of this class as no implementation
   * is give to the method, however you can declare a pointer and refrence it to any derived class where the method is impemented */
  virtual void speak() = 0;
};

class Dog : public Animal {
 public:
  void speak() { cout << "Woof!" << endl; }
};

int main() {
  /* You will get an error with following statement as the class methods are purely virtual */
  // Animal a;

  /* However you can define a pointer of type Animal */
  Animal* d;

  /* and reference it to a derived class type */
  d = new Dog();
  d->speak();

  return 0;
}
