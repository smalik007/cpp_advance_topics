/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <set>
using namespace std;

class Test {
 private:
  int _id;
  string _name;

 public:
  Test() : _id(0), _name("") {}
  Test(int id, string name) : _id(id), _name(name) {}

  /* const is required as the iterator pointer will expect it to be a type of const */
  void print() const { cout << _id << " : " << _name << endl; }

  /* you also need to overload the < operator as the set to sort the element uses < operator
    and our class doesn't know how to compare the class objects, and thus have no meaning */

  /* operator overloading will be covered later also but here is the basix syntax */

  /* The comparision operator < returns bool value, The object passed as param should be declared as
    constant as we don't want this to be changed, aslo the whole method needs to be declared as const
    as we also don't want the comparing objects to be changed of the class member and to also to avoid
    making copy of that by default copy constructor by compiler.
    */
  bool operator<(const Test& other) const { return _name < other._name; }
};

int main() {
  /* Set takes only unique elements, if you try to add same element again, it wouldn't just accept it. */
  set<int> numbers;
  numbers.insert(70);
  numbers.insert(50);
  numbers.insert(60);
  numbers.insert(60);  // note the set is only taking one element with value 60

  cout << "Set Size : " << numbers.size() << endl;  // even if you print the size it will only show the size as 3

  /* Get and iterator */
  set<int>::iterator it = numbers.begin();

  /* it will print in accending order, no matter how you the insert order was */
  for (; it != numbers.end(); it++) {
    cout << *it << endl;
  }
  cout << endl;

  /* if number is found in the set, the pointer to element will be returned, else end() pointer will be
    returned */
  it = numbers.find(50);
  if (it != numbers.end()) {
    cout << "Found:" << *it << endl;
  }

  set<Test> test;
  test.insert(Test(10, "Mike"));
  test.insert(Test(20, "Mike"));  // won't insert as the element is duplicated
  test.insert(Test(20, "Joey"));
  test.insert(Test(10, "Sue"));  // But this could work even thought the id is same, the reason for this we have overloaded < operator for string and not the id

  set<Test>::iterator testIt = test.begin();
  cout << endl;
  for (; testIt != test.end(); testIt++) {
    testIt->print();
  }
  return 0;
}
