#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charToInts(char *temp);
char *readALine(int maxChars);

int main(int argc, char *argv[]) {
  int size = 10;
  if(argc != 1) {
    size = charToInts(argv[1]);
  }
  char** arr = (char**) malloc(sizeof(char*) * size);   //creating an array of string pointers
  int arrStart = 0;    //To keep track of beginning of the array
  char *currentLine;
  int inputCount = 0;

  currentLine = readALine(80);
  int arrayIter = 0;    //This pointer is used to iteratively store lines in the array of string pointers
  while(currentLine != NULL) {
    if(arrayIter == arrStart+size) {    //If we reach the end of the array and have to go back to the beginning
      arrayIter = arrStart;
    }
    arr[arrayIter] = currentLine;
    currentLine = readALine(80);
    arrayIter++;
    inputCount++;
  }

  arrayIter--;
  int stopPt = arrayIter;
  if(inputCount >= size) {
    if(arrayIter+1 == arrStart+size) {    //If the input stops at the final element in the array
      arrayIter = arrStart;
      while(arrayIter != arrStart+size) {
        printf("%s\n", arr[arrayIter++]);
      }
    } else {
      arrayIter++;
      while(arrayIter != arrStart+size) {
        printf("%s\n", arr[arrayIter++]);
      }
      while(arrStart <= stopPt) {
        printf("%s\n", arr[arrStart++]);
      }
    }

  } else {
    arrayIter = arrStart;
    while(arrayIter < arrStart+inputCount) {
      printf("%s\n", arr[arrayIter++]);
    }
  }
  free(arr);
}

char *readALine(int maxChars) {
  char *myLine = (char*) malloc(sizeof(char) * (maxChars+2));
  if(fgets(myLine, maxChars, stdin) != NULL) {
    int length = strlen(myLine);
    if(myLine[length-1] == '\n') {
      myLine[length-1] = '\0';
      return myLine;
    } else {
      return myLine;
    }
  } else {
    free(myLine);
    // printf("here");
    return NULL;
  }

}


int charToInts(char *temp) {
  int size = 0;
  while(*temp != '\0') {
    size = 10*size + (*temp++-'0');
  }
  return size;
}
