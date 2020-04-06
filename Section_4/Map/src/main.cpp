/*
 * Description - Basic Exception.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <map>
using namespace std;

int main() {
  /* Map creates a look up table to store data against a unique key value.
    Syntax: map<key_type, data_type> var; */
  map<string, int> people;
  /* To add values to map we use overloaded array subcript operator as below
   */
  people["Mike"] = 40;
  people["Raj"] = 20;
  people["Joey"] = 35;

  cout << "Joey is " << people["Joey"] << " yrs old " << endl;
  cout << "Sue is " << people["Sue"] << " yrs old " << endl;  // Accessing an non existing key will return 0 value, and register it

  people["Joey"] = 30;  // overwrite the value
  cout << "Joey is " << people["Joey"] << " yrs old " << endl;

  /* Getting an iterator */
  map<string, int>::iterator it = people.begin();

  // find function
  // const string findPerson = "Vicky";
  // const string findPerson = "Sue";
  const string findPerson = "Mike";
  it = people.find(findPerson);  // retruns pointer to the element if found, else return map.end();
  if (it != people.end()) {
    cout << findPerson << " exist in map, has value " << it->second << endl;
  } else {
    cout << findPerson << " doesn't exist in the map" << endl;
  }

  cout << endl;
  for (it = people.begin(); it != people.end(); it++) {
    cout << it->first << "-" << it->second << endl;
  }

  /* You can also use below method to fill elements in map */
  pair<string, int> age("Peter", 50);
  people.insert(age);

  // cout << age.first << " is " << age.second << " yrs old" << endl;

  /* Alternative more simpler sintax */
  people.insert(make_pair("Haward", 20));
  cout << endl;
  /* Notice Map itself sort in alpha Numeric assending order*/
  for (it = people.begin(); it != people.end(); it++) {
    pair<string, int> getMap = *it;
    cout << getMap.first << "-" << getMap.second << endl;
  }

  return 0;
}
