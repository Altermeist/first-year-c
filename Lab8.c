//
// APS105-F15 Lab 8 Lab8.c
//
// This is a program written to maintain a personal music library, 
// using a linked list to hold the songs in the library.
//
// Author: <Your Name Goes Here>
// Student Number: <Your Student Number Goes Here>
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
const int MAX_LENGTH = 1024;

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
    char *songName;
    char *artist;
    char *genre;
    struct node *link;
} Node;

// Create a New Node for Insert command
Node *newNode(char *newsongName, char *newartist, char *newgenre, Node *link) {
    
    int songLength = strlen(newsongName) + 1;
    int artistLength = strlen(newartist) + 1;
    int genreLength = strlen(newgenre) + 1;

    Node *t = (Node *) malloc(sizeof (Node));
    
    t -> songName = (char *) malloc(songLength * sizeof(char));
    t -> artist = (char *) malloc(artistLength * sizeof(char));
    t -> genre = (char *) malloc(genreLength * sizeof(char));

    if (t != NULL) {
        strcpy(t -> songName, newsongName);
        strcpy(t -> artist, newartist);
        strcpy(t -> genre, newgenre);
        t -> link = link;
    }
    return t;
}
// Print a title for playlist
void printMusicLibraryTitle(void) {
    printf("\nMy Personal Music Library: \n");
}
// Print deletion of specified song
void songNameDeleted(char songName[]) {
    printf("\nDeleting a song with name '%s' from the music library.\n", songName);
}
// Print presence of duplicate
void songNameDuplicate(char songName[]) {
    printf("\nA song with the name '%s' is already in the music library.\n"
            "No new song entered.\n", songName);
}
// Print specified song not found
void songNameNotFound(char songName[]) {
    printf("\nThe song name '%s' was not found in the music library.\n",
            songName);
}
// Print that list is empty
void printMusicLibraryEmpty(void) {
    printf("\nThe music library is empty.\n");
}
// Print found specified song
void songNameFound(char songName[]) {
    printf("\nThe song name '%s' was found in the music library.\n\n",
            songName);
}
// Insert a non-duplicate song by creating a new node into list in alphabetical order 
Node *insertIntoOrderedList(Node *head, char *insongName, char *inartist, char *ingenre) {
    if (head == NULL || strcmp(insongName, head -> songName) < 0) // stcmp
        return newNode(insongName, inartist, ingenre, head); // a new head of the list

    if (strcmp(insongName, head -> songName) == 0) {
        songNameDuplicate(insongName);
        return head;
    }

    Node *current = head;
    while (current -> link != NULL && strcmp(insongName, current -> link -> songName) > 0) { // strcmp songName and head
        current = current -> link;
    }
    if (current -> link != NULL) {
        if (strcmp(insongName, current -> link -> songName) == 0) {
            songNameDuplicate(insongName);
            return head;
        }
    }
    current->link = newNode(insongName, inartist, ingenre, current->link);
    return head;
}

// Search for a specific song name in list and return true if found
bool search(Node *head, char *searchKey) {
  Node *current = head;
  char printCurrentArtist[MAX_LENGTH +1];
  char printCurrentGenre[MAX_LENGTH +1];
  
  while (current != NULL) {
    if (strcmp(current -> songName, searchKey) == 0 ) {
        songNameFound(searchKey);
     strcpy(printCurrentArtist, current -> artist);
    strcpy(printCurrentGenre, current -> genre);
    printf("%s\n%s\n%s\n", searchKey, printCurrentArtist, printCurrentGenre);
      return true;
    }
    current = current -> link;
  }
  songNameNotFound(searchKey);      
  return false;
}

// Delete specified song name from list
Node *deleteFirstOccurrence(Node *head, char *searchKey) {
    if (head == NULL) {
        songNameNotFound(searchKey);
        return NULL;
    }
    // If the first node is to be deleted
    if (strcmp(head -> songName, searchKey) == 0) {
        Node *secondNode = head -> link;
        free(head -> songName);
        free(head -> artist);
        free(head -> genre);
        free(head);
        songNameDeleted(searchKey);
        return secondNode;
    }

    bool found = false;
    Node *current = head;

    while (!found && current -> link != NULL) {
        if (strcmp(current -> link -> songName, searchKey) == 0) {
            found = true;
        }
        else
            current = current -> link;
    }

    // if there exists a node to be deleted
    if (current -> link != NULL) {
        Node *nodeToRemove = current -> link;
        current -> link = current -> link -> link;
        free(nodeToRemove -> songName);
        free(nodeToRemove -> artist);
        free(nodeToRemove -> genre);
        free(nodeToRemove);
        songNameDeleted(searchKey);
    }
    
    if (!found) {
        songNameNotFound(searchKey);  
    }
    return head;
}

