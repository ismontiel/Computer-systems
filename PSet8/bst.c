#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new node having the specified item.
BSTnode *createNode(void *item) {
  BSTnode *myNode = (BSTnode*) malloc(sizeof(BSTnode));
  myNode -> item = item;
  myNode -> left = NULL;
  myNode -> right = NULL;
  return myNode;
}

// Search the tree rooted at node n for the node matching the specified item.
// If the item exists, return its node.  If not, return the node that would be its parent.
// The function "compare" compares items
BSTnode *find(BSTnode *n, void *item, int compare(void *, void *)) {
  if(n == NULL) {   // Base case!! The node above was the last node
    return NULL;
  }

  BSTnode *myNode;
  if(compare(item, n -> item) < 0) {   // My item comes before the current node
    myNode = find(n -> left, item, compare);    // Look in the left branch
    if(myNode == NULL) {
      return n;
    }
  }
  else if(compare(item, n -> item) > 0) {    // My item comes after the current node
    myNode = find(n -> right, item, compare);    // Look in the left branch
    if(myNode == NULL) {
      return n;
    }
  } else {
    return n;   // If there is a matching node, return that node
  }
  return myNode;    // To 'pass up' the matching/parent node
}

// Insert an item into the tree rooted at node n.
// If the tree already has a node for that item, do nothing.
void insert(BSTnode *n, void *item, int compare(void *, void *)) {
  BSTnode *nodeFinder;
  nodeFinder = find(n, item, compare);    // Finding either the same string or the node above
  if(compare(item, (nodeFinder -> item)) < 0) {   // Insert the item to the left
    nodeFinder -> left = createNode(item);
    return;
  }
  else if(compare(item, (nodeFinder -> item)) > 0) {    // Insert the item to the right
    nodeFinder -> right = createNode(item);
    return;
  }
}
