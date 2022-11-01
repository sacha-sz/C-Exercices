#include <stdio.h>
#include <stdlib.h>

int main () {
    char c;
    printf("Saisir un caractère : ");
    c = getchar();

    switch (c) {
        case '1':
            printf("un");
            break;
        case '2':
            printf("deux");
            break;
        case '3':
            printf("trois");
            break;

        default:
            printf("autre");
            break;
    }

    return 0;
}