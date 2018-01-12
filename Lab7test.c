/* 
 * File:   Lab6.c
 * Author: Nicholas Park
 *
 * Created on October 31, 2015, 1:43 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// int totalScore = 0;
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
    } else if ((int) row < N && (int) col < N && (int) row >= 0 && (int) col >= 0) {
        return true;
    } else {
        return false;
    }
}

bool checkFullBoard(char board[26][26], int N) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (board[row][col] == 'U') {
                return false;
            }
        }
    }
    return true;
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
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
    }// Check the same as above, but for 'B'    
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

                    //scoreInDir(board, row - 'a', col - 'a', i);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
    }
}

int scoreInDirection(char board[26][26], int N, char row, char col, char colour, int deltaRow, int deltaCol) {

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



                    return (i - 1);
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }// Check the same as above, but for 'B'    
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

                    //scoreInDir(board, row - 'a', col - 'a', i);
                    return (i - 1);
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        }
    }
}

int main(void) {
    char board[26][26];
    char wUserMoves[26][26];
    char bUserMoves[26][26];
    char scoreBoard[26][26];
    char cpu, colour, inRow, inCol, uColour, uRow, uCol;
    int *tScore;
    char *tRow;
    char *tCol;
    int dimension, cpuInvalidDir, userInvalidDir, cpuAvailSqr, userAvailSqr;
    int maxScore = 0, bothNoMoves = 0;
    int minRow = dimension - 1, minCol = dimension - 1;  
    int tminRow, tminCol;
    bool doWhite, doBlack;
    bool userMove = true;

    // Prompt user to input board size (even number)
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

    /*
    printf("Enter board configuration: \n");
    do {
        scanf(" %c %c %c", &colour, &inRow, &inCol);
        if (colour == 'W') {
            board[inRow - 'a'][inCol - 'a'] = 'W';
        } else if (colour == 'B') {
            board[inRow - 'a'][inCol - 'a'] = 'B';
        }
    } while (colour != '!' && inRow != '!' && inCol != '!');
    printBoard(board, dimension);
    */

    //
    printf("Computer plays (B/W): ");
    scanf(" %c", &cpu);

    if (cpu == 'B') {
        printBoard(board, dimension);
        while (userMove == true && bothNoMoves != 2 && checkFullBoard(board, dimension) == false) {
            if (checkFullBoard(board, dimension) == false && userMove == true) {
                cpuInvalidDir = 0;
                userInvalidDir = 0;
                if (bothNoMoves == 1) {
                    bothNoMoves = 1;
                } else {
                    bothNoMoves = 0;
                }
                cpuAvailSqr = 0;
                userAvailSqr = 0;
                doBlack = true;
                doWhite = true;
                int cpuInvalidSqr;
                cpuInvalidSqr = 0;

                for (int row = 0; row <= dimension; row++) {
                    for (int col = 0; col < dimension; col++) {
                        if (cpuInvalidDir == 9) {
                            cpuInvalidSqr++;
                        }
                        cpuInvalidDir = 0;
                        if (row < dimension) {
                            if (board[row][col] == 'U') {
                                char vrow = row + 'a';
                                char vcol = col + 'a';
                                for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
                                    for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
                                        if (checkLegalInDirection(board, dimension, vrow, vcol, 'B', deltaRow, deltaCol) == true) {
                                        } 
                                        else {
                                            cpuInvalidDir++;
                                        }
                                    }
                                }
                                cpuAvailSqr++;
                            }
                        }
                    }
                }
                if (cpuInvalidSqr == cpuAvailSqr) {
                    printf("B player has no valid move.\n");
                    doBlack = false;
                    bothNoMoves++;
                }              
                if (bothNoMoves == 1 && doBlack == true) {
                    bothNoMoves = 0;
                }         
                if (doBlack == true) {
                    for (int row = 0; row < dimension; row++) {
                        for (int col = 0; col < dimension; col++) {
                            if (board[row][col] == 'U') {
                                char vrow = row + 'a';
                                char vcol = col + 'a';
                                int totalScore = 0;
                                for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
                                    for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
                                        if (checkLegalInDirection(board, dimension, vrow, vcol, 'B', deltaRow, deltaCol) == true && scoreInDirection(board, dimension, vrow, vcol, cpu, deltaRow, deltaCol) > 0) {
                                            totalScore = scoreInDirection(board, dimension, vrow, vcol, cpu, deltaRow, deltaCol) + totalScore;
                                            tScore = &totalScore;
                                            tRow = &vrow;
                                            tCol = &vcol;
                                            if (*tScore > maxScore) {
                                                maxScore = *tScore;
                                                minRow = *tRow - 'a';
                                                minCol = *tCol - 'a';
                                                tminRow = minRow;
                                                tminCol = minCol;
                                            }
                                        }
                                    }
                                    minRow = dimension - 1;
                                    minCol = dimension - 1;
                                }
                            }
                        }
                    }
                    maxScore = 0;
                    board[tminRow][tminCol] = 'B';
                    for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
                        for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
                            if (checkLegalInDirection(board, dimension, tminRow + 'a', tminCol + 'a', 'B', deltaRow, deltaCol) == true) {
                                for (int i = 1; board[tminRow + (deltaRow * i)][tminCol + (deltaCol * i)] == 'W'; i++) {
                                    board[tminRow + deltaRow * i][tminCol + deltaCol * i] = 'B';
                                }
                            }
                        }
                    }
                    printf("Computer places B at %c%c.\n", tminRow + 'a', tminCol + 'a');
                    printBoard(board, dimension);
                }
            }
            // White user's turn
            if (checkFullBoard(board, dimension) == false && userMove == true) {
                int userInvalidSqr;
                userInvalidSqr = 0;
                for (int row = 0; row <= dimension; row++) {
                    for (int col = 0; col < dimension; col++) {
                        if (userInvalidDir == 9) {
                            userInvalidSqr++;
                        }
                        userInvalidDir = 0;
                        if (userInvalidDir < dimension) {
                            if (board[row][col] == 'U') {
                                char vrow = row + 'a';
                                char vcol = col + 'a';
                                int check = 0;
                                for (int deltaRow = -1; deltaRow < 2 && check == 0; deltaRow++) {
                                    for (int deltaCol = -1; deltaCol < 2 && check == 0; deltaCol++) {
                                        if (checkLegalInDirection(board, dimension, vrow, vcol, 'W', deltaRow, deltaCol) == true) {
                                            wUserMoves[vrow - 'a'][vcol - 'a'] = 'W';
                                            check = 1;
                                        } 
                                        else {
                                            userInvalidDir++;
                                        }
                                    }
                                }
                                userAvailSqr++;
                            }
                        }
                    }
                }
                if (bothNoMoves != 2 && checkFullBoard(board, dimension) == false) {
                    if (userAvailSqr == userInvalidSqr) {
                        printf("W player has no valid move.\n");
                        doWhite = false;                     
                        bothNoMoves++;
                    }
                }
                if (bothNoMoves == 1 && doWhite == true) {
                    bothNoMoves = 0;
                }
                if (bothNoMoves != 2) {
                    if (doWhite == true) {
                        printf("Enter move for colour W (RowCol): ");
                        scanf(" %c %c", &uRow, &uCol);                      
                        if (wUserMoves[uRow - 'a'][uCol - 'a'] == 'W') {
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
                            userMove = false;
                        }
                    }
                }
            }
        }
        // exit loop and end game
        int uScore = 0;
        for (int srow = 0; srow < dimension; srow++) {
            for (int scol = 0; scol < dimension; scol++) {
                if (board[srow][scol] == 'W') {
                    uScore++;
                }
            }
        }
        int cScore = 0;
        for (int srow = 0; srow < dimension; srow++) {
            for (int scol = 0; scol < dimension; scol++) {
                if (board[srow][scol] == 'B') {
                    cScore++;
                }
            }
        }
        if (uScore > cScore) {
            printf("W player wins.\n");
        } else if (uScore == cScore) {
            printf("Draw!\n");
        } else {
            printf("B player wins.\n");
        }
    }
    // Other case if comp is White, then human is Black & goes first
    // Turns alt as long as human inputs valid moves, both players have avail moves & board is not full
    else {
        printBoard(board, dimension);
        while (userMove == true && bothNoMoves != 2 && checkFullBoard(board, dimension) == false) {
            if (checkFullBoard(board, dimension) == false && userMove == true) {
                if (bothNoMoves == 1) {
                    bothNoMoves = 1;
                } 
                else {
                    bothNoMoves = 0;
                }
                // Black human: look for avail moves & keep counter of 'U's & invalid 'U's.
                doBlack = true;
                doWhite = true;
                int userInvalidSqr;
                userInvalidSqr = 0;             
                for (int row = 0; row < dimension; row++) {
                    for (int col = 0; col < dimension; col++) {
                        if (userInvalidDir == 9) {
                            userInvalidSqr++;
                        }
                        userInvalidDir = 0;
                        if (board[row][col] == 'U') {
                            char vrow = row + 'a';
                            char vcol = col + 'a';
                            int check = 0;
                            for (int deltaRow = -1; deltaRow < 2 && check == 0; deltaRow++) {
                                for (int deltaCol = -1; deltaCol < 2 && check == 0; deltaCol++) {
                                    if (checkLegalInDirection(board, dimension, vrow, vcol, 'B', deltaRow, deltaCol) == true) {
                                        wUserMoves[vrow - 'a'][vcol - 'a'] = 'B';
                                        check = 1;
                                    } else {
                                        userInvalidDir++;
                                    }
                                }
                            }
                            userAvailSqr++;
                        }
                    }
                }
                // Skip Black human's turn if # U's == # unavail moves & ++ to bothNoMoves
                if (userAvailSqr == userInvalidSqr) {
                    printf("B player has no valid move.\n");
                    doBlack = false;
                    bothNoMoves++;
                }
                if (bothNoMoves == 1 && doBlack == true) {
                    bothNoMoves = 0;
                }
                // Prompt black user for input & end game if not valid
                if (doBlack == true) {
                    printf("Enter move for colour B (RowCol): ");
                    scanf(" %c %c", &uRow, &uCol);
                    if (wUserMoves[uRow - 'a'][uCol - 'a'] == 'B') {
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
                    } else {
                        printf("Invalid move.\n");
                        userMove = false;
                    }
                }
            }
            // Go to white cpu turn if end game condtns not met & check for avail moves
            if (checkFullBoard(board, dimension) == false && userMove == true) {
                cpuInvalidDir = 0;
                userInvalidDir = 0;
                cpuAvailSqr = 0;
                userAvailSqr = 0;
                int cpuInvalidSqr;
                cpuInvalidSqr = 0;
                for (int row = 0; row <= dimension; row++) {
                    for (int col = 0; col < dimension; col++) {
                        if (cpuInvalidDir == 9) {
                            cpuInvalidSqr++;
                        }
                        cpuInvalidDir = 0;
                        if (row < dimension) {
                            if (board[row][col] == 'U') {
                                char vrow = row + 'a';
                                char vcol = col + 'a';                            
                                for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
                                    for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
                                        if (checkLegalInDirection(board, dimension, vrow, vcol, 'W', deltaRow, deltaCol) == true) {
                                        } else {
                                            cpuInvalidDir++;
                                        }
                                    }
                                }
                                cpuAvailSqr++;
                            }
                        }
                    }
                }
                // if # 'U's == # unavail moves, skip white cpu turn & ++ to bothNoMove 
                if (bothNoMoves != 2 && checkFullBoard(board, dimension) == false) {
                    if (cpuInvalidSqr == cpuAvailSqr) {
                        printf("W player has no valid move.\n");
                        doWhite = false;
                        bothNoMoves++;
                    }
                }
                if (bothNoMoves == 1 && doWhite == true) {
                    bothNoMoves = 0;
                }
                // Look for & choose the highest scoring move for white cpu
                if (bothNoMoves != 2) {
                    if (doWhite == true) {
                        for (int row = 0; row < dimension; row++) {
                            for (int col = 0; col < dimension; col++) {
                                if (board[row][col] == 'U') {
                                    char vrow = row + 'a';
                                    char vcol = col + 'a';
                                    int totalScore = 0;
                                    for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
                                        for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
                                            if (checkLegalInDirection(board, dimension, vrow, vcol, 'W', deltaRow, deltaCol) == true && scoreInDirection(board, dimension, vrow, vcol, cpu, deltaRow, deltaCol) > 0) {
                                                totalScore = scoreInDirection(board, dimension, vrow, vcol, cpu, deltaRow, deltaCol) + totalScore;
                                                tScore = &totalScore;
                                                tRow = &vrow;
                                                tCol = &vcol;
                                                if (*tScore > maxScore) {
                                                    maxScore = *tScore;
                                                    minRow = *tRow - 'a';
                                                    minCol = *tCol - 'a';
                                                    tminRow = minRow;
                                                    tminCol = minCol;
                                                }
                                            }
                                        }
                                        minRow = dimension - 1;
                                        minCol = dimension - 1;
                                    }
                                }
                            }
                        }
                        if (checkFullBoard(board, dimension) == false) {
                            maxScore = 0;
                            board[tminRow][tminCol] = 'W';
                            for (int deltaRow = -1; deltaRow < 2; deltaRow++) {
                                for (int deltaCol = -1; deltaCol < 2; deltaCol++) {
                                    if (checkLegalInDirection(board, dimension, tminRow + 'a', tminCol + 'a', 'W', deltaRow, deltaCol) == true) {
                                        for (int i = 1; board[tminRow + (deltaRow * i)][tminCol + (deltaCol * i)] == 'B'; i++) {
                                            board[tminRow + deltaRow * i][tminCol + deltaCol * i] = 'W';
                                        }
                                    }
                                }
                            }
                            printf("Computer places W at %c%c.\n", tminRow + 'a', tminCol + 'a');
                            printBoard(board, dimension);
                        }
                    }
                }
            }
        }
        // After game end condtns are met, exit loop and declare winner or tie based on # of squares
        int uScore = 0;
        for (int srow = 0; srow < dimension; srow++) {
            for (int scol = 0; scol < dimension; scol++) {
                if (board[srow][scol] == 'B') {
                    uScore++;
                }
            }
        }
        int cScore = 0;
        for (int srow = 0; srow < dimension; srow++) {
            for (int scol = 0; scol < dimension; scol++) {
                if (board[srow][scol] == 'W') {
                    cScore++;
                }
            }
        }
        if (uScore > cScore) {
            printf("B player wins.\n");
        } else if (uScore == cScore) {
            printf("Draw!\n");
        } else {
            printf("W player wins.\n");
        }
    }
    return 0;
}
