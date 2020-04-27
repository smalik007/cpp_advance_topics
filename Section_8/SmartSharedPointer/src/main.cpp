/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <memory>  // include for smart pointers
using namespace std;

class Test {
 public:
  Test() { cout << "Constructor is called" << endl; }
  ~Test() { cout << "Destructor is called" << endl; }
  void greet() { cout << "Hello" << endl; }
};

int main() {
  /* Shared pointers are similar to unique pointers with a added twist that it does not delete the memory allocated by your objects, untill all the pointers that points to the object goes out of
   * scope. You can't however use the shared pointers as array in c++11 */

  // shared_ptr<Test> ptest(new Test());
  /* More efficient way is to make_shared template like this */

  /* initialize the ptest1 with nullptr, you can also use () intead of {}, but {} can be used to initialize any value type in c++11 */
  shared_ptr<Test> ptest1{nullptr};

  /* let's make ptest2 score restricted and see when this object is getting destroyed */
  {
    shared_ptr<Test> ptest2 = make_shared<Test>();

    /* if you comment below line ptest2 object would be detroyed as the scope is limited to these bracket, but if we put this line of code here, the ptest2 object will not be destroyed untill ptest is
     * destroyed, so you will see the Destructor called after the Finished print, while you comment below line you will see destructor called before finished print  */
    ptest1 = ptest2;
  }

  cout << "Finished" << endl;

  return 0;
}
