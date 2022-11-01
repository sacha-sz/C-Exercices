/*
 * Ecrire un programme qui lit une liste de Nb nombres,
 * la décale d'un cran vers le haut(le premier doit se retrouver en dernier),
 * l'affiche puis
 * la décale vers le bas.
 * Les nombres doivent être stockés dans un tableau avec une notation en pointeurs.
 */

#include <stdio.h>
#include <stdlib.h>

int main () {
    int Nb = 0;
    int *tab = NULL;
    int i = 0;

    printf("Saisir le nombre de valeurs : ");
    scanf("%d", &Nb);

    /// Allocation de la mémoire pour le tableau et remplissage des valeurs
    tab = (int *) malloc(Nb * sizeof(int));

    for (i = 0; i < Nb; i++) {
        printf("Saisir la valeur %d : ", i + 1);
        scanf("%d", &tab[i]);
    }

    /// Décalage d'un cran vers le haut

    // Sauvegarde de la première valeur
    int temp = tab[0];
    for (i = 0; i < Nb - 1; i++) {
        // Parcours du tableau et décalage des valeurs
        tab[i] = tab[i + 1];
    }
    // Remplacement de la dernière valeur par la première
    tab[Nb - 1] = temp;

    /// Affichage du tableau
    printf("Tableau décalé d'un cran vers le haut : ");
    for (i = 0; i < Nb; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");


    /// Décalage d'un cran vers le bas
    // Sauvegarde de la dernière valeur
    temp = tab[Nb - 1];
    for (i = Nb - 1; i > 0; i--) {
        // Parcours du tableau à l'envers
        tab[i] = tab[i - 1];
    }
    // Remplacement de la première valeur par la dernière
    tab[0] = temp;

    /// Affichage du tableau
    printf("Tableau décalé d'un cran vers le bas : ");
    for (i = 0; i < Nb; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");

    /// Libération de la mémoire
    free(tab);

    return 0;
}
