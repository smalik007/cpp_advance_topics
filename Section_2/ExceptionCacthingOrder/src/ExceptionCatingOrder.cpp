/*
 * Description - ExceptionCacthingOrder.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <exception>
#include <iostream>
using namespace std;

void mightGoWrong() {
  const bool error1 = false;
  const bool error2 = true;

  if (error1) {
    throw bad_alloc();
  }
  if (error2) {
    throw exception();
  }
}

int main() {
  cout << "Hello\n";

  /* bad_alloc is a subclass member of exception class, So if the error is of bad_alloc type below code can handle the both bad_alloc and exception
   type, But important thing here is to note that is the exception will handle the bad_alloc type instead of bad_alloc exception, And that's the
   we are getting the below warning. */

  /* uncomment to see the warning
    Not recommended below code */

  // try {
  //   mightGoWrong();
  // } catch (exception& e) {
  //   cout << "Catching exception : " << e.what() << endl;
  // } catch (bad_alloc& e) {
  //   cout << "Catching bad_alloc : " << e.what() << endl;
  // }

  /* Hence it is important to cathch the sub class exception first before the base class. Otherwise the order will be of no use and all the
   exception will be catched by base class only. */

  // This is the correct way to write it

  try {
    mightGoWrong();
  } catch (bad_alloc& e) {
    cout << "Catching bad_alloc : " << e.what() << endl;
  } catch (exception& e) {
    cout << "Catching exception : " << e.what() << endl;
  }

  return 0;
}