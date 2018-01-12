/* 
 * File:   Lab9.c
 * Author: Nicholas Park
 *
 * Created on November 26, 2015, 2:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 1024

const int MAX_LIBRARY_SIZE = 100;
int libraryCell = 0;

typedef struct song {
    char songName[MAX_LENGTH];
    char artist[MAX_LENGTH];
} Song;

void swap(Song *song1, Song *song2) {
    Song temp = *song1;
    *song1 = *song2;
    *song2 = temp;
}

void getStringFromUserInput(char s[], int maxStrLength) {
    int i = 0;
    char c;

    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;
    s[i] = '\0';
}

void insertInLibrary(Song newSong, Song Library[/*MAX_LENGTH*/]) {
    Library[libraryCell] = newSong;
    libraryCell++;
}

void printMusicLibraryEmpty(void) {
    printf("\nThe music library is empty.\n");
}

void printMusicLibraryTitle(void) {
    printf("\nMy Personal Music Library: \n");
}

void printList(Song Library[/*MAX_LENGTH*/], int listLength) {
    if (listLength == 0) {
        printMusicLibraryEmpty();
    } else {
        printMusicLibraryTitle();
        for (int i = 0; i < listLength; i++) {
            printf("\n%s\n%s\n", Library[i].songName, Library[i].artist);
        }
    }
}

void cocktailSort(Song Library[MAX_LENGTH], int size) {
    bool goingUp = true;
    bool sorted = false;
    for (int top = size - 1; top > 0 && !sorted; top--) {
        sorted = true;

        //goingUp = true;
        if (goingUp == true) {
            for (int i = 0; i < top; i++) {

                if (strcmp(Library[i].artist, Library[i + 1].artist) > 0) {
                    swap(&Library[i], &Library[i + 1]);
                sorted = false;
                }
            }
            goingUp = false;
        }
        else {
            for (int i = top; i > 0; i--) {
                if (strcmp(Library[i].artist, Library[i - 1].artist) < 0) {
                    swap(&Library[i], &Library[i - 1]);
                sorted = false;
                }
            }
            goingUp = true;
        }  
    }
}

int main(void) {
    Song Library[MAX_LIBRARY_SIZE];

    printf("%s", "Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), S (sort by artist),\n"
            "P (print), Q (quit).\n");
    int listLength = 0;
    char response;
    char input[MAX_LENGTH];
    do {
        printf("\nCommand?: ");
        getStringFromUserInput(input, MAX_LENGTH);

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I') {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            Song newSong;
            printf("Song name: ");
            getStringFromUserInput(newSong.songName, MAX_LENGTH - 1);
            printf("Artist: ");
            getStringFromUserInput(newSong.artist, MAX_LENGTH - 1);
            insertInLibrary(newSong, Library);
            listLength++; // if song successfully added
        }
        else if (response == 'S') {
            // Search for a song by its name.
            cocktailSort(Library, listLength);
            printList(Library, listLength);
        }
        else if (response == 'P') {
            // Print the music library.
            printList(Library, listLength);
        }
        else if (response == 'Q') {
            ; // do nothing, we'll catch this below
        }
        else {
            // do this if no command matched ...
            printf("\nInvalid command.\n");
        }
    } while (response != 'Q');
    return 0;
}

