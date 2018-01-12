#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *link;
};

typedef struct node Node;

// Creating a new node
Node *newNode(int data, Node *link) {
  Node *t = (Node *) malloc(sizeof(Node));

  if (t != NULL) {
    t -> data = data;
    t -> link = link;
  }

  return t;
}

// Inserting a new node at the front of the list
Node *insertAtFront(Node *head, int item) {
  return newNode(item, head);
}

// Printing all the nodes in a linked list
void printList(Node *head) {
  Node *current = head;

  while (current != NULL) {
    printf("%d\n", current -> data);
    current = current -> link;
  }
}

// Searching through the linked list for a particular key
bool search(Node *head, int searchKey) {
  Node *current = head;

  while (current != NULL) {
    if (current -> data == searchKey)
      return true;

    current = current -> link;
  }

  return false;
}

// Deleting the first node
Node *deleteFirstNode(Node *head) {
  if (head != NULL)
  {
    Node *newHead = head -> link;
    free(head);

    return newHead;
  }
  return head;
}

// Deleting all the nodes in the linked list
Node *deleteAllNodes(Node *head) {
  while (head != NULL) {
     Node *firstNode = head;
     head = head -> link;
     free(firstNode);
   
     // Alternatively...

     // Node * secondNode = head -> link;
     // free(head);
     // head = secondNode;
  }
  return NULL;
}

// Inserting at the tail of a linked list
Node *insertAtTail(Node *head, int item) {
  if (head == NULL)
    return newNode(item, NULL);
  else {
     Node *current = head;

     while (current -> link != NULL)
       current = current -> link;

     current -> link = newNode(item, NULL);
     return head;
  }
}

// Deleting the last node in the linked list
Node *deleteLastNode(Node *head) {
  if (head == NULL)
      
    return NULL;

  else if (head -> link == NULL) { 
    // Deleting the last node in the list
    free(head);
    return NULL; // the list becomes empty after deletion
  }
  else {
    Node *current = head;

    while (current -> link -> link != NULL)
       current = current -> link;

    free(current -> link);
    current -> link = NULL;
    return head; // head is not changed in this case
  }
}

// Inserting a new node into an ordered linked list, maintaining its order
Node *insertIntoOrderedList(Node *head, int item) {
   if (head == NULL || item < head -> data)
     return newNode(item, head); // a new head of the list

   Node *current = head;
   
   while (current -> link != NULL && item > current -> link -> data) 
     current = current -> link;

   current -> link = newNode(item, current -> link);
   return head;
}

// Deleting the first occurrence of a search key from a linked list
Node *deleteFirstOccurrence(Node *head, int searchKey) {
  if (head == NULL) 
    return NULL;

  // If the first node is to be deleted
  if (head -> data == searchKey) {
     Node *secondNode = head -> link;
     free(head);
     return secondNode;
  }

  bool found = false;
  Node *current = head;

  while (!found && current -> link != NULL) {
    if (current -> link -> data == searchKey)
      found = true;
    else
      current = current -> link;
  }

  // if there exists a node to be deleted
  if (current -> link != NULL)
  {
      Node *nodeToRemove = current -> link;
      current -> link = current -> link -> link;
      free(nodeToRemove);
  }

  return head;
}

// Deleting all occurrences of a search key from a linked list
Node *deleteAllOccurrences(Node *head, int searchKey) {
  while (head != NULL && head -> data == searchKey) {
    Node *firstNode = head;
    head = head -> link;
    free(firstNode);
  }

  if (head != NULL) {
    Node *current = head;
    while (current -> link != NULL) {
      if (current -> link -> data == searchKey) {
        Node *nodeToRemove = current -> link;
        current -> link = current -> link -> link;
        free(nodeToRemove);
      }
      else // only advance 'current' if nothing is deleted
        current = current -> link;
    }
  }

  return head;
}



int main(void) {
  Node *head = NULL;

  // Creating a linked list: 2 -> 3 -> 1
  head = insertAtFront(head, 1);
  head = insertAtFront(head, 3);
  head = insertAtFront(head, 2);

  // Printing the list
  printList(head);

  // Testing search
  printf("Searching for 3: %s\n", search(head, 3) ? "true" : "false");
  printf("Searching for 5: %s\n", search(head, 5) ? "true" : "false");

  // Deleting the first node
  head = deleteFirstNode(head);
  printf("After deleting the first node:\n");
  printList(head);

  head = deleteAllNodes(head);
  printf("After deleting all the nodes:\n");
  printList(head);

  // Creating a linked list: 5 -> 6 -> 4
  head = insertAtTail(head, 5);
  head = insertAtTail(head, 6);
  head = insertAtTail(head, 4);
  printList(head);

  // Deleting the last node three times  
  head = deleteLastNode(head);
  printf("After deleting the last node:\n");
  printList(head);

  head = deleteLastNode(head);
  printf("After deleting the last node:\n");
  printList(head);

  head = deleteLastNode(head);
  printf("After deleting the last node:\n");
  printList(head);

  printf("Inserting into an ordered list:\n");

  // Inserting into an ordered list
  head = insertIntoOrderedList(head, 5);
  head = insertIntoOrderedList(head, 6);
  head = insertIntoOrderedList(head, 4);
  printList(head);

  // Deleting the first occurrence of a search key
  printf("Deleting 6:\n");
  head = deleteFirstOccurrence(head, 6);
  printList(head);

  printf("Deleting 7:\n");
  head = deleteFirstOccurrence(head, 7);
  printList(head);

  printf("Deleting 4:\n");
  head = deleteFirstOccurrence(head, 4);
  printList(head);

  printf("Creating a list: 5 -> 5 -> 5 -> 6.\n");
  head = insertIntoOrderedList(head, 5);
  head = insertIntoOrderedList(head, 5);
  head = insertIntoOrderedList(head, 6);
  printList(head);

  // Deleting all occurrences of a search key
  printf("Deleting all occurrences of 5:\n");
  head = deleteAllOccurrences(head, 5);
  printList(head);

  printf("Deleting all occurrences of 6:\n");
  head = deleteAllOccurrences(head, 6);
  printList(head);
}
