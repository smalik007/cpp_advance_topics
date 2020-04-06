/*
 * Description - Basic Exception.cpp
 *
 * @authors Suhail.m (suhail.m@greyorange.com)
 * @date    2020-04-04 13:02:05
 *
 */

#include <iostream>
#include <list>
using namespace std;

int main() {
  /* The fundamental difference between a list and vector is, in vector you can only push the data on top of and can access it by knowing
    the exact index whereas in a list you can add and modify the data in front, top, and between anywhere, list consist of nodes storing data
    and memory address of the next data, in a doubly linked list you have the address for next and prev node, accessing time thus is higher
    than the a vector or an array.
   */

  list<int> numbers;

  numbers.push_back(1);
  numbers.push_back(2);
  numbers.push_back(3);
  // Unlike a vector you can also push data at front of the list anytime.
  numbers.push_front(0);

  // similar to vectors you can create an iterator by this operator.
  list<int>::iterator it = numbers.begin();
  it++;

  /* you can aslo insert more data to the list like this, the insert function always add the new element to before the pointer element in list */
  // numbers.insert(it, 100);  // changing the 2 second element
  /* but it pointer is still working with previous begin pointer, so the print here would be difft than the below for loop */
  // cout << "Element:" << *it << endl;

  /* To correct above behaviour use following */
  it = numbers.insert(it, 100);  // changing the 2 second element
  /* This should now work fine. */
  cout << "Element:" << *it << endl;

  // To delete an element use this
  // similar to vectors you can create an iterator by this operator.
  list<int>::iterator eraseIt = numbers.begin();
  eraseIt++;

  /* Never do this below, as once erased you should not try to access it cause now the memory address it is pointing to is an
   unknown location and might even crash your code.*/

  //  numbers.erase(eraseIt);
  // cout << *eraseIt << endl:

  /* Instead use this*/
  // eraseIt = numbers.erase(eraseIt);
  // cout << *eraseIt << endl;

  // you can traverse by increamenting the it++ or it--, note you can't do it += 2, as you don't know the memory address of the next to next
  // node prior unlike vectors where the data is in contigous memory. Here it++ is overloaded and doesn't simply mean (it = it + 1) here it
  // gets assign the address of the next node automatically.
  for (it = numbers.begin(); it != numbers.end(); it++) {
    cout << *it << endl;
  }

  for (it = numbers.begin(); it != numbers.end(); it++) {
    if (*it == 2) {
      // do something
      numbers.insert(it, 101);  // you can also erase it
    }
    /* impt thing here to notice is that now that the element is deleted, the pointer is pointing to next element, So the for
      incrementer is actully incrementing it twice so you need to handle this, otherwise you may skip some data elements,
      it's advisable to use while loop in that case */
    // if (*it == 1) {
    //   numbers.erase(it);
    // }
  }

  cout << "\nList After adding new elemensts :\n";
  for (it = numbers.begin(); it != numbers.end(); it++) {
    cout << *it << endl;
  }

  it = numbers.begin();
  while (it != numbers.end()) {
    if (*it == 1) {
      it = numbers.erase(it);  // important to catch the new assign pointer here by back assigning it, otherwise the location
                               // will be unknown and you will get segment fault error here, try it here by deleting just assignment operation to it and
                               // on deleting it.
    } else {
      it++;
    }
  }

  cout << "\nList After deleting some elemensts :\n";
  for (it = numbers.begin(); it != numbers.end(); it++) {
    cout << *it << endl;
  }

  return 0;
}
