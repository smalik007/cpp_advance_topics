/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

template <class T>
/* Alternatively you can also use below syntax, some prefer this */
// template <typename T>

void print(T var) {
  cout << "Template version : " << var << endl;
}

void print(int var) { cout << "Non-Template version : " << var << endl; }

int main() {
  print<string>("Mike");
  print<double>(2.4);

  /* Compiler implicity finds out the type for you */
  print("Hi I am there");

  /* the most similar reference would be the function with exact type and the non-template version will overload the template version here */
  print(5);

  /* Here we are actully telling the compiler to look for the template version, even if we didn't provide the type, the type will be automatically found by compiler looking by the argument, but the
   * dimond operator make sure the compiler use the template version of the function */
  print<>(6);
  print<int>(8);
  return 0;
}
