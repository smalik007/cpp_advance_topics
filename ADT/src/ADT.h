#pragma once
/* Description : Writing my own Vector Class */

class Array {
 private:
  int* A;
  int capacity;
  int length; /* current element in the array */
              //   void swap(int* x, int* y);
  void autoCapacity();
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
  //   int LinearSearch(Array* arr, int key);

  //   int BinarySearch(Array arr, int key);
  //   int RBinSearch(int a[], int l, int h, int key); /* Recursive */
  //   int Get(Array arr, int index);
  //   void Set(Array* arr, int index, int x);

  //   void Reverse(Array* arr);
  //   void InsertSort(Array* arr, int x);
  //   void Rearrange(Array* arr);
};
