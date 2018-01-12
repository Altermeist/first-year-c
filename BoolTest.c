/* 
 * File:   BoolTest.c
 * Author: Nicholas Park
 *
 * Created on October 19, 2015, 5:18 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*
 * 
 */
int main(int argc, char** argv) {
    int input, output;
    
    bool done = false;

while (done == false) {
    printf("Enter a number: ");
    scanf("%d", &input);
    
    printf("Output is %d", input);
    
    if (input < 0) {
        done = true;
    }
    
    
}
    printf("Exit");
    return (EXIT_SUCCESS);
}

