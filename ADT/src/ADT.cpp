#include "ADT.h"

#include <iostream>

// #include <stdlib.h> // for malloc

Array::Array(int s) : A(nullptr), capacity(s), length(0) {
  /* c++ syntax */
  this->A = new int[this->capacity * sizeof(int)];
  /* using malloc */
  //   this->A = (int*)malloc(this->size * sizeof(int));
}

Array::Array(int arr[], int l, int s) : A(nullptr), capacity(s), length(l) {
  this->A = new int[this->capacity * sizeof(int)];
  for (int idx = 0; idx < l; idx++) {
    this->A[idx] = arr[idx];
  }
}

void Array::freeMem() {
  if (this->A == nullptr) {
    return;
  }

  delete[] this->A;
  // free(this->A); /* for malloc */
  A = nullptr;
  //   std::cout << "Freed memory\n";
}

Array::~Array() { freeMem(); }

void Array::autoCapacity() {
  this->capacity = this->capacity * 2;
  int* tempA = new int[capacity * sizeof(int)];

  for (int idx = 0; idx < length; idx++) {
    tempA[idx] = this->A[idx];
  }
  this->freeMem();
  this->A = tempA;
}

bool Array::empty() {
  if (length == 0) {
    return true;
  }
  return false;
}
void Array::display() {
  if (this->empty()) {
    std::cout << "Array is empty\n";
    return;
  }

  for (int idx = 0; idx < length; idx++) {
    std::cout << this->A[idx] << " ";
  }
  std::cout << " size : " << length << " capacity : " << capacity << " \n";
}

bool Array::full() {
  if (length == capacity) {
    return true;
  }
  return false;
}
int Array::getCapacity() { return capacity; }

int Array::size() { return length; }

void Array::push(int x) {
  if (this->full()) {
    this->autoCapacity();
  }
  this->A[length++] = x;
}

int Array::pop() {
  if (this->empty()) {
    std::cout << "Error: No element to pop";
    return 0;
  }
  return this->A[--length];
}

void Array::insert(int index, int x) {
  for (int idx = length; idx > index; idx--) {
    if (this->full()) {
      this->autoCapacity();
    }
    this->A[idx] = this->A[idx - 1];
  }
  this->A[index] = x;
  length++;
}

int Array::remove(int index) {
  if (this->empty()) {
    std::cout << "Error : No element to delete";
    return 0;
  }

  int temp = this->A[index];

  for (int idx = index; idx < length - 1; idx++) {
    this->A[idx] = this->A[idx + 1];
  }

  length--;
  return temp;
}

int Array::max() {
  if (this->empty()) {
    return INT32_MIN;
  }

  /* TODO : Optimize
 1. check if sorted
 2. return last element as max */

  int max = this->A[0];
  for (int idx = 1; idx < length; idx++) {
    if (max < this->A[idx]) {
      max = this->A[idx];
    }
  }
  return max;
}

int Array::min() {
  if (this->empty()) {
    return INT32_MAX;
  }

  /* TODO : Optimize
 1. check if sorted
 2. return last element as max */

  int min = this->A[0];
  for (int idx = 1; idx < length; idx++) {
    if (min > this->A[idx]) {
      min = this->A[idx];
    }
  }
  return min;
}

int Array::sum() {
  if (this->empty()) {
    return 0;
  }

  int sum = 0;
  for (int idx = 0; idx < length; idx++) {
    sum += this->A[idx];
  }
  return sum;
}

float Array::avg() {
  if (this->empty()) {
    return 0.0;
  }

  float avg = this->sum();
  avg = avg / length;
  return avg;
}

bool Array::isSorted(sort_order_e order) {
  if (this->empty()) {
    return true;
  }
  for (int idx = 0; idx < length - 1; idx++) {
    if (DISSENDING == order) {
      if (this->A[idx] < this->A[idx + 1]) {
        return false;
      }
    } else {
      if (this->A[idx] > this->A[idx + 1]) {
        return false;
      }
    }
  }
  return true;
}