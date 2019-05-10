
#include "LinkedList.h"

  // default constructor (creates empty list)
LinkedList::LinkedList() {
  head = NULL;
  tail = NULL;
  length = 0;
}

  // constructor creates list when given head node (can be head of another list)
LinkedList::LinkedList(Node* h) {
  head = h;
  length = 0;

  Node* curr = head;
  Node* prev = curr;

  while(curr != NULL) {
    length++;
    prev = curr;
    curr = curr->next;
  }

  tail = prev;
}

  // default destructor
LinkedList::~LinkedList() {
  if (head != NULL) {
    delete head;
  }
}

  // add a node to the linked list (nodes are added in assending order, smallest value at head)
Node* LinkedList::add(int data) {

  Node* n = new Node(data);
  length++;

  // case of an empty list
  if (head == NULL) {
    n->next = NULL;
    n->prev = NULL;

    head = n;
    tail = n;

    return(head);
  }

  // case where we add to the head of the list
  if (n->data <= head->data) {
    n->next = head;
    n->prev = NULL;

    head = n;

    return(head);
  }

  Node* prev = head;
  Node* curr = head;

  // move to the location for the data to be added
  while ((curr != NULL) && (n->data > curr->data)) {
    prev = curr;
    curr = curr->next;
  }

  // case where we add to the middle of the list
  if (curr != NULL) {
    n->next = curr;
    n->prev = prev;

    prev->next = n;
    curr->prev = n;

    return(head);
  }

  // case where node is added to the end of the list
  n->next = NULL;
  n->prev = prev;

  prev->next = n;
  tail = n;

  return(head);
}

  // add a node to the linked list (nodes are added in assending order, smallest value at head)
Node* LinkedList::add(Node* n) {
  length++;

  // case of an empty list
  if (head == NULL) {
    n->next = NULL;
    n->prev = NULL;

    head = n;
    tail = n;

    return(head);
  }

  // case where we add to the head of the list
  if (n->data <= head->data) {
    n->next = head;
    n->prev = NULL;

    head = n;

    return(head);
  }

  Node* prev = head;
  Node* curr = head;

  // move to the location for the data to be added
  while ((curr != NULL) && (n->data > curr->data)) {
    prev = curr;
    curr = curr->next;
  }

  // case where we add to the middle of the list
  if (curr != NULL) {
    n->next = curr;
    n->prev = prev;

    prev->next = n;
    curr->prev = n;

    return(head);
}

void LinkedList::print() {

  Node* temp = head;
  cout << "Contents of Linked List: " << endl;
  
  while (temp != NULL) {
    cout << temp->data << endl;
    temp = temp->next;
  }
  
  return;
}
