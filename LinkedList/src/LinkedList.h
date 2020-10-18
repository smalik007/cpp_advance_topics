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
  int deleteItem(size_t index);
  bool isSorted();
  void reverse();
  void merge(LinkedList& second);
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

int LinkedList::deleteItem(size_t index) {
  /* check if the list is empty */
  if (this->empty()) {
    return -1;
  }

  /* Check For valid index */
  /* This check may not required as the index pass is already an unsigned var and we are checking size by checking if the traversing has not reached a nullptr */
  // if (index < 0 || index >= this->_size) {
  //   return -1;
  // }

  Node* temp;
  temp = head;
  int item = -1;
  if (index == 0) {
    head = head->next;
    this->_size--;
    item = temp->data;
    delete temp;
  } else {
    Node* prev;
    size_t i = 0;
    /* Check whether temp has not reached a null, For cases where index > size of the list is passed*/
    for (i = 0; i < index && temp; i++) {
      prev = temp;
      temp = temp->next;
    }

    /* Extra check in case our _size variable in not maintained correctly */
    if (temp == nullptr) {
      return -1;
    }

    prev->next = temp->next;
    item = temp->data;
    if (prev->next == nullptr) {
      this->last = prev;
    }
    this->_size--;
    delete temp;
  }
  return item;
}

bool LinkedList::isSorted() {
  /* empty list is always sorted */
  if (this->empty()) {
    return true;
  }
  bool return_status = true;
  Node* prev = head;
  Node* curr = head->next;
  while (prev != nullptr && curr != nullptr) {
    if (prev->data > curr->data) {
      return_status = false;
      break;
    }
    prev = curr;
    curr = curr->next;
  }

  return return_status;
}

void LinkedList::reverse() {
  if (this->empty()) {
    return;
  }
  /* using three pointer sliding */
  Node* p = head;
  Node* q = nullptr;
  Node* r = nullptr;

  while (p != nullptr) {
    /* slide pointers */
    r = q;
    q = p;
    p = p->next;

    /* reverse the link  */
    q->next = r;
  }
  /* new head after complete reverse */
  head = q;
}

void LinkedList::merge(LinkedList& secondList) {
  /* Validation */
  /* if current list is empty directly point to head of second list */
  if (this->empty()) {
    this->head = secondList.head;
  } else if (secondList.empty()) {
    /* if second list is empty no merging is required */
    return;
  }

  Node* first = this->head;
  Node* second = secondList.head;
  Node* mergedHead = nullptr;
  Node* lastMerged = nullptr;

  if (first->data < second->data) {
    mergedHead = lastMerged = first;
    first = first->next;
    lastMerged->next = nullptr;
  } else {
    mergedHead = lastMerged = second;
    second = second->next;
    lastMerged->next = nullptr;
  }

  while (first != nullptr && second != nullptr) {
    if (first->data < second->data) {
      lastMerged->next = first;
      lastMerged = first;
      first = first->next;
      lastMerged->next = nullptr;
    } else {
      lastMerged->next = second;
      lastMerged = second;
      second = second->next;
      lastMerged->next = nullptr;
    }
  }

  /* link for the remaining elements */
  if (first != nullptr) {
    lastMerged->next = first;
  } else {
    lastMerged->next = second;
  }

  /* new Head */
  this->head = mergedHead;

  Node* temp;
  temp = this->head;
  /* new Size */
  this->_size = this->_size + secondList.size();

  /* rearrange last element */
  while (temp != nullptr) {
    this->last = temp;
    temp = temp->next;
  }
}

LinkedList::~LinkedList() {}
