#pragma once
/* Description : Writing my own Vector Class */

class Array {
 private:
  int* A;
  int capacity;
  int length; /* current element in the array */
  void swap(int* x, int* y);
  void autoCapacity(int newCap);
  void freeMem();

 public:
  enum sort_order_e {
    ASSENDING = 0,
    DISSENDING = 1,
  };

 public:
  explicit Array(int c);
  explicit Array(int arr[], int l, int c); /* Create Array with some initial element */
  ~Array();

  void display();
  bool empty();
  bool full();
  void push(int x); /* Append */
  int pop();
  int getCapacity();
  int size();
  void insert(int index, int x);
  int remove(int index);

  int max();
  int min();
  int sum();
  float avg();

  bool isSorted(sort_order_e order = ASSENDING);
  int linearSearch(int key);
  int binarySearch(int key); /* Array needs to be sorted */

  int get(int index);
  void set(int index, int x);

  void reverse();
  void merge(Array* obj);
  void Union(Array* obj);
  void intersection(Array* obj);
};
