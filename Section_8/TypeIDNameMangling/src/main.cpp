/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <typeinfo>
using namespace std;

int main() {
  /* Typid is a useful function and gives you the type of the variable */
  int value;
  cout << typeid(value).name() << endl;

  double value2;
  cout << typeid(value2).name() << endl;

  char c;
  cout << typeid(c).name() << endl;

  /* Lets try some c++ types, which are not available in c */
  /* In case of c program, when we look to the binary file, it includes actual name of the program, but with c++ you can overload functions and attach functions to objects and classes(like friend),
   * that means the binary file needs more information about the context about the version of the function you are using is it a overloaded function or a direct call or does it belongs to a class(as
   * we know each class is seperately compiled and have .o output file), So c++ does this Name Mangling in which it takes the names of things like functions variables and classes and adds overloaded
   * characters to them to get more information about what they are, which overloaded function we are dealing with does it belong to a class etc */

  string str;
  /* String being c++ feature, have more info and is a example of Name mangling, thus the below output will be a linked connection of different files pointing to string somewhere */
  cout << typeid(str).name() << endl;

  /* There is another useful function Decltype which automatically finds the type a passed armunt and canbe used as an alternative to template/typename T */
  decltype(str) another_var = "Bob";
  cout << typeid(another_var).name() << endl;
  cout << another_var << endl;

  return 0;
}
