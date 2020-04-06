/*
 * Description - main.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Test {
 private:
  string _name;

 public:
  Test(string name) : _name(name) {}
  ~Test() {
    /* Uncomment print how the objects are getting destroyed */
    // cout << "Object Destroyed " << endl;
  }

  void print() { cout << _name << endl; }
};

int main() {
  cout << "Stack" << endl;
  /* Stack is Last in First out (LIFO) structure, it's interesting that we use stack all the time but doesn't always realize it, Stack is being used by the program for storing variables in the memory,
   * also when we call a function all the data variable are stored in stack of the calling function before jumping to the next.
   */
  stack<Test> myStack;

  /* Here a very important concept is that these below object when created get a shallow copy stored in the stack and the object here will be immidiatly be destroyed
   after as soon as each of the below statement completes */
  myStack.push(Test("Mike"));
  cout << "1." << endl;  // Putting extra endl so that you can see the object gets destroyed after the statement and only the copy of the object reside in the stack, which again will be destroyed when
                         // main terminates
  myStack.push(Test("Joey"));
  cout << "2." << endl;
  myStack.push(Test("Mike"));
  cout << "3." << endl;
  myStack.push(Test("Monica"));
  cout << "4." << endl;

  cout << endl;

  /* You can't iterate through the stack, you only pop from top or check what's on the top*/
  /* When you use the assignment operator here you are actually creating a copy again from the stack and this copy is basically assign to test1 beloy and get destroyed after the program ends */
  // Test test1 = myStack.top();
  // test1.print();
  // cout << endl;

  /* If you want a actual intance of the stack you might want to use it by reference, here in this case no extra object will be
    created instead the same reference will returned from the stack */
  // Test& test2 = myStack.top();
  // cout << "1. " << endl;

  /*If you pop the top element here you also destroyed the object refrenced by test2 */
  // myStack.pop();

  /* This is invalid and should not be used, it may work coz something else might not have accessed this memory but this should be avoided.*/
  // test2.print(); // reference refers to destroyed object. This is a very hard kind of bug to find so be aware of that

  cout << endl;

  while (myStack.size() > 0) {
    Test& testPop = myStack.top();
    testPop.print();
    myStack.pop();
  }

  cout << endl << "Queue" << endl << endl;

  /* First in First out (FIFO), The same concept of objects applies here as well, only fundamental difference is in sequence the data is accessed */
  queue<Test> myQueue;

  myQueue.push(Test("Mike"));
  myQueue.push(Test("Joey"));
  myQueue.push(Test("Mike"));
  myQueue.push(Test("Monica"));

  /* You can use front or back to access first and the last element */
  myQueue.front().print();
  myQueue.back().print();

  cout << endl;

  while (myQueue.size() > 0) {
    Test& testPop = myQueue.front();
    testPop.print();
    myQueue.pop();
  }

  cout << endl;

  return 0;
}
