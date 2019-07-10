// count.c  Count the number of lines and chars in the input.

#include <stdio.h>
#include <ctype.h>

int main() {
  int lineCount = 0;
  int numLines = 0;
  int numChars = 0;
  int wordCount = 0;
  int wordCharCount = 0;  //Total characters of all words
  int wordCheck = 0;      //This variable is to check that a whitespace is actually indicating a new word instead of, for example, two whitespaces in a row

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
		  if (wordCheck != 0) {
			wordCount++;
			wordCheck=0;
		  }
      }
      else {
          lineCount ++;
		  if (isspace(c) && wordCheck != 0) {
		    wordCount++;
		    wordCheck=0;
	  	  }
		  if (!isspace(c)) {
			wordCheck++;
			wordCharCount++;

		  }
	  }
  }
  float avgCharPerWord = ((float) wordCharCount) / ((float) wordCount);
  printf("Your text has %d lines and %d characters.\n", numLines, numChars);
  printf("Your text has %d words averaging at %.2f charachters per word.\n", wordCount, avgCharPerWord);
}
