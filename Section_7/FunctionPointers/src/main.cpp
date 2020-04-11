/*
 * Description - main.cpp
 *
 * Function Pointer has been there since the begining of the c++, but in c++11 we can use lambda expression to simplify things. Like we assign a pointer to a variable we can also assign a pointer to a
 * function and we can use the same pointer to call the function istead of calling function directly. You have probably using this feature without even knowing, While using the virtual funtion the c++
 * make a virtual table of these funciton and stores them as a pointer, So when you define the function in a derived class and later call it, the program lookup in this table for the pointer to call
 * the right funtion
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
using namespace std;

void print(int value) { cout << "Value :" << value << endl; }

int main() {
  /* Normal call */
  print(7);

  /* define pointer of type function to be pointed, () brackets tell the compiler it's a pointer to a function */
  void (*pLamda)(int);

  /* Assign the pointer to desired function. Here we have explcity added & at right hand side but the function also actully mean the address to the function so without & sign this will still be a
   * valid statement */
  pLamda = &print;

  /* Alternatively */
  // pLamda = print;

  /* Derefrence the pointer first which means you are accessing whatever the funtion may or may not return value, also () is required to call the funtion */
  (*pLamda)(8);

  /* Alternatively, since we know that the function is the address to the function and adding bracket defrences it so we can also use the following statement, this is equivalent to calling test() */
  pLamda(9);

  return 0;
}
