/* 
 * File:   Lec13.c
 * Author: Nicholas Park
 *
 * Created on October 14, 2015, 1:58 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */


// This program shows various ways of declaring and defining
// functions in the C language.

// Function prototype at the beginning of the file
void skipLines(int n);

int main(void) {
  // Function prototype in the calling function
  void skipLine(void);
  int factorial(int n);

  skipLine();
  skipLine();
  skipLines(3);
  printf("The factorial of 6 is: %d\n", factorial(6));
  return 0;
}

// A function that does not return a value, and has no parameters
void skipLine(void) {
  printf("\n");
}

// A function that does not return a value, and has parameters
void skipLines(int n) {
  for (int i = 1; i <= n; i ++)
    printf("\n");
}

// A function that returns a value, and has parameters
int factorial(int n) {
  int product = 1;
  for (int i = 1; i <= n; i++)
    product *= i;

  return product;
}
