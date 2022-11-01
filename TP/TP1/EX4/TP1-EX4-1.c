#include <stdio.h>
#include <stdlib.h>

void switcher(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


int main () {
    int a = 1;
    int b = 2;
    switcher(&a, &b);
    printf("a = %d, b = %d", a, b);
}