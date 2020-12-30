#include "BST.h"
#include "binaryTree.h"

void testCode() {
  BinaryTree binT;
  binT.createTree();
  binT.preOrder();
  std::cout << std::endl;
  binT.inOrder();
  std::cout << std::endl;
  binT.postOrder();
  std::cout << std::endl;
  std::cout << "Node :" << binT.countNodes() << " Height : " << binT.height() << std::endl;
}

void testCode2() {
  BST bst;
  bst.insert(50);
  bst.insert(30);
  bst.insert(40);
  bst.insert(10);
  bst.insert(60);
  bst.insert(20);

  bst.inorder();
  std::cout << std::endl;

  int key;
  std::cout << "Enter element to search :";
  std::cin >> key;

  Node* temp = bst.search(key);
  if (temp) {
    std::cout << "Element found " << temp->data << std::endl;
  } else {
    std::cout << "Element not found\n";
  }

  bst.Delete(bst.getRoot(), 10);
  bst.inorder();
  std::cout << std::endl;
}

int main() {
  // testCode();
  testCode2();
  return 0;
}