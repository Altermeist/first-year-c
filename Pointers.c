#include <stdio.h>

void swap(int *m, int *n) {
  int temp = *m;
  *m = *n;
  *n = temp;
}

int *larger(int *m, int *n) {
  if (*m > *n) 
    return m;
  else
    return n;
}

int main(void) {
    // int x = 3, y = 4;
    const int num = 3;
    int *a, *b;
    for (int j = 0; j < num; j++) {
    for(int i=0; i < num; i++){
        int x = 3 + i;
        int y = 4 + i;
    a = &x;
    b = &y;
    //*a = 6;
    //*b = *b + 3;
    }
    }
    *a = *a + *b;
    if (*a > *b) {
    printf("%d %d", *a, *b);
    }
    else
    //swap(&x, &y); // or equivalently: swap(a, b);
    //printf("%d %d\n", x, y);

   // printf("larger = %d\n", *larger(&x, &y));
    return 0;
}
