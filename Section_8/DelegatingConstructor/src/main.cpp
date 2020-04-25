/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

/* c++11 allow calling a constructor of class from other constructor of the same class when an object is created */

class Parent {
 private:
  int _age;
  string _name;

 public:
  /* we can call a argument constructor from the empty constructor, But now this constructor is not equivalent to default implementation even if we remove the cout print here */
  /* This constructor is called delegating constructor */
  /* Here it will first call the Delegated constructor and start executing itself */
  Parent() : Parent(40, "Mike") { cout << "Delegating Parent Constructor is called" << endl; }

  Parent(int age, string name) : _age(age), _name(name) { cout << "Parent constructor with arguments runnnig" << endl; }
};

class Child : public Parent {
 public:
  Child() = default;
};

int main() {
  Child c1;
  return 0;
}
