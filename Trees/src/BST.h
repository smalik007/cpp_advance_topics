#pragma once
#include "queue.h"

class BST {
 private:
  Node* root;

 public:
  BST() : root(nullptr) {}
  Node* getRoot() { return root; }
  void insert(int key);
  void inorder() { inorder(this->root); }
  void inorder(Node* p);
  Node* search(int key);
  Node* Delete(Node* p, int key);
  int Height(Node* p);
  Node* InPre(Node* p);
  Node* InSucc(Node* p);
};

void BST::insert(int key) {
  Node* p = root;
  Node* r = nullptr;
  Node* temp = nullptr;

  if (this->root == nullptr) {
    temp = new Node;
    temp->data = key;
    temp->lchild = nullptr;
    temp->rchild = nullptr;
    this->root = temp;
    return;
  }
  /* traverse and insert the node */
  while (p != nullptr) {
    r = p;
    if (key < p->data) {
      p = p->lchild;
    } else if (key > p->data) {
      p = p->rchild;
    } else {
      /* duplicate entry is not allowed */
      return;
    }
  }

  temp = new Node;
  temp->data = key;
  temp->lchild = temp->rchild = nullptr;

  if (key < r->data)
    r->lchild = temp;
  else
    r->rchild = temp;
}

void BST::inorder(Node* p) {
  if (p) {
    inorder(p->lchild);
    std::cout << p->data << " ";
    inorder(p->rchild);
  }
}

Node* BST::search(int key) {
  Node* p;
  p = root;

  while (p != nullptr) {
    if (key == p->data) {
      return p;
    } else if (key < p->data) {
      p = p->lchild;
    } else {
      p = p->rchild;
    }
  }
  return nullptr;
}

Node* BST::Delete(Node* p, int key) {
  Node* q;

  if (p == nullptr) {
    return nullptr;
  }

  if (p->lchild == nullptr && p->rchild == nullptr) {
    if (p == root) {
      root = nullptr;
    }
    delete p;
    return nullptr;
  }

  if (key < p->data) {
    p->lchild = Delete(p->lchild, key);
  } else if (key > p->data) {
    p->rchild = Delete(p->rchild, key);
  } else {
    if (Height(p->lchild) > Height(p->rchild)) {
      q = InPre(p->lchild);
      p->data = q->data;
      p->lchild = Delete(p->lchild, q->data);
    } else {
      q = InSucc(p->rchild);
      p->data = q->data;
      p->rchild = Delete(p->rchild, q->data);
    }
  }
  return p;
}

int BST::Height(Node* p) {
  int x;
  int y;
  if (p == nullptr) {
    return 0;
  }
  x = Height(p->lchild);
  y = Height(p->rchild);
  return x > y ? x + 1 : y + 1;
}

Node* BST::InPre(Node* p) {
  while (p && p->rchild != nullptr) {
    p = p->rchild;
  }
  return p;
}

Node* BST::InSucc(Node* p) {
  while (p && p->lchild != nullptr) {
    p = p->lchild;
  }
  return p;
}