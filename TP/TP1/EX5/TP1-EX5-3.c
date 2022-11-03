#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Jeu du pendu
int gagne (char *mot);
void cherche_mot_secret (char *mot_secret, char * mot_decouvert, char lettre);

int main ()
{
    printf("*** Jeu du pendu ***\n\n");

    // Déclaration des variables
    char mot_secret[100];
    char mot_decouvert[100];
    int nb_coups = 10;

    // Saisie du mot secret
    printf("Saisir le mot secret : ");
    scanf("%s", mot_secret);
    while (getchar() != '\n');

    // Initialisation du mot découvert
    for (size_t i=0; i<strlen(mot_secret); i++) {
        mot_decouvert[i] = '*';
    }
    mot_decouvert[strlen(mot_secret)] = '\0';

    // Affichage de lignes blanches afin de cacher le mot secret
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    // En version terminal il faut commenter la ligne précédente et décommenter la ligne correspondante ci-dessous
    // Si utilisation terminal Linux
    // system("clear");
    // Si utilisation terminal Windows
    // system("cls");

    char lettre;
    while (nb_coups > 0 && !gagne(mot_decouvert))
    {
        printf("Mot découvert : %s\n", mot_decouvert);
        printf("Nombre de coups restants : %d\n", nb_coups);

        printf("Saisir une lettre : ");
        scanf("%c", &lettre);
        while (getchar() != '\n');

        // Recherche de la lettre dans le mot secret
        cherche_mot_secret(mot_secret, mot_decouvert, lettre);

        nb_coups--;
    }

    if (gagne(mot_decouvert)) {
        printf("Bravo, VOUS AVEZ GAGNE :) !\n");
    }
    else
    {
        printf("VOUS AVEZ PERDU :( !\n");
        printf("Le mot secret était : %s\n", mot_secret);
    }

}

int gagne (char *mot)
{
    while(*mot != '\0') {
        if (*mot == '*') {
            return 0;
        }
        mot++;
    }
    return 1;
}

void cherche_mot_secret (char *mot_secret, char * mot_decouvert, char lettre) {
    for (size_t i=0; i<strlen(mot_secret); i++) {
        if (mot_secret[i] == lettre) {
            mot_decouvert[i] = lettre;
        }
    }
}