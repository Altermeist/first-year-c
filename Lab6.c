/* 
 * File:   Lab6.c
 * Author: Nicholas Park
 *
 * Created on October 31, 2015, 1:43 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * 
 */

// Print current state of board (pieces & dimension) when called
void printBoard(char board[26][26], int n) {
    int row, col;
    printf("  ");
    for (int i = 0; i < n; i++) {
        printf("%c", 'a' + i);
    }
    printf("\n");

    for (row = 0; row < n; row++) {
        printf("%c ", 'a' + row);

        for (col = 0; col < n; col++) {
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
}

// Check if potential move is within dimensions of board
bool positionInBounds(int N, char row, char col) {

    if ((int) row == 0 && (int) col == 0) {

        return false;
    } 
    else if ((int) row < N && (int) col < N && (int) row >= 0 && (int) col >= 0) {
        return true;
    } 
    else {
        return false;
    }
}

// Check in 1 of 8 dir. if move is adjacent to at least 1 'B', in bound, & 'W' at end of dir.
bool checkLegalInDirection(char board[26][26], int N, char row, char col, char colour, int deltaRow, int deltaCol) {
    if (colour == 'W') {
        if (positionInBounds(N, row - 'a' + deltaRow, col - 'a' + deltaCol) == true) {
            if (board[(row - 'a') + deltaRow][(col - 'a') + deltaCol] == 'B') {
                int i = 1;
                do {
                    i++;
                    row - 'a' + (deltaRow * i);
                    col - 'a' + (deltaCol * i);
                } while (board[(row - 'a') + (deltaRow * i)][(col - 'a') + (deltaCol * i)] == 'B');

                if (board[(row - 'a') + (deltaRow * i)][(col - 'a') + (deltaCol * i)] == 'W') {
                    return true;
                } 
                else {
                    return false;
                }
            } 
            else {
                return false;
            }
        }
        else {
                return false;}
    }
    
// Check the same as above, but for 'B'    
    else if (colour == 'B') {
        if (positionInBounds(N, row - 'a' + deltaRow, col - 'a' + deltaCol) == true) {
            if (board[(row - 'a') + deltaRow][(col - 'a') + deltaCol] == 'W') {
                int i = 1;
                do {
                    i++;
                    row - 'a' + (deltaRow * i);
                    (col - 'a') + (deltaCol * i);
                } while (board[(row - 'a') + (deltaRow * i)][(col - 'a') + (deltaCol * i)] == 'W');
                
                if (board[(row - 'a') + (deltaRow * i)][(col - 'a') + (deltaCol * i)] == 'B') {
                    return true;
                } 
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
    }
}

int main(void) {

    int dimension;
    char board[26][26];
    char wUserMoves[26][26];
    char bUserMoves[26][26];
    char colour, inRow, inCol, uColour, uRow, uCol;

    // Prompt user to enter board dim & initialize board w/ starting pieces
    printf("Enter the board dimension: ");
    scanf("%d", &dimension);

    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            board[row][col] = 'U';
        }
    }
    board[(dimension / 2) - 1][(dimension / 2) - 1] = 'W';
    board[dimension / 2][dimension / 2] = 'W';
    board[(dimension / 2) - 1][dimension / 2] = 'B';
    board[dimension / 2][(dimension / 2) - 1] = 'B';
    printBoard(board, dimension);

    // Prompt user for placing pieces on board until '!!!' is entered
    printf("Enter board configuration: \n");
    do {
        scanf(" %c %c %c", &colour, &inRow, &inCol);
        if (colour == 'W') {
            board[inRow - 'a'][inCol - 'a'] = 'W';
        } 
        else if (colour == 'B') {
            board[inRow - 'a'][inCol - 'a'] = 'B';
        }
    } while (colour != '!' && inRow != '!' && inCol != '!');
    printBoard(board, dimension);

    // Display possible moves for W in order of inc rows, then cols by calling checkLegal func 
    printf("Available moves for W: \n");
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            if (board[row][col] == 'U') {
                char vrow = row + 'a';
                char vcol = col + 'a';
                int check = 0;
                for (int deltaRow = -1; deltaRow < 2 && check == 0; deltaRow++) {
                    for (int deltaCol = -1; deltaCol < 2 && check == 0; deltaCol++) {
                        if (checkLegalInDirection(board, dimension, vrow, vcol, 'W', deltaRow, deltaCol) == true) {
                            printf("%c%c\n", vrow, vcol);
                            wUserMoves[vrow - 'a'][vcol - 'a'] = 'W';
                            check = 1;
                        }
                    }
                }
            }
        }
    }

    // Display possible moves for B in order of inc rows, then cols by calling checkLegal func 
    printf("Available moves for B: \n");
    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            if (board[row][col] == 'U') {
                char vrow = row + 'a';
                char vcol = col + 'a';
                int check = 0;
                for (int deltaRow = -1; deltaRow < 2 && check == 0; deltaRow++) {
                    for (int deltaCol = -1; deltaCol < 2 && check == 0; deltaCol++) {
                        if (checkLegalInDirection(board, dimension, vrow, vcol, 'B', deltaRow, deltaCol) == true) {
                            printf("%c%c\n", vrow, vcol);
                            bUserMoves[vrow - 'a'][vcol - 'a'] = 'B';
                            check = 1;
                        }
                    }
                }
            }
        }
    }

    // Prompt user to enter a move from list of avail moves & call checkLegal func to flip valid pieces
    printf("Enter a move: \n");
    scanf(" %c %c %c", &uColour, &uRow, &uCol);

    if (uColour == 'W') {
        if (wUserMoves[uRow - 'a'][uCol - 'a'] == 'W') {
            printf("Valid move.\n");
            board[uRow - 'a'][uCol - 'a'] = 'W';
            
            for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
                for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
                    if (checkLegalInDirection(board, dimension, uRow, uCol, 'W', deltaRow, deltaCol) == true) {
                        for (int i = 1; board[(uRow - 'a') + (deltaRow * i)][(uCol - 'a') + (deltaCol * i)] == 'B'; i++) {
                            board[(uRow - 'a') + deltaRow * i][(uCol - 'a') + deltaCol * i] = 'W';
                        }
                    }
                }
            }
            printBoard(board, dimension);
        } 
        else {
            printf("Invalid move.\n");
            printBoard(board, dimension);  
        }
    } 
    else if (uColour == 'B') {
        if (bUserMoves[uRow - 'a'][uCol - 'a'] == 'B') {
            printf("Valid move.\n");
            board[uRow - 'a'][uCol - 'a'] = 'B';

            for (int deltaRow = -1; deltaRow < 2; deltaRow++) {             
                for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
                    if (checkLegalInDirection(board, dimension, uRow, uCol, 'B', deltaRow, deltaCol) == true) {
                        for (int i = 1; board[(uRow - 'a') + (deltaRow * i)][(uCol - 'a') + (deltaCol * i)] == 'W'; i++) {
                            board[(uRow - 'a') + deltaRow * i][(uCol - 'a') + deltaCol * i] = 'B';
                        }

                    }

                }
            }
            printBoard(board, dimension);
        } 
        else {
            printf("Invalid move.\n");
            printBoard(board, dimension);
        }
    }
    else {
        printf("Invalid move.\n");
        printBoard(board, dimension);
    }
    /* else {
        while ((uColour != 'W' && uColour != 'B') || (bUserMoves[uRow - 'a'][uCol - 'a'] != 'W' && wUserMoves[uRow - 'a'][uCol - 'a'] == 'W')) {
        printf("Invalid move.\n");
            printf("Enter a move: \n");
        scanf(" %c %c %c", &uColour, &uRow, &uCol);
        }
    } */
    return 0;
}