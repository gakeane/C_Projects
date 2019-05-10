
#include <iostream>

using namespace std;

void print();

class Node {
public:

  // data structure
  int data;
  Node* next;
  Node* prev;

  // constructors
  Node();
  Node(int d);

  // destructors
  ~Node();

};
