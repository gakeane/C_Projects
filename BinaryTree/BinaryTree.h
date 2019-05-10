
#include "Node.h"

class BinaryTree {
public:

  // datastructure
  Node* root;

  // constructors
  BinaryTree();
  BinaryTree(Node* r);

  // destructors
  ~BinaryTree();

  // add methods
  Node* insert(int data);
  Node* insert(Node* n);

  // search methods
  Node* find(int data);
  Node* find(int data, Node* r);
  
  // print methods
  void print();
  void print(Node* r);
};
