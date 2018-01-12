/* 
 * File:   Lab5.c
 * Author: Nicholas Park
 *
 * Created on October 23, 2015, 9:48 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//bool matchFound = false;
bool sequence;
int seqLength;
char inChar[100];
char DNA[] = {'A', 'G', 'C', 'G', 'G', 'G', 'A', 'C', 'C', 'G',
    'T', 'C', 'C', 'C', 'G', 'A', 'C', 'A', 'T', 'T', 'G', 'A',
    'T', 'G', 'A', 'A', 'G', 'G', 'G', 'T', 'C', 'A', 'T', 'A',
    'G', 'A', 'C', 'C', 'C', 'A', 'A', 'T', 'A', 'C', 'G', 'C',
    'C', 'A', 'C', 'C', 'A', 'C', 'C', 'C', 'C', 'A', 'A', 'G',
    'T', 'T', 'T', 'T', 'C', 'C', 'T', 'G', 'T', 'G', 'T', 'C',
    'T', 'T', 'C', 'C', 'A', 'T', 'T', 'G', 'A', 'G', 'T', 'A',
    'G', 'A', 'T', 'T', 'G', 'A', 'C', 'A', 'C', 'T', 'C', 'C',
    'C', 'A', 'G', 'A', 'T', 'G', '\0'};

/*
 * 
 */

int readSearch() {
    sequence = true;
    for (int i = 0; i < seqLength; i++) {
        scanf(" %c", &inChar[i]);
        if (inChar[i] != 'A' && inChar[i] != 'G' && inChar[i] != 'T' && inChar[i] != 'C' && inChar[i] != '*') {
            printf("Erroneous character input '%c' exiting \nGoodbye", inChar[i]);
            sequence = false;
            return -1;
        }
    }
}

int searchMatch() {
    int i, k, DNALength;
    DNALength = 100;
    for (k = 0; k <= DNALength - seqLength; k++) {
        bool matchFound = true;
        for (i = 0; i < seqLength; i++) {
            if (inChar[i] != DNA[i + k] && inChar[i] != '*') {
                matchFound = false;
            }
        }
        if (matchFound) {
            printf("Match of sequence found at element %d\n", k);
        }
    }
}

int main(void) {
    bool done = false;

    while (done == false) {
        printf("Enter length of DNA sequence to match: ");
        scanf("%d", &seqLength);

        if (seqLength <= 0) {
            printf("Goodbye");
            done = true;
        } 
        else {
            printf("Enter %d characters (one of AGTC*) as a search sequence: ", seqLength);

            readSearch();
            
            if (sequence == false) {
                return 0;
            }
            searchMatch();
        }
    }
    return 0;
}

