#include <stdio.h>
#include <stdlib.h>

void affiche_table (int nb)
{
    int compteur = 0;

    printf("Table de multiplication de %d\n", nb);

    for (compteur = 0; compteur < 11; compteur++) {
        printf("\t%d * %d = %d\n", nb, compteur, nb * compteur);
    }
}

int main () {
    int valeur_saisie = 1;

    while (valeur_saisie != 0) {
        printf("Quelle table de multiplication voulez-vous, tapez 0 (zero) pour sortir ?\n");
        scanf("%d", &valeur_saisie);

        if (valeur_saisie > 10 || valeur_saisie < 0) {
            printf("Ce n'est pas dans les possibilites du programme, recommencez !\n");
        }

        else if (valeur_saisie <= 10 && valeur_saisie >0) {
            affiche_table(valeur_saisie);
        }
    }
}