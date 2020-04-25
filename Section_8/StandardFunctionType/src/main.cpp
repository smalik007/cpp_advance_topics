/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

bool check(string& test) { return (test.size() == 5); }

class Check {
 public:
  /* overloading () callable thing */
  bool operator()(string& test) { return test.size() == 3; }
};

/* defining a std function that can take anything that is callable and returns a bool and take string as paramenter */
// template<typename T>
int myCount(vector<string>::iterator beg, vector<string>::iterator end, function<bool(string&)> stdFunc) {
  int count = 0;
  string test;
  vector<string>::iterator it = beg;
  for (; it != end; it++) {
    test = *it;
    count += stdFunc(test);
  }

  /* here the stdFunc will call the respective defined method for the callable thing that run is called, just like in count_if function */
  return count;
}

int main() {
  Check ch1;

  uint size = 3;
  vector<string> numbers{"one", "two", "three"};
  auto lambda = [size](string text) { return text.size() == size; };

  /* count_if is a example of std function where in the third argument, it expect something callable which returns a bool and take the parameter of type iterator is pointing to */

  /* To count number of string with size = 3, here count_if call the lamda function */
  int count = count_if(numbers.begin(), numbers.end(), lambda);
  cout << count << endl;

  /* Alternatively instead of a lambda expression we can pass a functor, here count_if will call the check function */
  count = count_if(numbers.begin(), numbers.end(), check);
  cout << count << endl;

  /* We can even pass a object which calls the overloaded callable operator, here count_if will call the overloaded operator funtion */
  count = count_if(numbers.begin(), numbers.end(), ch1);
  cout << count << endl;

  /* Now let's see the same thing usin the run() funtion */

  cout << "using run" << endl;

  cout << myCount(numbers.begin(), numbers.end(), lambda) << endl;
  cout << myCount(numbers.begin(), numbers.end(), check) << endl;
  cout << myCount(numbers.begin(), numbers.end(), ch1) << endl;

  /* We can also make a variable of type callable using function */
  /* add is a callable type variable, which takes two int as param and return an iteger output */
  function<int(int, int)> add = [](int one, int two) { return one + two; };
  cout << "Add:" << add(3, 5) << endl;

  return 0;
}
