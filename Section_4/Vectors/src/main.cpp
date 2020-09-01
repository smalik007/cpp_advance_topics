/*
 * Description - Basic Exception.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

int main() {
  /* you can declare a vector with defined size, but it's size is not limited to 5 only unlike an array, we add more strings by
    calling the push_back() operation. So ideally you don't need to actually assign a size prior to a vector.
  */
  // vector<string> str(5);
  // str[3] = "dog";

  // // push_back funtion will create extra string from 5th string onwards
  // str.push_back("one");
  // str.push_back("two");

  // cout << str[3] << endl;
  // cout << str.size() << endl;
  // cout << str[5] << "," << str[6] << endl;

  vector<string> str;

  str.push_back("dog");
  str.push_back("one");
  str.push_back("two");

  cout << str.size() << endl;

  std::string mytest = str.front();
  cout << mytest << endl;

  std::string mytest2 = str.back();
  cout << mytest2 << endl;

  // cout << str[1] << endl;

  // one way to iterate through the vector

  // for (uint i = 0; i < str.size(); i++) {
  //   cout << str[i] << endl;
  // }

  // recommended way
  // begin give the pointer to the first element of the vector
  // end give the pointer after the end element of the vector (remember pointer will point to end element + next location)
  // vector<string>::iterator it = str.begin();
  // for (; it != str.end(); it++) {
  //   cout << *it << endl;
  // }

  std::queue <std::string> myList;
  myList.push("suhail");
  myList.push("malik");
  myList.push("Aliya");
  myList.push("Rohan");

  cout << myList.size() << endl;
  cout << myList.back() << " , " << myList.front() << endl;

  myList.pop();
  cout << myList.size() << endl;
  cout << myList.back() << " , " << myList.front() << endl;



  return 0;
}
