#include <stdio.h>
#include <stdlib.h>

int * deepCopy(const int *a, int n);


int main(int argc, char **argv){
 //create an array containing {10, 20, 30, 40, 50}
 int n = 5;
 int *a = (int *) malloc(n * sizeof(int));
 for(int i=0; i<n; i++) {
 a[i] = (i+1)*10;
 }
 int *b = deepCopy(a,n);
 b[0] = 42;

 printf("a[0] = %d\n", a[0]);

  return 0;

}
int * deepCopy(const int *a, int n) {
 if(a == NULL || n < 0) {
 return NULL;
 }
 int *copy = (int *) malloc(n * sizeof(int));
for(int i=0; i<n; i++) {
 copy[i] = a[i];
 }
 return copy;
 }

