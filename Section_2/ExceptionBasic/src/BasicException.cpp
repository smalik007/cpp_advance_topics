/*
 * Description - Basic Exception.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

void mightGoWrong() {
  bool error1 = false;
  bool error2 = true;

  // If error1 is true the function will return from here after throwing the error, it will not go to second if statement.
  if (error1) {
    // throw 8;
    throw "Something went wrong";
  }

  if (error2) {
    throw string("Something else went wrong");
  }
}

void usesMightGoWrong() { mightGoWrong(); }

int main() {
  cout << "Hello\n";
  try {
    // mightGoWrong();
    usesMightGoWrong();  // Nested function calls can also catch exceptions
  } catch (int e) {
    cout << "Error Code " << e << endl;
  } catch (const char* e) {
    cout << "Error Msg : " << e << endl;
  } catch (string& e) {
    cout << "Error Msg : " << e << endl;
  }
  cout << "Still running\n";
  return 0;
}