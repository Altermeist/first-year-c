#include <stdio.h>
#include <stdlib.h>

int main(void) {
  const int SizeOfMatrix = 6;
  const int SequenceLength = 2;

  int board[6][6] =
   {0,1,1,1,1,0,
    0,0,1,1,1,0,
    1,1,1,1,0,0,
    0,0,0,1,1,1,
    1,1,0,0,1,1,
    0,0,1,0,1,1};

    for (int row = 0; row < SizeOfMatrix; row++) {
      for (int col = 0; col < SizeOfMatrix; col++) {
        // count the number of 1's from this point on
        int count = 0;

        for (int i = col; i < col + SequenceLength && i < SizeOfMatrix; i++) {
          if (board[row][i] == 1) 
            count++;
            
          if (count == SequenceLength) 
            printf("Found %d in a row at (%d, %d).\n", 
              SequenceLength, row, col);
        }
      }
    }

    return 0;
}
