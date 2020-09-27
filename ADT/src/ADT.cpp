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

  /* Validate capacity */
  if (this->capacity < l) {
    autoCapacity(l);
  }

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

void Array::autoCapacity(int newCap) {
  this->capacity = newCap * 2;
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
    this->autoCapacity(this->capacity);
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
  /* Validate index */
  if (index < 0) {
    return;
  }

  for (int idx = length; idx > index; idx--) {
    if (this->full()) {
      this->autoCapacity(this->capacity);
    }
    this->A[idx] = this->A[idx - 1];
  }
  this->A[index] = x;
  length++;
}

int Array::remove(int index) {
  /* Validate index */
  if ((index < 0) || (index >= length)) {
    return -1;
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

int Array::linearSearch(int key) {
  if (this->empty()) {
    return -1;
  }

  for (int idx = 0; idx < length; idx++) {
    if (this->A[idx] == key) {
      return idx;
    }
  }

  return -1;
}

int Array::binarySearch(int key) {
  if (this->empty()) {
    return -1;
  }
  if (!this->isSorted(ASSENDING)) {
    std::cout << "Error : Can't Perform binary Search elements are not sorted\n";
    return -1;
  }

  int start = 0;
  int end = length - 1;
  int mid = 0;
  while (start <= end) {
    mid = (start + end) / 2;

    if (this->A[mid] == key) {
      return mid;
    } else if (this->A[mid] < key) {
      start = mid + 1;
    } else {
      end = mid - 1;
    }
  }
  return -1;
}

int Array::get(int index) {
  /* Validate index */
  if ((index < 0) || (index >= length)) {
    return -1;
  }
  return this->A[index];
}
void Array::set(int index, int x) {
  /* Validate index */
  if ((index < 0) || (index >= length)) {
    return;
  }

  this->A[index] = x;
}

void Array::swap(int* x, int* y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void Array::reverse() {
  for (int i = 0, j = length - 1; i <= j; i++, j--) {
    swap(&this->A[i], &this->A[j]);
  }
}

void Array::merge(Array* obj) {
  int i = 0, j = 0, k = 0;

  int* temp = new int[sizeof(int) * (this->capacity + obj->capacity)];

  while (i < this->length && j < obj->length) {
    if (this->A[i] < obj->A[j])
      temp[k++] = this->A[i++];
    else
      temp[k++] = obj->A[j++];
  }

  /* Fill remaining element of the arrays that did not finish in above loop
  Only one of the below loop will execute, As the other would have been already exhuasted in above while */
  for (; i < this->length; i++) temp[k++] = this->A[i];

  for (; j < obj->length; j++) temp[k++] = obj->A[j];

  this->length = this->length + obj->length;
  this->capacity = this->capacity + obj->capacity;

  freeMem();
  this->A = temp;
}

/* If at any idex element is equal in both the array include on one from that index */
void Array::Union(Array* obj) {
  int i = 0, j = 0, k = 0;

  int* temp = new int[sizeof(int) * (this->capacity + obj->capacity)];

  while (i < this->length && j < obj->length) {
    if (this->A[i] < obj->A[j])
      temp[k++] = this->A[i++];
    else if (this->A[i] > obj->A[j])
      temp[k++] = obj->A[j++];
    else {
      temp[k++] = this->A[i++];
      j++;
    }
  }

  /* Fill remaining element of the arrays that did not finish in above loop
  Only one of the below loop will execute, As the other would have been already exhuasted in above while */
  for (; i < this->length; i++) temp[k++] = this->A[i];

  for (; j < obj->length; j++) temp[k++] = obj->A[j];

  this->length = k;
  this->capacity = this->capacity + obj->capacity;

  freeMem();
  this->A = temp;
}

/* If at any idex element is equal only Include them */
void Array::intersection(Array* obj) {
  int i = 0, j = 0, k = 0;

  int* temp = new int[sizeof(int) * (this->capacity + obj->capacity)];

  while (i < this->length && j < obj->length) {
    if (this->A[i] < obj->A[j])
      i++;
    else if (this->A[i] > obj->A[j])
      j++;
    else {
      temp[k++] = this->A[i++];
      j++;
    }
  }

  this->length = k;
  this->capacity = this->capacity + obj->capacity;

  freeMem();
  this->A = temp;
}