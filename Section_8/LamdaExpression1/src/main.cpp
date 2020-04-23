/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

void test(void(*pFunc())) { pFunc(); }

int main() {
  /* Below is the syntax of a lamda funtion, it's like function with no name and should compile without anything int it, uncomment and try to compile it */
  // []() {};

  /* Now let's implement something in it, it now a function but we will not get any out put as we never call this function. Though we can call it by putting to circle bracket befor ; */
  // []() { cout << "Hello" << endl; };
  // []() { cout << "Hello" << endl; }(); // This will call it but serve not much purpose.

  /* Lets assign a variable to it and call it , func here is functor and the type varies from lambda expression to lamda expression, in this case void*/
  auto func = []() { cout << "Hello" << endl; };

  func();

  /* we can pass it as param to other function which takes function pointer */
  test(func);

  test([]() { cout << "Hello again" << endl; });

  return 0;
}
