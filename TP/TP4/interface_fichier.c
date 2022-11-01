#include "interface_fichier.h"
#include "stdio.h"
#include "stdlib.h"

void affiche_menu (int debut) {
    // Afficher une ligne de séparation


    // Afficher le menu
    if (debut == 1) {
        printf("\t========================================================\n");
        printf("\t\tBienvenu dans la gestion d'une election.\n");
    }
    else {
        printf("\n\t========================================================\n");
    }
    printf("Voici le menu:\n");
    printf("1.  Charger un fichier.\n");
    printf("2.  Caracteristiques de l'index.\n");
    printf("3.  Afficher index.\n");
    printf("4.  Rechercher un mot.\n");
    printf("5.  Afficher le mot avec le maximum d'apparitions.\n");
    printf("6.  Afficher les occurrences d'un mot.\n");
    printf("7.  Construire le texte a partir de l'index.\n");
    printf("8.  Afficher le texte.\n");
    printf("9.  Quitter.\n");

    // Afficher une ligne de séparation
    printf("\t........................................................\n");

    // Afficher la question de saisie
    printf("Veuillez saisir votre choix :\n");
}

void affiche_message_quitter (void) {
    // Afficher le message de quitter
    printf("Vous avez choisi de quitter.\n");
}

void affiche_message_erreur (int rep_min, int rep_max) {
    // Afficher le message d'erreur
    printf("Vous avez choisi une option invalide.\nVeuillez saisir un nombre entre %d et %d.\n\n", rep_min, rep_max);
}