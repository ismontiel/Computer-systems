#include <stdio.h>

int readline(int text[], int charLimit);
int *findmatch(int *pattern, int *text, int patternLen, int textLen);
void printmessage(int *position, int *text, int patternLen, int textLen);

int main() {
  int text[40], pattern[40], *position;
  int textLen, patternLen;

  printf("Enter text: ");
  textLen = readline(text, 40);
  printf("Enter pattern: ");
  patternLen = readline(pattern, 40);
  position = findmatch(pattern, text, patternLen, textLen);
  printmessage(position, text, patternLen, textLen);
}

int readline(int text[], int charLimit) {
  int charCount = 0;
  int *p = text;

  while (1) {
      int intChar = getchar();
      if (intChar < 0) {   //EOF encountered
          break;
      }
      if ((char) intChar == '\n') {   //A new line marks the end of the input
        break;
      }
      if((charCount+1) > charLimit) {   //Next character would be over the limit
        break;
      }
      *p = intChar;   //Setting the array cell to the inputted character
      p++;    //Traversing through the array
      charCount++;
    }

    return charCount;
}

int *findmatch(int *pattern, int *text, int patternLen, int textLen) {
  int *textIter, *patternCheck;
  for(textIter = text; textIter <= text + (textLen-patternLen); textIter++) {    //Itterating through each letter of the text
    if(*pattern == *textIter || *pattern == '?') {   //Checking if the first char of the pattern matches the current text char OR if the first pattern character is a '?'
      int *textCheck = textIter+1;    //Defining a new pointer to traverse the text and check for a match

      for(patternCheck = pattern+1; patternCheck < (pattern + patternLen); patternCheck++) {    //Traversing through the pattern for a match
        if(*patternCheck == *textCheck || *patternCheck == '?') {   //If this pattern character matches the text character or is a '?'
          if(patternCheck == pattern + patternLen-1) {   //Checking if we have reached the end of the pattern (meaning we are done)
            return textIter;
          } else {    //We're not done seeing if the whole pattern matches the text
            textCheck++;
          }
        } else {
          break;
        }
      }
    }
  }
  return NULL;    //No match was found
}

void printmessage(int *position, int *text, int patternLen, int textLen) {
  if(position==NULL) {
    printf("No match match was found.\n");
  } else {
    printf("The pattern was found was found at char %u. The remaining text characters are: ", (position-text +1));
    position += patternLen;
    while(position < text + textLen) {
      putchar(*position);
      position++;
    }
    printf("\n");
  }
}
