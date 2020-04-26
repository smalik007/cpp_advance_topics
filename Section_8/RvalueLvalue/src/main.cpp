/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

class Test {
 public:
  Test() = default;
  /* copy constructor */
  Test(const Test& other) = default;
};

int getRandom() { return rand(); }

void check(const int& lValue) { cout << "lvalue check is running " << lValue << endl; }
void check(int&& rValue) { cout << "rValue check is running " << rValue << endl; }

int main() {
  /* In c++ 98 L value is defined if something is in the left hand side of the expression and R value for right hand side */
  /* we simply say value is L value, 7 is R value */
  int value = 7;

  /* c++11 the defination changes. An L value is something anything you can take the address of  */
  /* here value is actually a L value since we can take the address and store it in a pointer */
  int* pValue;
  pValue = &value;
  cout << *pValue << endl;
  /* However we can't do something below, as 7 is a R value and we can't take the memory address of it */
  // pValue = &7;

  /* Anoter example  with prefix operator, here prefix first increase the value and then assign the address to pointer, So it's a L value*/
  pValue = &(++value);
  cout << *pValue << endl;

  /* However, we can't do this with a post-fix value, here since postfix take a temporary value for a first operation and increment it, we can't take the address of an temporary value/element */
  // pValue = &(value++);

  /* similarly below expression will also be a R value, though value is L value but adding something in it make the whole expression as R value */
  // pValue = &(5 + value);

  /* The return value from a function is also a R value as the return value is stored in a temporary memory and you can't take the address of it */
  // pValue = &getRandom();

  /* L value References */
  cout << "L Value references" << endl;
  /* in c++ 98 we had references, which now in c++11 are catogries in L value references and R value references */
  /* A L value refrence can only take a Lvalue */

  Test test;

  /* Lvalue referece object bind to Lvalue object, this will even work in c++98  */
  Test& ltes1 = test;
  int& value1 = value;
  cout << value1 << endl;

  /* But we can't make a L value reference to an R value, This will give you an error */
  // int& value2 = getRandom();

  /* Though there still a way to make it work, by using const, what's happenning here is we have extended the life of of the returned value using const, it is no longer a stored as temporary, So as
   * long as the L value reference value3 exist it's scope exist   */
  const int& value3 = getRandom();
  cout << value3 << endl;

  /* R value References */
  cout << "R Value references" << endl;

  /* There are scenarios like in case of returned value from a function which is a temporary value stored, and compiler optimization may not detect it, it could cause problems, so if would want to
  have a handling mechanism for that we can do it using R value references */

  /* The syntax for R value reference looks like this, here && is not reference to a referece but has a special meaning here. */
  /* We can only bind R value refence to and R values */
  Test&& rtest = Test();
  int&& rvalue1 = getRandom();
  int&& rvalue2 = 90;
  cout << rvalue1 << "," << rvalue2 << endl;
  /* R value reference to L value like this will give you an error */
  // Test&& rtest1 = test;
  // int&& rvalue3 = value;

  int value4 = 10;
  cout << "Calling for rvalues" << endl;
  check(getRandom());
  check(7);
  check(value4++);

  cout << "Calling for lvalues" << endl;
  value4 = 5;
  check(value4);
  check(++value4);

  return 0;
}
