//
//  ConsecutiveOnes.c
//  Finds all sequences of consecutive ones with a particular length in a 2D matrix.
//
//  Created by Baochun Li on 2014-10-29.
//  Copyright (c) 2014 APS 105. All rights reserved.
//

#include <stdio.h>

int main(void) {
  const int SizeOfMatrix = 6;
  const int SequenceLength = 2;

  int board[6][6] =
   {{0,1,1,1,1,0},
    {0,0,1,1,1,0},
    {1,1,1,1,0,0},
    {0,0,0,1,1,1},
    {1,1,0,0,1,1},
    {0,0,1,0,1,1}};
  
  for (int row = 0; row < SizeOfMatrix; row ++) {
    int col = 0, numberOfConsecutiveOnes = 0;
    
    while (col < SizeOfMatrix) {
      if (numberOfConsecutiveOnes > 0) {
        if (board[row][col] == 0) {
          if (numberOfConsecutiveOnes == SequenceLength)
            printf("Found %d 1's in a row at location (%d, %d).\n",
                   SequenceLength, row, col - SequenceLength);
          numberOfConsecutiveOnes = 0;
        }
        else 
          numberOfConsecutiveOnes++;
        
      }
      else if (board[row][col] == 1) 
        numberOfConsecutiveOnes = 1;
      
      col++;
    }
    
    if (numberOfConsecutiveOnes == SequenceLength)
      printf("Found %d 1's in a row at location (%d, %d).\n",
             SequenceLength, row, col - SequenceLength);
  }
}
