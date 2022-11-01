#include <stdio.h>
#include <stdlib.h>

int main () {
    int tab[3][4];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            tab[i][j] = 12 + i * 4 + j;
        }
    }

    return 0;
}