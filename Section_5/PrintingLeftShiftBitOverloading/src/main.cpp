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
  ~Test() {}
  friend ostream& operator<<(ostream& out, const Test& other);
};

/* cout is being passed as reference as first argument and test object as second argument */
ostream& operator<<(ostream& out, const Test& other) {
  out << other._id << ":" << other._name;
  return out;
}

int main() {
  Test test1(10, "Mike");
  /* We are going to overloadd << operator which is used in cout printing. So that we can directly print values of test object using cout << test1 ;*/
  /* We can't overload this in the class as the cout is of type ostream and the returning reference would be different then the Test object, so we need to make a function and overload the operator
   * with this function, and make it as a friend function to out class so then can access the private member of the class */
  cout << test1 << endl;
  return 0;
}