// Delete all songs and free malloc
Node *deleteAllNodes(Node *head) {
    while (head != NULL) {        
        Node * secondNode = head -> link;
        songNameDeleted(head -> songName);
        
        free(head -> songName);
        free(head -> artist);
        free(head -> genre);
        free(head);
        head = secondNode;   
    }
    return NULL;
}

// Print current play list
void printList(Node *head) {
    Node *current = head;
    if (current == NULL) {
        printMusicLibraryEmpty();
    }
    else {
        printMusicLibraryTitle();
    while (current != NULL) {        
        printf("\n%s", current -> songName);
        printf("\n%s", current -> artist);
        printf("\n%s", current -> genre);
        printf("\n");
        current = current -> link;
    }
}
}
// Declarations of support functions
// See below the main function for descriptions of what these functions do

void getStringFromUserInput(char s[], int arraySize);
void songNameFound(char songName[]);
void songNameNotFound(char songName[]);
void songNameDeleted(char songName[]);
void artistFound(char artist[]);
void artistNotFound(char artist[]);
void printMusicLibraryEmpty(void);
//void printMusicLibraryTitle(void);

int main(void) {
    // Declare the head of the linked list.
    //Node NewNode;
    Node *head = NULL;
    char asongName[MAX_LENGTH + 1];
    char aartist[MAX_LENGTH + 1];
    char agenre[MAX_LENGTH + 1];
    
    // Announce the start of the program
    printf("%s", "Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
            "P (print), Q (quit).\n");

    char response;
    char input[MAX_LENGTH + 1];
    do {
        printf("\nCommand?: ");
        getStringFromUserInput(input, MAX_LENGTH);

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I') {
            // Insert a song into the linked list.
            // Maintain the list in alphabetical order by song name.
            printf("Song name: ");
            getStringFromUserInput(asongName, MAX_LENGTH);

            printf("Artist: ");
            getStringFromUserInput(aartist, MAX_LENGTH);            

            printf("Genre: ");
            getStringFromUserInput(agenre, MAX_LENGTH);

            head = insertIntoOrderedList(head, asongName, aartist, agenre);
        } 
        else if (response == 'D') {
            // Delete a song from the list.
            printf("\nEnter the name of the song to be deleted: ");
            getStringFromUserInput(asongName, MAX_LENGTH);
            head = deleteFirstOccurrence(head, asongName);
        } 
        else if (response == 'S') {
            // Search for a song by its name.
            printf("\nEnter the name of the song to search for: ");
            getStringFromUserInput(asongName, MAX_LENGTH);
            search(head, asongName);
        } 
        else if (response == 'P') {
            // Print the music library.
            printList(head);
        } 
        else if (response == 'Q') {
            ; // do nothing, we'll catch this below
        } 
        else {
            // do this if no command matched ...
            printf("\nInvalid command.\n");
        }
    } while (response != 'Q');

    // Delete the entire linked list.
    head = deleteAllNodes(head);
    // Print the linked list to confirm deletion.
    printList(head);
    return 0;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void getStringFromUserInput(char s[], int maxStrLength) {
    int i = 0;
    char c;

    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;
    s[i] = '\0';
}

// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.
/*
void songNameDuplicate(char songName[]) {
    printf("\nA song with the name '%s' is already in the music library.\n"
            "No new song entered.\n", songName);
}
 */

// Function to call when a song name was found in the personal music library.

//void songNameFound(char songName[]) {
//    printf("\nThe song name '%s' was found in the music library.\n",
//            songName);
//}

// Function to call when a song name was not found in the personal music library.

/*
void songNameNotFound(char songName[]) {
    printf("\nThe song name '%s' was not found in the music library.\n",
            songName);
}
*/
// Function to call when a song name that is to be deleted
// was found in the personal music library.

//void songNameDeleted(char songName[]) {
//    printf("\nDeleting a song with name '%s' from the music library.\n",
//            songName);
//}

// Function to call when printing an empty music library.
/*
void printMusicLibraryEmpty(void) {
    printf("\nThe music library is empty.\n");
}
*/
// Function to call to print a title when the entire music library is printed.

/*void printMusicLibraryTitle(void) {
    printf("\nMy Personal Music Library: ");
}
 */


// Add your functions below this line.


//   ADD STATEMENT(S) HERE