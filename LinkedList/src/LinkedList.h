#pragma once
#include <iostream>

using namespace std;

class Node {
 public:
  int data;
  Node* next;
};

class LinkedList {
 private:
  Node* head;
  Node* last;
  size_t _size;

 public:
  LinkedList();
  ~LinkedList();
  void push_back(int data);
  void push_front(int data);
  int pop_front();
  int pop_back();
  size_t size();
  int max();
  int min();
  bool empty();
  friend ostream& operator<<(ostream& os, const LinkedList& list);
};

LinkedList::LinkedList() : head(nullptr), last(nullptr), _size(0) {}

void LinkedList::push_back(int data) {
  if (head == nullptr) {
    head = new Node;
    head->data = data;
    head->next = nullptr;
    last = head;
    _size++;
  } else {
    Node* temp = new Node;
    temp->data = data;
    temp->next = nullptr;
    last->next = temp;
    last = temp;
    _size++;
  }
}

void LinkedList::push_front(int data) {
  Node* temp = new Node;
  temp->data = data;

  if (head == nullptr) {
    temp->next = nullptr;
    head = temp;
    last = head;
    _size++;
  } else {
    temp->next = head;
    head = temp;
    _size++;
  }
}

ostream& operator<<(ostream& os, const LinkedList& list) {
  if (list.head == nullptr) {
    return os;
  }
  Node* temp = list.head;
  while (temp != nullptr) {
    cout << temp->data << " ";
    temp = temp->next;
  }
  cout << "\n";
  return os;
}

int LinkedList::pop_front() {
  if (head == nullptr) {
    return -1;
  } else {
    Node* temp = head;
    int data = temp->data;
    head = head->next;
    delete temp;
    _size--;
    return data;
  }
}

int LinkedList::pop_back() {
  if (head == nullptr) {
    return -1;
  }

  Node* temp = head;

  /* Traverse till you get the address of last element */
  while (temp->next != last) {
    temp = temp->next;
  }

  int data = last->data;
  delete last;
  temp->next = nullptr;
  last = temp;
  _size--;
  return data;
}

size_t LinkedList::size() { return _size; }

int LinkedList::max() {
  int maxData = INT32_MIN;
  if (head == nullptr) {
    return maxData;
  }
  Node* temp = head;
  while (temp != nullptr) {
    if (temp->data > maxData) {
      maxData = temp->data;
    }
    temp = temp->next;
  }
  return maxData;
}

int LinkedList::min() {
  int minData = INT32_MAX;
  if (head == nullptr) {
    return minData;
  }
  Node* temp = head;
  while (temp != nullptr) {
    if (temp->data < minData) {
      minData = temp->data;
    }
    temp = temp->next;
  }
  return minData;
}

bool LinkedList::empty() {
  if (head == nullptr) {
    return true;
  }
  return false;
}

LinkedList::~LinkedList() {}
