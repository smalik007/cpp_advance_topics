/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

class Test {
 private:
  int _id;
  string _name;

 public:
  Test() : _id(0), _name("") {}
  Test(int id, string name) : _id(id), _name(name) {}
  void print() { cout << _id << "-" << _name << endl; }
  ~Test() {}
  /* Overaloading the assignment operator */
  const Test& operator=(const Test& other) {
    cout << "Assignment operator running" << endl;
    _id = other._id;
    _name = other._name;

    /* Lets try assigning some random value here */
    // _id = 123;
    // _name = "Raj";

    /* Derefrencing and return the value of the object being assigned value to*/
    return *this;
  }

  /* Lets implement the copy constructor to see the copy initialization. If you comment delete this function, the functionality will still remain same and program will use the default copy constructor
   * and copy all the values, this is just to show when this is being executed */
  Test(const Test& other) {
    cout << "Copy Constructor is running" << endl;
    /* If you commment out below operation than there will be some garbage values assigned here */
    _id = other._id;
    _name = other._name;
  }
};

int main() {
  Test test1(10, "Mike");
  test1.print();
  cout << endl;

  Test test2(20, "Raj");

  /* c++ provide this default assignment operator and create a shallow copy of tes1 object and assign it to test2. But in some cases if let say the class members have pointers and are pointing to some
   * memory location, you may not want the shallow copy of this pointer and a second object pointing to same memory in those case operator overloading can come into play */
  test2 = test1;
  /* Internally the assignment operator or any operator is like a method taking an reference to assigned value and returning value as reference
   You can also you above statement like this below and it will have the same effect, uncomment to check*/
  // test2.operator=(test1);

  test2.print();
  cout << endl;

  /* In this case the assignment operator will not be invoked, instead this is called Copy initialization, and here actually default copy constructor is initliazing the values to test3 instead of
    assignment operator */
  Test test3 = test1;
  test3.print();

  return 0;
}
