#include "intsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global Variables
IntNode *headNode;

// Function Declarations
// create a node
IntNode *createNode(int val);
// insert a node into the chain, in sorted order
void insert(IntNode *header, int val);
// print the values stored in the chain of nodes
void printAll(IntNode *header);


int main(int argc, char *argv[]) {
  printf("Enter some numbers, ending with -1: ");
  int currentVal;   // Keeps track of current user entered number
  scanf("%d", &currentVal);
  headNode = createNode(currentVal);
  while(1) {
    scanf("%d", &currentVal);
    if(currentVal == -1) {    // Until we reach the break condition
      break;
    } else {
      insert(headNode, currentVal);
    }
  }
  printAll(headNode);
}

// create a node
IntNode *createNode(int val) {
  IntNode *myNode = (IntNode*) malloc(sizeof(IntNode));
  myNode -> item = val;
  myNode -> next = NULL;
  return myNode;
}

// insert a node into the chain, in sorted order
void insert(IntNode *header, int val) {
  if(header -> item > val) {    // If the new value is less than anything else in the chain
    IntNode *myNode = createNode(val);
    myNode -> next =  header;
    headNode = myNode;
    return;
  }
  IntNode *beforeNode = header;
  IntNode *afterNode = header -> next;
  while(afterNode != NULL) {    // While the trailing scanner is not at the last node in the chain
    if(val < (afterNode -> item)) {   // If the value should be between the scanning nodes
      IntNode *myNode = createNode(val);
      myNode -> next = afterNode;
      beforeNode -> next = myNode;
      return;
    }
    beforeNode = afterNode;
    afterNode = afterNode -> next;    // Incrementing out scanners
  }
  IntNode *myNode = createNode(val);    //Reaching this point means the value should be at the end of the chain
  beforeNode -> next = myNode;
  return;
}

// print the values stored in the chain of nodes
void printAll(IntNode *header) {
  IntNode *myScan = header;
  printf("Here are the numbers in sorted order: ");
  while(myScan != NULL) {
    printf("%d ", myScan -> item);
    myScan = myScan -> next;
  }
  printf("\n");
}
