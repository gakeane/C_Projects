
#include "BinaryTree.h"

// default constructor
BinaryTree::BinaryTree() {
  root = NULL;
}

// constructor given root location (note this isn't a copy constructor)
BinaryTree::BinaryTree(Node* r) {
  root = r;
}

// default constructor
BinaryTree::~BinaryTree() {
  if (root != NULL) {
    delete root;
  }
}

// add method for a data element
Node* BinaryTree::insert(int data) {

  Node* n = new Node(data);
  
  // case when tree is empty
  if (root == NULL) {
    root = n;
    return(root);
  }
   
  Node* curr = root;
  Node* prev = root;

  while (curr != NULL) {

    prev = curr;
    
    if (data <= curr->data) {
      curr = curr->left;
    }
    else {
      curr = curr->right;
    }
  }

  if (data <= prev->data) {
    prev->left = n;
  }
  else {
    prev->right = n;
  }

  return (root);
}

// add method for a pointer to a node
Node* BinaryTree::insert(Node* n) {

  // case when tree is empty
  if (root == NULL) {
    root = n;
    return(root);
  }

  Node* curr = root;
  Node* prev = root;

  // move through tree until we find the posistion of the node
  while (curr != NULL) {

    prev = curr;
    
    if (n->data <= curr->data) {
      curr = curr->left;
    }
    else {
      curr = curr->right;
    }
  }

  // add the node to either the left or right path
  if (n->data <= prev->data) {
    prev->left = n;
  }
  else {
    prev->right = n;
  }

  return (root);  
}

// recursive function to find an element in the Binary tree
Node* BinaryTree::find(int data) {

  if (root == NULL) {
    return (NULL);
  }

  else {
    return (find(data, root));
  }
}

Node* BinaryTree::find(int data, Node* r) {

  if (r == NULL) {
    return (NULL);
  }

  else if (r->data == data) {
    return (r);
  }

  else if (r->data > data) {
    return (find(data, r->left));
  }
  else {
    return (find(data, r->right));
  }
}

// recursive print method
void BinaryTree::print() {

  if (root == NULL) {
    cout << "TREE IS EMPTY" << endl;
  }
  else {
    print(root);
    cout << endl;
  }

  return;
}

void BinaryTree::print(Node* r) {

  if (r != NULL) {
    print(r->left);
    cout << r->data << " ";
    print(r->right);
  }

  return;
}
