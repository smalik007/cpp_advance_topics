/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <algorithm>  // for std::sort()
#include <iostream>
#include <vector>
using namespace std;

class Test {
 private:
  int _id;
  string _name;

 public:
  Test() = delete;  // deleting default constructor make sure program does not use it to create more shallow copies by assignment operator
  Test(int id, string name) : _id(id), _name(name) {}
  ~Test() {
    // cout << " Object destroyed " << endl;
  }

  void print() { cout << _id << "-" << _name << endl; }

  /* overloaded operator < to compare based on name. If you want to compare based on ID, use Id here instead*/
  bool operator<(const Test& other) const { return _name < other._name; }
};

int main() {
  vector<Test> people;
  /* Object will be destroyed as soon as each line completes, a shallow copy will be saved in the vector */
  people.push_back(Test(1, "Mike"));
  people.push_back(Test(5, "Jack"));
  people.push_back(Test(3, "Raj"));
  people.push_back(Test(2, "Aliya"));
  people.push_back(Test(19, "Aamir"));

  /* creating an iterator will point to reference of the object of the vector, so no new object will be created */
  vector<Test>::iterator it;

  cout << endl;
  for (it = people.begin(); it != people.end(); it++) {
    it->print();
  }

  cout << endl;

  /* sort the elements on the vector ad per their name */
  sort(people.begin(), people.end());

  /* Alternatively you can also print using normal iterator, Here also no new object is created */
  for (uint i = 0; i < people.size(); i++) {
    people[i].print();
  }

  return 0;
}
