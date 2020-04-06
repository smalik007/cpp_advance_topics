/*
 * Description - CustomException.cpp
 * In this program, a class is created by deriving base std::exeption class and defining the it's own
 * what() method to throw custom exception.
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <exception>
#include <iostream>

using namespace std;

// here not much using the exception class, but it is alway a good practice to derive it.
// The code will still work if the exception class is not inherited.
class MyException : public exception {
 private:
  /* data */
 public:
  // override what() function from base class function to make custom exception types.
  virtual const char* what() const throw() { return "something bad happend"; }
};

class Test {
 public:
  void goesWrong() { throw MyException(); }
};

int main() {
  cout << "Hello\n";
  Test test;
  try {
    test.goesWrong();
  } catch (MyException& e) {
    cout << e.what() << endl;
  }
  return 0;
}