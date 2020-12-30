#pragma once
#include "queue.h"

class BinaryTree {
 private:
  Queue* storeNodes;
  Node* root;

 public:
  BinaryTree();
  void createTree();
  /* Dummy functions to call parameterize function in recursive */
  void preOrder() { preOrder(root); }
  void inOrder() { inOrder(root); }
  void postOrder() { postOrder(root); }

  void preOrder(Node* p);
  void inOrder(Node* p);
  void postOrder(Node* p);
  int countNodes();
  int countNodes(Node* p);
  int height();
  int height(Node* p);
};

BinaryTree::BinaryTree() {}

void BinaryTree::createTree() {
  storeNodes = new Queue(Queue(100));
  root = new Node;
  Node *p, *t;
  int x;
  std::cout << "Enter root Node: ";
  std::cin >> x;
  root->data = x;
  root->lchild = nullptr;
  root->rchild = nullptr;

  this->storeNodes->enqueue(root);

  while (!this->storeNodes->isEmpty()) {
    p = this->storeNodes->dequeue();

    /* if p is a nullptr continue the loop */
    if (!p) {
      continue;
    }

    std::cout << "Enter left child of : " << p->data << " ";
    std::cin >> x;
    if (x != -1) {
      t = new Node;
      t->data = x;
      t->lchild = nullptr;
      t->rchild = nullptr;
      p->lchild = t;
      this->storeNodes->enqueue(t);
    }

    std::cout << "Enter right child : " << p->data << " ";
    std::cin >> x;
    if (x != -1) {
      t = new Node;
      t->data = x;
      t->lchild = nullptr;
      t->rchild = nullptr;
      p->rchild = t;
      this->storeNodes->enqueue(t);
    }
  }
}

void BinaryTree::preOrder(Node* p) {
  if (p) {
    std::cout << p->data << " ";
    preOrder(p->lchild);
    preOrder(p->rchild);
  }
}

void BinaryTree::inOrder(Node* p) {
  if (p) {
    inOrder(p->lchild);
    std::cout << p->data << " ";
    inOrder(p->rchild);
  }
}

void BinaryTree::postOrder(Node* p) {
  if (p) {
    preOrder(p->lchild);
    std::cout << p->data << " ";
    preOrder(p->rchild);
  }
}

int BinaryTree::countNodes() {
  if (this->root) return countNodes(this->root->lchild) + countNodes(this->root->rchild) + 1;
  return 0;
}

int BinaryTree::countNodes(Node* p) {
  if (p) return countNodes(p->lchild) + countNodes(p->rchild) + 1;
  return 0;
}

int BinaryTree::height() {
  int x = 0, y = 0;
  if (root == 0) return 0;
  x = height(root->lchild);
  y = height(root->rchild);
  if (x > y)
    return x + 1;
  else
    return y + 1;
}

int BinaryTree::height(Node* p) {
  int x = 0, y = 0;
  if (p == 0) return 0;
  x = height(p->lchild);
  y = height(p->rchild);
  if (x > y)
    return x + 1;
  else
    return y + 1;
}