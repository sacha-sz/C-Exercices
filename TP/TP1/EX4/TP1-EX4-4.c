#include <stdio.h>
#include <stdlib.h>

int main () {
    int i;
    int * j;

    i = 5;
    j = &i;

    printf("i = %d\n", i);
    printf("Valeur pointee par j = %d\n", *j);

    *j++;
    printf("i = %d\n", i);

    i *= 5;
    printf("Valeur pointee par j = %d\n", *j);

    j++;
    printf("Valeur pointee par j = %d\n", *j);

    return 0;
}