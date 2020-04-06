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

int main() {
  /* Multimaps lets you store values with duplicate keys, Though it is recommended not to use it
    and instead use the map with custom key values like vector or a class type.
  */
  multimap<int, string> lookup;  // taking integer as the key

  /* Multimap does not have an overloaded array square bracket operator to add values, so we need to
    use the insert method to add values in it
  */
  lookup.insert(pair<int, string>(30, "Mike"));
  /* You can also use below syntax where you don't have to specify the type*/
  lookup.insert(make_pair(20, "Raj"));
  lookup.insert(make_pair(30, "Joey"));  // here note key value is same as above for Mike, in normal it would have overwritten the Mike to Joey
  lookup.insert(make_pair(40, "Monica"));

  /* Get iterator */
  multimap<int, string>::iterator it = lookup.begin();

  for (it = lookup.begin(); it != lookup.end(); it++) {
    cout << it->first << "-" << it->second << endl;
  }
  cout << endl;

  /* If you want to find all the values matching in map, you might not get a expected result
    with below code */
  for (it = lookup.find(30); it != lookup.end(); it++) {
    cout << it->first << "-" << it->second << endl;
  }

  cout << endl;

  /* We need an iterator which define a range or equal to value and look through it */
  pair<multimap<int, string>::iterator, multimap<int, string>::iterator> its = lookup.equal_range(30);

  for (it = its.first; it != its.second; it++) {
    cout << it->first << "-" << it->second << endl;
  }

  /* A far more simpler version of it */
  cout << endl;

  /* In c++11 auto , automatically gets the type for you */
  auto its2 = lookup.equal_range(30);

  for (it = its2.first; it != its2.second; it++) {
    cout << it->first << "-" << it->second << endl;
  }

  return 0;
}
