/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <memory>  // include for smart pointers
using namespace std;

class Test {
 public:
  Test() { cout << "Constructor is called" << endl; }
  ~Test() { cout << "Destructor is called" << endl; }
  void greet() { cout << "Hello" << endl; }
};

int main() {
  /* Normal type of pointer where we need to track of the deleting it, otherwise we will be leaking the memory*/
  Test* pTest1 = new Test();
  pTest1->greet();
  /* If you comment below line, destructor will never be called */
  delete pTest1;

  cout << endl << "Using smart Pointer" << endl;
  /* Alternatively we can use smart pointers to avoid tracking of the pointers delete, smart pointers automatically deallocate the memory as soon as it goes out of scope */
  /* Note: Prior to c++11 there was auto_ptr<type> which is similar to this unique ptr, they are now deprecated in c++11 */
  unique_ptr<Test> pTest2(new Test());
  pTest2->greet();

  /* You can also expilicity deallocate the memory(Though it is not required) using reset method, reset replaces the managed object */
  /* Uncomment/Comment below line to see at what stage the destructor is called(before or after the print "Finished") */
  // pTest2.reset();

  /* In some situation you might need need to get the address from of some element which is pointed by unique pointer to a normal pointer or may be to call a function which does not take smart
   * pointers(for example memcpy, or any third party library functions),  you can use ptr.get() method and it will return returns a pointer to the managed object */
  // Test* pTest3 = pTest2.get();

  /* Becareful: Sometime you may also wan't to release the ownership to a normal ptr from unique pointer, you can use ptr.release() method, this will returns a pointer to the managed object and
   * releases the ownership, now you would have to take care the deallocating part by yourself, and there may be leaks if you don't do so */
  // Test* pTest3 = pTest2.release();
  /* Must do this otherwise leaks will happen */
  // delete pTest3;

  cout << endl << "Using unique_ptr with array" << endl;
  unique_ptr<Test[]> pArray(new Test[2]);
  pArray[1].greet();

  cout << "Finished" << endl;

  return 0;
}
