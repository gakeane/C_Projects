
#include "Node.h"

class LinkedList {
public:

  // data structure
  int length;
  Node* head;
  Node* tail;

  // constructors
  LinkedList();
  LinkedList(Node* h);

  ~LinkedList();

  // add methods
  Node* add(int data);
  Node* add(Node* n);

  // print methods
  void print();
};
