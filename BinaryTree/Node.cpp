
#include "Node.h"

// default constructor
Node::Node() {

  data = 0;
  left = NULL;
  right = NULL;
}

Node::Node(int d) {

  data = d;
  left = NULL;
  right = NULL;
}

Node::~Node() {
  if (right != NULL) {
    delete right;
  }
  if (left != NULL) {
    delete left;
  }
}
