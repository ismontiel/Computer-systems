// count.c  Count the number of lines and chars in the input.

#include <stdio.h>

int main() {
  int lineCount = 0;
  int numLines = 0;
  int numChars = 0;
  printf("Enter text.  Use an empty line to stop.\n");
  
  while (1) {
      int ic = getchar();
      if (ic < 0)    //EOF encountered
          break;
      char c = (char) ic;
      if (c == '\n' && lineCount == 0) //Empty line
          break; 
      numChars ++;
      if (c == '\n') {
          numLines ++;
          lineCount = 0;
      }
      else
          lineCount ++;
  }
  printf("Your text has %d lines and %d characters.\n", numLines, numChars);
}
