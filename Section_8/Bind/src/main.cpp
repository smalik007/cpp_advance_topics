/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <functional>
#include <iostream>

using namespace std;
using namespace placeholders;

int add(int a, int b, int c) {
  cout << "a : " << a << ", b : " << b << ", c : " << c << endl;
  return (a + b + c);
}

/* if add were a method of a class */
class Test {
 public:
  int add(int a, int b, int c) {
    cout << "a : " << a << ", b : " << b << ", c : " << c << endl;
    return (a + b + c);
  }
};

int run(function<int(int, int)> func) { return func(3, 7); }

int main() {
  /* Binding did exist earlier as well but you had to use the boost library, with c++11 there's a provision to use bindig directly with its new features, Binding creates aliases for functions as a
   * function pointers  */

  cout << add(1, 2, 3) << endl;

  /* lets create a simple alias using bind */
  auto sum = bind(add, 3, 2, 5);
  /* Now every time you call sum (an alias) it will call add with already supplied arguments */
  cout << sum() << endl;

  /* you may even supply the arguments using placeholders like this, we have already using namespace placeholders, the first argument is jus to show how we can use where namspace is not declared */
  /* here _1, _2, _3 has a significance interms of placeholders they represent the sequence in which param is passed to the function */
  auto sum1 = bind(add, placeholders::_1, _2, _3);
  cout << "sum1: " << sum1(10, 20, 30) << endl;

  /* If you do something like this you are telling that the first argument passed to sum3 would be the 2nd argument to add function */
  auto sum2 = bind(add, _2, _1, _3);

  /* check the add output a, b , c values*/
  cout << "sum2: " << sum2(10, 20, 30) << endl;

  /* You may also use some values to be place holders and other as fixed values like this */
  auto sum3 = bind(add, _2, 100, _1);

  /* Here even if you pass the third argument as something different than above 100, this will only take 100 */
  cout << "sum3: " << sum3(10, 20) << endl;

  /* we can also use the alias with std::function like this, this will take second fix value as 100 , and other given by run method */
  cout << run(sum3) << endl;

  Test testObj;
  /* you have to pass Test by reference and testObj as the first argument */
  auto sum4 = bind(&Test::add, testObj, _2, _1, _3);
  /* check the add output a, b , c values*/
  cout << "sum4: " << sum2(10, 20, 30) << endl;

  return 0;
}
