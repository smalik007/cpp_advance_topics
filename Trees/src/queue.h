#pragma once
#include <iostream>

/* Node for doubly linked-List */
class Node {
 public:
  int data;
  Node* lchild;
  Node* rchild;
};

class Queue {
 private:
  int _size;
  int _rear;
  int _front;
  Node** Q; /* An Array pointer of type Node (pointer to a pointer) */

 public:
  explicit Queue(int size) : _size(size) {
    this->_front = this->_rear = 0;
    this->Q = (Node**)new Node[_size]; /* Create an array of type Node, Pointer stored in array with of Node type */
  }
  void enqueue(Node* x);
  Node* dequeue();
  bool isEmpty();
};

void Queue::enqueue(Node* x) {
  if ((this->_rear + 1) % this->_size == this->_front) {
    std::cout << "Queue is full can't add more elements\n";
  } else {
    this->_rear = (this->_rear + 1) % this->_size;
    this->Q[_rear++] = x;
  }
}

Node* Queue::dequeue() {
  Node* x = nullptr;
  if (this->_front == this->_rear) {
    std::cout << "Queue is Empty!!\n";
  } else {
    this->_front = (this->_front + 1) % this->_size;
    x = this->Q[this->_front];
  }
  return x;
}

bool Queue::isEmpty() { return this->_rear == this->_front; }