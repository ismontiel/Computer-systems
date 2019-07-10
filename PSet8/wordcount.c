#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct wordcount {
  char word[80];
  int count;
};
typedef struct wordcount WordCount;

int compare(void *myItem, void *treeItem);
WordCount *createItem(char myWord[80]);

int main(int argc, char const *argv[]) {
  char myString[80];
  scanf("%s", myString);    // Creating the root of the tree
  BSTnode *headNode = createNode(createItem(myString));   // The actual root of the tree
  WordCount *largestItem = headNode -> item;    // Since the tree only has a root, it itself is the largest item

  while(scanf("%s", myString) >  0) {   // Looping until EOF
    WordCount *myItem = createItem(myString);   // Creating a WordCount item out of the current word
    BSTnode *findFlag = find(headNode, myItem, compare);   // Node to compare a match agains

    if(compare(myItem, (findFlag -> item)) == 0) {    // If there actually was a match
      ((WordCount *) findFlag -> item) -> count += 1;   // Increment the count on the node
      if(((WordCount *) (findFlag -> item)) -> count > largestItem -> count) {    // Testing if there was a change in the largest item
        largestItem = (WordCount *) (findFlag -> item);
      }
    }
    insert(headNode, myItem, compare);    // Always inserts because insert will do nothing if there was a match
  }
  printf("The most frequent word is '%s' which appears %d times\n", largestItem -> word, largestItem -> count);
  return 0;
}

// @param two WordCount structures
// @return an int indicating the comparison b/w the item's words
int compare(void *myItem, void *treeItem) {
  return strcmp(((WordCount*) myItem) -> word, ((WordCount*) treeItem) -> word);
}

// Takes in a string, returns a WordCount structure from that string
WordCount *createItem(char myWord[80]) {
  WordCount *myItem = (WordCount*) malloc(sizeof(WordCount));
  strcpy(myItem -> word, myWord);
  myItem -> count = 1;
  return myItem;
}
