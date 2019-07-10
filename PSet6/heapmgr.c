// hw6test.c  A test file for the memory manager.
#include "memorymgr.h"
#include <stdio.h>
#include <stdlib.h>

//Global Variables
int *frontBlock;
int *endBlock;
// int counterLMAO = 1;

// Initializes a simulated heap
void  initmemory(int size) {
  size += 12;
  int temp = size % 8;
  if(temp != 0) {
    size = size - temp + 8;
  }

  void *heapStart = malloc(size);

  int dataBlock = size - 8;     // Defining the length for which the user has access to
  frontBlock = heapStart+4;     // Add for to account for the inital padding
  *frontBlock = dataBlock;    //Throwing in the size of the allocated block in the header

  endBlock = frontBlock + dataBlock;
  *endBlock = 1;
}

// Allocates a block of length (or more) bytes
// Returns a pointer to that allocated block if there is an unallocated space with sufficient space
// Returns NULL otherwise
void *myalloc(int length) {
  length = length + 4;

  int temp = length % 8;
  if(temp != 0) {
    length = length - temp + 8;
  }

  int *traverser;
  traverser = frontBlock;

  while(*traverser != 1) {    //Keep looking until we reach the sentinel block
    if((*traverser >= length) && (isAllocated(traverser) == 0)) {    // If the length is even (unallocated) and it can store the data plus the header
      if(*(traverser+length) == 1) {
        *traverser = length | 1;
      } else {
        *(traverser+length) = *traverser - length;    // Dividing and initializing the unallocated block that will follow the block we are allocating
        *traverser = length | 1;      //Reducing the size of this block to the length requested, plus the size of the header, and setting the last bit to be 1 to mark allocation
      }
      return traverser;
    }
    traverser = nextBlock(traverser);
  }
  return NULL;    // A block meeting the requested conditions could not be found
}

// Free an allocated block
// Returns NULL
void  myfree(void *ptr){
  *(int *)ptr = *(int *)ptr & -2;
}

// Goes through the heap, coalescing
// Specifically, it uses two header traversers, one trailing the other, seeing if there are consecutive unallocated blocks
void  coalesce() {
  int *leadingTraverser = nextBlock(frontBlock);
  int *lagTraverser = frontBlock;

  while(*leadingTraverser != 1) {     // Until we reach the last block
    if((*leadingTraverser % 2 == 0) && (*lagTraverser % 2 == 0)) {      // If the two headers denote an unallocated block
      *lagTraverser = *leadingTraverser + *lagTraverser;      // The actual coalesce
      leadingTraverser = nextBlock(leadingTraverser);     // Moving the front highest traverser up because we need to see if this now coalesced block can be coalesced again
    } else {      // Else, move both traversers forward
      lagTraverser = leadingTraverser;
      leadingTraverser = nextBlock(leadingTraverser);
    }
  }
}

// print info about the simulated heap, for debugging purposes
void  printallocation() {
  int blockCounter = 0;
  int *traverser = frontBlock;
  while(*traverser != 1) {
    if(isAllocated(traverser) == 1) {
      printf("Block %d: Size %d   - Allocated\n", blockCounter, (*traverser-1));
    } else {
      printf("Block %d: Size %d   - Unallocated\n", blockCounter, *traverser);
    }
    traverser = nextBlock(traverser);
    blockCounter++;
    if(blockCounter > 4) {
      break;
    }
  }
  printf("\n");
  // printf("You've reached the sentinel block. Thanks for coming! :D\n");
}

int  isAllocated(int *p) {  // is the block at location p allocated?
  if(*p % 2 == 0) {
    return 0;
  } else {
    return 1;
  }
}

// return a pointer to the block that follows p
int *nextBlock(int *p) {
  if(isAllocated(p) == 1) {
    return p + (*p - 1);
  }
  return p + (*p);
}

// return a pointer to the first block on the heap
int *firstBlock() {
  return frontBlock;
}

// return a pointer to the sentinel block
int *lastBlock() {
  return endBlock;
}
