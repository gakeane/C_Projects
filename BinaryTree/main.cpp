
#include "BinaryTree.h"

int main () {
   
  BinaryTree tree;
  tree.insert(20);
  tree.insert(10);
  tree.insert(5);
  tree.insert(12);
  tree.insert(31);
  tree.insert(35);
  tree.insert(32);

  tree.print();

  Node* n = tree.find(31);

  if (n != NULL) {
    cout << n->data << endl;
  }
  else {
    cout << "Couldn't find node " << endl;
  }
  
  return (0);
}
