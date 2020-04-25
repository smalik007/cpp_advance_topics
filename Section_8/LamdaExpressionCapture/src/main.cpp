/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

int main() {
  int a = 1;
  int b = 2;
  string name{"Mike"};

  /* lamda expression has it's own scope and woul not have access to the local valriables defined above. We however can capture these values by passing them in the [] bracket as follows, but we can't
   * change the value of the variables in the lamda expression */
  [a, name]() { cout << a << "," << name << endl; }();

  /* we also pass all local variables by one by using = in the square bracket */
  [=]() { cout << a << "," << b << "," << name << endl; }();

  /* To make changes in the variable we would have to pass the variable by reference, So here all values are pass by value and b is passed by reference so we can modify it */
  [=, &b]() {
    b++;
    cout << a << "," << b << "," << name << endl;
  }();

  /* The value has changed */
  cout << b << endl;

  /* we can also pass all local variables by refrence using & in the square bracket */
  [&]() {
    name = "Monica";
    cout << ++a << "," << ++b << "," << name << endl;
  }();

  /* You can do something like this, where everything is passed by reference but, b is passed by value */
  [&, b]() {
    name = "Joy";
    cout << ++a << "," << b << "," << name << endl;
  }();

  /* There is still a way where without changing the passed value you can change the captured copy in lamda expression without changing the reference value, it will only change the capture copy value
   * localy like in any call by value function, to do that you have add a keyword mutable and compiler will alow it to change inside lamda expression  */

  int c = 5;
  /* c captured by value, still we can change the local copy */
  [c]() mutable {
    c = 9;
    cout << c << endl;
  }();

  /* value of c will not be changed here */
  cout << c << endl;

  return 0;
}
