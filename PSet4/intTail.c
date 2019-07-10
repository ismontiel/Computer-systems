#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charToInts(char *temp);

int main(int argc, char *argv[]) {
  int size = 10;
  if(argc != 1) {
    size = charToInts(argv[1]);
  }
  int *arr = (int*) malloc(sizeof(int) * size);   //creating int array
  int *arrStart = arr;    //To keep track of beginning of the array
  int currentVal;
  int inputCount = 0;

  scanf("%d", &currentVal);
  while(currentVal != -1) {   //This loop is filling the "circullar array"
    if(arr == arrStart+size) {    //If we reach the end of the array
      arr = arrStart;
    }
    *arr = currentVal;
    scanf("%d", &currentVal);
    arr++;
    inputCount++;
  }

  arr--;
  int *stopPt = arr;
  if(inputCount >= size) {
    if(arr+1 == arrStart+size) {    //If the input stops at the final element in the array
      printf("Here are the last %d numbers: ", size);
      arr = arrStart;
      while(arr != arrStart+size) {
        printf("%d ", *arr++);
      }
    } else {
      arr++;
      printf("Here are the last %d numbers: ", size);
      while(arr != arrStart+size) {
        printf("%d ", *arr++);
      }
      while(arrStart <= stopPt) {
        printf("%d ", *arrStart++);
      }
    }

  } else {
    printf("There are only %d numbers: ", inputCount);
    arr = arrStart;
    while(arr < arrStart+inputCount) {
      printf("%d ", *arr++);
    }
  }
  printf("\n");
  free(arrStart);
}

int charToInts(char *temp) {
  int size = 0;
  while(*temp != '\0') {
    size = 10*size + (*temp++-'0');
  }
  return size;
}
