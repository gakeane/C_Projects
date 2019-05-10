
#include <iostream>

using namespace std;

class Node {
public:

  // datastructure
  int data;
  Node* left;
  Node* right;

  // constructors
  Node();
  Node(int d);

  // destructors
  ~Node();
};
