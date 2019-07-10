#include <stdio.h>
#include <ctype.h>

int takesNoArgs(char op);
float processOp(float amt, char op, float val);
float processPlus(float amt, float val);
float processMinus(float amt, float val);
float processTimes(float amt, float val);
float processDivide(float amt, float val);
float processPrint(float amt);
float processClear();

int main() {
  float amt = 0.0;   //Current value of the Calculator
  char op;
  float val;      //Value of the operation

  printf("CS 2271 Calculator\n");
  while(1) {
    // printf("%f\n", amt);
    int ic = getchar();
    // printf("%d\n", ic);
    if(ic < 0) {      //EOF
      break;
    }
    op = (char) ic;
    if(op == 'Q') {
      break;
    }
    if(takesNoArgs(op)){      //Take this patch if the operator takes now arguments (ex. '=')
      val = 0.0;
      ic = getchar();
      char c = (char) ic;
      while(c != '\n'){     //Checking for the end of the line
        ic = getchar();
        c = (char) ic;
      }
    } else {
      scanf("%f", &val);    //Grabbing the float

      ic = getchar();
      char c = (char) ic;
      // printf("lmao %d\n", ic);
      // printf("lmao\n");
      //
      while(c != '\n'){     //Checking for the end of the line
        ic = getchar();
        c = (char) ic;
      }
    }
    amt = processOp(amt, op, val);
  }

  printf("Thank you and goodbye! :D\n");
}

int takesNoArgs(char op){
  return (op == 'C') || (op == '=');
}

float processOp(float amt, char op, float val) {
  if(op == '+') {
    return processPlus(amt, val);
  }
  else if(op == '-') {
    // printf("%f, %f\n", amt, val);
    return processMinus(amt, val);
  }
  else if(op == '*') {
    return processTimes(amt, val);
  }
  else if(op == '/') {
    return processDivide(amt, val);
  }
  else if(op == '=') {
    // printf("%f\n", amt);
    return processPrint(amt);
  }
  else if(op == 'C') {
    return processClear();
  } else {
    printf("Bad Operator\n");
    return amt;
  }
}

float processPlus(float amt, float val) {
  return amt + val;
}

float processMinus(float amt, float val) {
  return amt - val;
}

float processTimes(float amt, float val) {
  return amt * val;
}

float processDivide(float amt, float val) {
  return amt / val;
}

float processPrint(float amt) {
  printf("%f\n", amt);
  return amt;
}

float processClear() {
  return 0;
}
