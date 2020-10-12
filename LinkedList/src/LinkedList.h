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
  bool linearSearch(int key);
  void insert(int data, size_t index);
  void insertSort(int data);
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

bool LinkedList::linearSearch(int key) {
  if (head == nullptr) {
    return false;
  }
  Node* temp = head;
  while (temp != nullptr) {
    if (temp->data == key) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

void LinkedList::insert(int data, size_t index) {
  /* Validate */
  if (index < 0 || index > _size) {
    return;
  }
  /* Insert at the front */
  if (index == 0) {
    push_front(data);
  } else if (index == _size) {
    push_back(data);
  } else {
    Node *temp, *prev;
    temp = new Node;
    temp->data = data;
    prev = head;
    for (size_t idx = 0; idx < index; idx++) {
      prev = prev->next;
    }
    temp->next = prev->next;
    prev->next = temp;
    _size++;
  }
}

void LinkedList::insertSort(int data) {
  if (head == nullptr) {
    push_back(data);
  } else {
    Node *temp, *q = nullptr, *p = nullptr;
    temp = new Node;
    temp->data = data;
    p = head;
    while (p != nullptr && p->data < data) {
      q = p;
      p = p->next;
    }
    if (p == head) {
      temp->next = head;
      head = temp;
    } else {
      q->next = temp;
      temp->next = p;
      if (p == nullptr) {
        last = temp;
      }
    }

    _size++;
  }
}

LinkedList::~LinkedList() {}
