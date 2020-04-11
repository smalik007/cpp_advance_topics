/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <vector>
using namespace std;

/* This give us an error as the auto can't find the type of the return value */
// auto test() {
//   return 2;
// }

/* To make this work we need to give a trailing type return type like this, now one may say what the point of doing that, But it can be actually helpul when having some kind of template type return
   values , Alternative syntax : auto test() -> decltype(a_variable)*/
auto test() -> int { return 2; }

template <class T>
auto test2(T var) -> decltype(var) {
  return var;
}

template <class S, class T>
auto test3(S value1, T value2) -> decltype(value1 + value2) {
  return value1 + value2;
}

int get() { return 999; }

/* we can even pass a function to decltype wich will take the return type of whaterver the get is of */
auto test4() -> decltype(get()) { return get(); }

int main() {
  /* Auto can automatically find out the type by the right hand assigned assigned value and can be very helpful when declaring a long type/ complex or hard to remember types in c++, we can also use
   * auto in function types*/
  auto value = 7;
  auto text = "Bob";

  cout << value << " " << text << endl;

  vector<string> people;
  people.push_back("Mike");
  people.push_back("Bob");
  people.push_back("Anamika");
  people.push_back("jenny");

  /* Here auto automaticaaly assign the type as an iterator */
  auto it = people.begin();

  for (; it != people.end(); it++) {
    cout << *it << endl;
  }

  cout << test2("Hello") << endl;
  /* one value is int other is double, the return type will be auto dudicalable from test3() function */
  cout << test3(2, 4.5) << endl;

  cout << test4() << endl;

  return 0;
}
