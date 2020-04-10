/*
 * Description - main.cpp
 *
 * A template class is a class where user can define the type of the members. as an example you can think vector<type> is template class where we can deine the type to be any when we are going to use
 * it. It should not be limited to a perticular type like int or string etc.
 *
 * While implementing a class we usually declare a class in .h file and the implementation in a seperate .cpp file. Then when compiler compiles the program it only need look at to header, and it can
 * seprately compile the .cpp file into an object file(.o output files), and finally the linker link the implementation part.
 *
 * But that's not the case with class with templates, coz compiler has to see both the implementation and the header together, as the compiler doesn't know the template type what they are going to be
 * and it needs to assign the memory as per the defined types, So it's better to put the declaration and defination of class of template type in a single file(mostly in a .h file).
 *
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

template <class T>

class Test {
 private:
  T _var;

 public:
  Test(T var) : _var(var) {}
  ~Test() {}

  /* This a very bad implementation here, as we are not sure the what the type of T is and whether the cout ostream support the type to simply print it. Also it is not advisable to write if else
   * statements where we first check if the type is this do this if type is that do that, coz that just loose the whole concept of OOP and is a bad practice
   * This is just for demostration purpose we are creating this function, ideally a template class is used to store the objects of various types  */
  void print() { cout << _var << endl; }
};

int main() {
  Test<string> test1("Mike");
  Test<int> test2(10);

  test1.print();
  test2.print();
  return 0;
}
