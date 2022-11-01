#include <stdio.h>
#include <stdlib.h>

int main () {
    //Pointeur pour les lignes
    int tab*[4];

    for (int i = 0; i < 3; i++) {
        //Allocation de la mémoire pour la ligne
        tab[i] = malloc(4*sizeof(int));
        for (int j = 0; j < 4; j++) {
            tab[i][j] = 12 + i * 4 + j;
        }
    }

    // Affichage du tableau
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }

    // Libération de la mémoire
    for (int i = 0; i < 3; i++) {
        free(tab[i]);
    }

    return 0;
}