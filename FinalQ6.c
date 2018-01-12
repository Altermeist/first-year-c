#include <stdio.h>

void insertionSort(int list[], int listLength) {
  int top;

  for (top = 1; top < listLength; top++) {
    int item = list[top];
    int i = top;

    while (i > 0 && item < list[i-1]) {
      list[i] = list[i-1]; // shift data to the right to make space
      i--;
    }

    list[i] = item;
  }
}

void selectionSort(int list[], int listLength) {
  int top, largeLoc, i;

  for (top = listLength - 1; top > 0; top--) {
    // find largest from 0 to top
    largeLoc = 0;
    for (i = 1; i <= top; i++)
      if (list[i] > list[largeLoc])
        largeLoc = i;

    // put largest at top
    int temp = list[top];
    list[top] = list[largeLoc];
    list[largeLoc] = temp;
  }
}

void printArray(int list[], int listLength) {
  for (int i = 0; i < listLength; i++) 
    printf("%d ", list[i]);
  printf("\n");
}

int main(void) {
  int list[] = {6, 3, 5, 8, 2};

  insertionSort(list, 5);
  printArray(list, 5);

  int list2[] = {6, 3, 5, 8, 2};
  selectionSort(list2, 5);
  printArray(list2, 5);
}
