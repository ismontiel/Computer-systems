#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pushValStack (int stack[], int *top, int value);
int popValStack (int stack[], int *top);
void pushOpStack (char *stack[], int *top, char *value);
char *popOpStack (char *stack[], int *top);
int operation(int val1, int val2, char op);

int main(int argc, char *argv[]) {
  int *valStack = (int*) malloc(sizeof(int) * 50);
  valStack[0] = -990999;        //Since there are no null ints, I couldn't figure out how to check if the stack was empty or just on the first element without my own 'null' value
  int valTop = 0;
  char **opStack = (char**) malloc(sizeof(char*) * 50);
  int opTop = 0;

  int tokenTrack = 1;   //To traverse all the inputs
  char *opTemp;
  int valTemp1;
  int valTemp2;

  while(tokenTrack < argc) {    //This while loop handles the calculator until we run out of tokens

    if((*argv[tokenTrack] == '[') || (*argv[tokenTrack] == 'x') || (*argv[tokenTrack] == '+')) {
      pushOpStack(opStack, &opTop, argv[tokenTrack]);
    } else if(*argv[tokenTrack] == ']') {
      opTemp = popOpStack(opStack, &opTop);
      while(*opTemp != '[') {
        valTemp1 = popValStack(valStack, &valTop);
        valTemp2 = popValStack(valStack, &valTop);
        pushValStack(valStack, &valTop, operation(valTemp1, valTemp2, *opTemp));
        opTemp = popOpStack(opStack, &opTop);
      }
    } else {
      pushValStack(valStack, &valTop, charToInts(argv[tokenTrack]));
    }
    tokenTrack++;
  }
  opTemp = popOpStack(opStack, &opTop);
  while(opTop >= -1) {    //Until we run out of operators
    valTemp1 = popValStack(valStack, &valTop);
    valTemp2 = popValStack(valStack, &valTop);
    pushValStack(valStack, &valTop, operation(valTemp1, valTemp2, *opTemp));
    opTemp = popOpStack(opStack, &opTop);
  }
  printf("%d\n", popValStack(valStack, &valTop));
}

void pushValStack (int stack[], int *top, int value) {
  if(*top == 0  && stack[0] == -990999) {
    stack[0] = value;
  }
  *top = *top + 1;

  stack[*top] = value;
}

int popValStack (int stack[], int *top) {
  *top = *top - 1;
  return stack[*top+1];
}

void pushOpStack (char *stack[], int *top, char *value) {
  if(*top == 0 && stack[*top] == NULL) {
    stack[0] = value;
    return;
  }
  *top = *top + 1;
  stack[*top] = value;
}

char *popOpStack (char *stack[], int *top) {
  *top = *top - 1;
  return stack[*top+1];
}

//This function handles the actual algebra between two integers and an operator
int operation(int val1, int val2, char op) {
  if(op == 'x') {
    return val1*val2;
  }
  else if (op == '+'){
    return val1+val2;
  }
}

//This function is to convert the string from argv into an integer to be pushed on the value stack
int charToInts(char *temp) {
  int myInt = 0;
  while(*temp != '\0') {
    myInt = 10*myInt + (*temp++-'0');
  }
  return myInt;
}
