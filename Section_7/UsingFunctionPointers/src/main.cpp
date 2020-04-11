/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <algorithm>  // for count_if function
#include <iostream>
#include <vector>
using namespace std;

int sum(int a, int b) { return (a + b); }

bool match(string str) {
  uint no_char = 3;
  return str.size() == no_char;
}

int countString(vector<string> str, bool (*pMatch)(string str)) {
  int tally = 0;

  vector<string>::iterator it = str.begin();
  for (; it != str.end(); it++) {
    if (pMatch(*it)) {
      tally++;
    }
  }
  return tally;
}

int main() {
  int (*pLambda)(int, int) = sum;

  cout << "Sum : " << pLambda(2, 3) << endl;

  vector<string> numbers;

  numbers.push_back("one");
  numbers.push_back("two");
  numbers.push_back("three");
  numbers.push_back("four");
  numbers.push_back("five");
  numbers.push_back("six");
  numbers.push_back("seven");
  numbers.push_back("eight");
  numbers.push_back("nine");
  numbers.push_back("ten");

  /* If we say want to check how many element in the vector has 3 character string we can use a function as count_if() */
  cout << count_if(numbers.begin(), numbers.end(), match) << endl;

  /* To make you own count_if function lets try */
  cout << countString(numbers, match) << endl;

  return 0;
}
