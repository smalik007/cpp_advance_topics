/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

class Parent {
 public:
  virtual void speak() { cout << "Parent" << endl; }
  virtual void defaultSpeak() { cout << "Default Parent" << endl; }

  /* This method here will make the Parent class abstract(coz of not implemented method) and will not allow to creat a instance of this class object, However we can define a Pointer of Parent type and
   * assign to any Derived type class  */
  virtual void someVirtual() = 0;
};

class Brother : public Parent {
 public:
  Brother() = delete;
  explicit Brother(int numb) : a(numb) {}
  void speak() override { cout << "Brother" << endl; }
  void defaultSpeak() override { cout << "Default Broter" << endl; }
  void someVirtual() override { cout << "virtual Brother method" << endl; }
  void brotherSpecific() { cout << "Brother specific function " << a << endl; }

 private:
  int a;
};

class Sister : public Parent {
  void speak() override { cout << "Sister" << endl; }
  void someVirtual() override { cout << "virtual Sister method" << endl; }
};

int main() {
  /* c++ 98 style/ c-style casting */
  float value = 3.2;
  cout << value << ", " << (int)value << endl;

  /* c++ 11, static_cast lets you cast anything to be of any other type(with some limitation, where we may need to use reinterpret_cast), it's a compile time casting */
  cout << endl << "Static Cast" << endl;
  cout << static_cast<int>(value) << endl;

  /* Lets see where the problem arises in static_cast */

  Parent* parent;
  Brother brother(5);
  Sister sister;

  /* Since Parent is Super/Base class and Brother and Sister are derived classes, Polymorphism allows us to do this */
  Parent* pointerParentToBrother = &brother;
  pointerParentToBrother->speak();

  Parent* pointerParentToSister = &sister;
  /* Should print Parent methos as not override in Sister Class */
  pointerParentToSister->defaultSpeak();

  /* Now lets see whar could go wrong with static_cast*/

  /* Here the pointerBrotherToBrother pointer will allow us to call Non virtual methods like brotherNonVirtual but since the pointer is pointing to a Parent/Sister type pointer where this function is
   * not defined will cause the program to crash, So static cast does not check these things and directly just type cast it but like in this situation the program could crash if we make a call to
   * brotherNonVirtual method using this pointer*/
  Brother* pointerBrotherToParent = static_cast<Brother*>(parent);

  /* Just to check a valid address is assigned (here though becoz of the newer version of the compiler we are getting a nullpointer address, So call to any of the member will not work)*/
  cout << pointerBrotherToParent << endl;

  /* This will crash your code, Since the method is not defined in the Parent class where the pointer is pointing to */
  // pointerBrotherToParent->someVirtual();

  cout << endl << "Dynamic Cast" << endl;

  /* Dynamic as the name suggest check on the runtime wheter the typecated value is valid or not in above it would simply return nullpointer here (Though above seems to be also returning a nullptr but
   * it's a good practice that we use the dynamic cast here)
   */
  /* A more useful example could be let say my Parent poiter could be pointing to a either Brother class or Sister Class using some if else scenario and our program doesn't know which one, later we
   * may want to use some specific function of Brother class using this Parent pointer, but we are not sure wheter the pointer is actually pointing to Brother class or Sister class, one way to handle
   * this could be to put all the specific method is the Parent itself and make notImplemented methods in Sister class and only implemented version in Sister class, other way can be using dynamic_cast
   * and cathing the invalid pointer address */

  Brother* pointerBrotherToParent2 = dynamic_cast<Brother*>(pointerParentToSister);
  /* This will crash the code as typeCast is invalid */
  // pointerBrotherToParent2->brotherSpecific();

  /* Proper way to Handle this */
  if (pointerBrotherToParent2 == nullptr) {
    cout << "Invalid cast handler1" << endl;
  } else {
    pointerBrotherToParent2->brotherSpecific();
  }

  /* Now this will work fine */
  pointerBrotherToParent2 = dynamic_cast<Brother*>(pointerParentToBrother);
  if (pointerBrotherToParent2 == nullptr) {
    cout << "Invalid cast handler2" << endl;
  } else {
    pointerBrotherToParent2->brotherSpecific();
    pointerBrotherToParent2->speak();
    pointerBrotherToParent2->defaultSpeak();
  }

  /* reinterpret_cast : reinterpret_cast just convert whaterver thing to whatever thing without any checks, This is again still lesser safer than the static cast and is compile type thing only. You
   * should all together avoid this. However in some cases where there's a bit complex code and compiler is giving an error with static/dynamic_cast, Programmer may use reinterpret_cast with his own
   * risk making sure whatever he is doing is valid  */

  return 0;
}
