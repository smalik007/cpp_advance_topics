/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <map>
using namespace std;

class Person {
 private:
  string _name;
  int _age;

 public:
  Person() {}  // Default constructor, try commenting it out.
  Person(string name, int age) : _name(name), _age(age) {}
  void print() { cout << _name << ":" << _age << endl; }
  ~Person() {}
};

int main() {
  /* Map creates a look up table to store data against a unique key value.
    Syntax: map<key_type, data_type> var; */
  map<int, Person> people;

  /* It is important here to note that is, the map operator first create an object of the claass with empty args constructor, and then call
    the second constructor to assign the values, if the default constructor is not provided, you will get an error here.*/
  people[2] = Person("Mike", 30);
  people[0] = Person("Sam", 20);
  people[1] = Person("Raj", 50);

  map<int, Person>::iterator it;
  for (it = people.begin(); it != people.end(); it++) {
    cout << it->first << "-";
    it->second.print();
  }

  /* To add values to map we use overloaded array subcript operator as below
   */

  return 0;
}
