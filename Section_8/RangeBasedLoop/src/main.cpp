/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <string.h>

#include <iostream>
#include <vector>
using namespace std;

class Test {
 private:
  int _age;
  string _name;

 public:
  Test() : _age(0), _name("") {}
  Test(int age, string name) : _age(age), _name(name) {}
  void print() { cout << _age << " : " << _name << endl; }
  ~Test() {}
};

int main() {
  string one = "bottom";
  char bottom[7] = "bottom";
  cout << one.size() << endl;
  cout << sizeof(bottom) << endl;
  if (strncmp(bottom, one.c_str(), sizeof(bottom)) == 0) {
    cout << "Matches" << endl;
  }
  string persons[] = {"Mike", "Bob", "Joey"};
  for (uint i = 0; i < (sizeof(persons) / sizeof(string)); i++) {
    cout << persons[i] << endl;
  }

  cout << endl;
  /* Alternativel in c++ 11 you can do something like this */
  auto cities = {"Mumbai", "Delhi", "Bangalore"};
  /* we can declare a variable with auto, which ensure the correct type after the variable passed followed by colon and iterate through it */
  for (auto it : cities) {
    cout << it << endl;
  }

  vector<Test> test;
  test.push_back(Test(10, "Mike"));
  test.push_back(Test(20, "Bob"));
  test.push_back(Test(30, "Monica"));
  test.push_back(Test(40, "Ross"));
  cout << endl;
  for (auto it : test) {
    it.print();
  }

  return 0;
}
