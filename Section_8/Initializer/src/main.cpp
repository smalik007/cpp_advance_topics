/*
 * Description - main.cpp
 *
 * c++11 uses {} to initialize almost all types
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <vector>
using namespace std;

int main() {
  /* c++11 initialization type {} instead of = */
  int var{5};
  cout << var << endl << endl;

  cout << "String:" << endl;
  string text{"Mike"};
  cout << text << endl;

  cout << endl << "Double Array" << endl;
  double numbers[]{1.2, 2.5, 6.7};
  for (auto number : numbers) {
    cout << number << endl;
  }

  cout << endl << "String Vector " << endl;
  vector<string> names{"Ross", "Joey", "Monica"};
  for (auto name : names) {
    cout << name << endl;
  }

  cout << endl << "iPtr" << endl;
  int* iPtr = new int[3]{1, 2, 3};
  /* Derenrence the pointer */
  cout << iPtr[1] << endl;
  delete[] iPtr;

  cout << endl << "Default value int" << endl;
  /* initialize to 0, in case of string initialize with empty string */
  int val2{};
  cout << val2 << endl;

  cout << endl << "Pointer" << endl;
  /* Initializes to nullptr(a keyword in c++11, No header file needed like for C-style NULL which is macro and casted to an interger) with empty {}, you can also assing it to point a value or some
   * other pointer of same type as well */
  int* pSomething{&var};
  cout << *pSomething << endl;

  cout << endl << "Struct" << endl;
  /* We can also use class and struct to initliaze using {} */

  struct S {
    int a;
    string name;
  };

  /* c++ 98 style */
  S s1 = {5, "Mike"};
  cout << s1.name << endl;
  /* c++11 style */
  S s2{3, "Joey"};
  cout << s2.name << endl;

  cout << endl << "Class" << endl;
  class C {
   private:
    int age;
    string name;

   public:
    C(int a, string n) : age(a), name(n) {}
    void print() { cout << "Age : " << age << ", Name : " << name << endl; }
  };

  C c1{10, "Ross"};
  c1.print();

  return 0;
}
