// hw6test.c  A test file for the memory manager.
#include "gc.h"
#include <stdio.h>
#include <stdlib.h>

// Funtion declarations
void gc();
void *stackBottom();
int *getHeader(int *p);
void *markAndScan(int *myPoint);
void markBlock(int *myHeader);
void sweep(int * mySweeper);

void gc() { // perform garbage collection on the heap
  int **max = (int **) stackBottom(); // the address of the bottom of the stack
  int* dummy;
  int **p = &dummy; // the address of the top of the stack

  while(p != max) {   // Going through all possible pointers in the stackframe
    if((*p < (int*) lastBlock()) && (*p >= (int *) firstBlock())) {    // Seeing if the possible pointer is an address in the heap
      markAndScan(*p);   // If it is, then we mark its block and scan for any other pointers in that block
    }
    p++;
  }
  sweep((int *) firstBlock());
}

void *stackBottom() {
	unsigned long bottom;
    FILE *statfp = fopen("/proc/self/stat", "r");
    fscanf(statfp,
           "%*d %*s %*c %*d %*d %*d %*d %*d %*u "
           "%*u %*u %*u %*u %*u %*u %*d %*d "
           "%*d %*d %*d %*d %*u %*u %*d "
           "%*u %*u %*u %lu", &bottom);
    fclose(statfp);
	return (void *) bottom;
}

int *getHeader(int *p) {
  int *follow = (int *) firstBlock();
  int *lead = (int *) nextBlock(follow);

  while(follow < (int *) lastBlock()) {
    if((p < lead) && (p >= follow)) {    // Determining which block the inputted pointer belongs to
      return follow;
    }
    follow = (int *) nextBlock(follow);
    lead = (int *) nextBlock(lead);
  }
}

// This function finds the header of the inputted pointer's block
// If the header is already marked, it will return NULL
// If not, the header will be marked and the functon will scan the block to determine if there are pointers to other blocks
// If there is another pointer, then this function will be recursively called for the new pointer
void *markAndScan(int *myPoint) {
  int *myHeader = getHeader(myPoint);    // Gets pointer to header of the block that p is in
  if(*myHeader % 4 == 3) {    // Checking if the block has already been marked
    return NULL;
  }
  markBlock(myHeader);
  int *traverser = myHeader;    // This is a traverser to check if there are any pointers in the current block
  while(traverser < (int *) nextBlock(myHeader)) {    // Scanning until we reach the next block
    if((*traverser < (int) lastBlock()) && (*traverser >= (int) firstBlock()) && (*traverser % 2 == 1)) {   // Again checking if the traverser is a pointer to the heap and if that pointer is allocated
      markAndScan((int *) *traverser);   // If so, recurse to see if its header has been marked
    }
    traverser++;
  }
}

void markBlock(int *myHeader) {
  *myHeader = *myHeader | 2;
}

// This function goes through each block in the heap and calls the coalesce function
// A non-marked item will be freed
// A marked item will have its mark removed
void sweep(int *mySweeper) {
  while(mySweeper < (int *) lastBlock()) {
    if(*mySweeper % 4 != 3) {   // If the header indicates an unmarked item
      myfree(mySweeper);
      mySweeper = (int *) nextBlock(mySweeper);
    } else {    // Else the header indicates a marked item
      *mySweeper = *mySweeper - 2;
      mySweeper = (int *) nextBlock(mySweeper);
    }
  }
  coalesce();
}
