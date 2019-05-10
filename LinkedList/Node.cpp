
#include "Node.h"

Node::Node() {

  data = 0;
  next = NULL;
  prev = NULL;
}

Node::Node(int d) {

  data = d;
  next = NULL;
  prev = NULL;
}

Node::~Node() {

  if (next != NULL) {
    delete next;
  }
}

