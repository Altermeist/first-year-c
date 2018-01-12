/* 
 * File:   Pointer2.c
 * Author: Nicholas Park
 *
 * Created on November 20, 2015, 8:17 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(void) {
    int x[] = {3, 7, 2, 9, 5,2,3,4,5,4};
    
    int *p = x;
    int *q = &x[3];
    
    p = q - p + 1;
    printf("%d %d", *p, *q);
    
    return 0;
}

