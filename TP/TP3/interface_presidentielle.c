#include "interface_presidentielle.h"
#include "stdlib.h"
#include "stdio.h"

void affiche_menu(void) {
    // Afficher une ligne de séparation
    printf("\t========================================================\n");

    // Afficher le menu
    printf("\t\tBienvenu dans la gestion d'une election.\nVoici le menu:\n");
    printf("1.  Entrer des electeurs.\n");
    printf("2.  Ajouter des electeurs.\n");
    printf("3.  Supprimer un electeur.\n");
    printf("4.  Supprimer le dernier electeur.\n");
    printf("5.  Rechercher un electeur.\n");
    printf("6.  Afficher la liste des electeurs.\n");
    printf("7.  Calculer le nombre des electeurs.\n");
    printf("8.  Decouper la liste en trois sous-listes selon les choix: droite. gauche et blanc :\n");
    printf("\tSelectionnez le numero 8 avant :\n");
    printf("\ta  Trier les sous-listes.\n");
    printf("\tb  Afficher les sous-listes.\n");
    printf("\tc  Fusionner les deux sous-listes : gauche et droite.\n");
    printf("9.  Calculer les pourcentages de gauche et de droite pour le 2eme tour.\n");
    printf("10. Trier la liste principale.\n");
    printf("11. Liberer les listes.\n");
    printf("12. Quitter.\n");

    // Afficher une ligne de séparation
    printf("\t........................................................\n");

    // Afficher la question de saisie
    printf("Veuillez saisir votre choix :\n");
}

void affiche_menu_secondaire(void) {
    // Afficher le menu secondaire
    printf("Entrez le numero correspondant a votre choix :\n");
    printf("1. Trier les sous-listes\n");
    printf("2. Afficher les sous-listes,\n");
    printf("3. Fusionner les deux sous-listes : gauche et droite\n");
    printf("4. Quitter\n");

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

long saisie_electeur_cin(void) {
    // Fonction permettant de saisir un cin

    // Declaration de la variable
    long cin;

    // Saisir le cin
    printf("Veuillez saisir le cin de l'electeur :\n");
    scanf("%ld", &cin);

    // Retourner le cin saisi
    return cin;
}

void affiche_candidat(void){
    // Fonction permettant d'afficher les candidats
    printf("Format de la liste des candidats : (nom : choix a saisir(entier)    Bord)\n");
    printf("Nom 1 : 1\tGauche\n");
    printf("Nom 2 : 2\tDroite\n");
    printf("Nom 3 : 3\tGauche\n");
    printf("Nom 4 : 4\tDroite\n");
    printf("Tout autre choix : 5\tBlanc\n\n");
}