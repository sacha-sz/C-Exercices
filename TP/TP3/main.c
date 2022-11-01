#include <stdio.h>
#include <unistd.h>
#include "election_presidentielle.h"
#include "interface_presidentielle.h"

#define Taille_MAX_NOM 100
#define NUM_REP_MIN 1
#define NUM_REP_MAX 12

int main() {
    // Initialisation de la liste principale des electeurs
    T_Electeur liste_elec;
    liste_elec = NULL;
    T_Electeur *liste = &liste_elec;

    // Initialisation de la liste des electeurs votants à gauche
    T_Electeur liste_elec_gauche;
    liste_elec_gauche = NULL;
    T_Electeur *liste_gauche = &liste_elec_gauche;

    // Initialisation de la liste des electeurs votants à droite
    T_Electeur liste_elec_droite;
    liste_elec_droite = NULL;
    T_Electeur *liste_droite = &liste_elec_droite;

    // Initialisation de la liste des electeurs votants blancs
    T_Electeur liste_elec_blanc;
    liste_elec_blanc = NULL;
    T_Electeur *liste_blanc = &liste_elec_blanc;

    // Initialisation de la liste des electeurs fusion
    T_Electeur liste_fusion;
    liste_fusion = NULL;
    T_Electeur *fusion = &liste_fusion;

    // Initialisation des variables de réponse
    int rep = -1;
    int rep_menu_8 = -1;

    // Initialisation de la variable de vérification de la possibilité de calculer les pourcentages
    int calcul_pourcentage_possible = 0;

    // *********** Valeurs de test ***********
    ajoutelecteur(liste, "Emma", 34432, 1);
    ajoutelecteur(liste, "Jade", 65921, 2);
    ajoutelecteur(liste, "Louise", 70186, 3);
    ajoutelecteur(liste, "Alice", 45762, 4);
    ajoutelecteur(liste, "Chloe", 12456, 1);
    ajoutelecteur(liste, "Lina", 10247,5);
    ajoutelecteur(liste, "Lea", 54763, 7);
    ajoutelecteur(liste, "Rose", 40239, 4);
    ajoutelecteur(liste, "Anna", 42597, 1);
    ajoutelecteur(liste, "Marwa", 39350, 4);
    ajoutelecteur(liste, "Sarah", 25390, 5);
    ajoutelecteur(liste, "Sarah", 90357, 7);
    ajoutelecteur(liste, "Sarah", 84256, 9);
    ajoutelecteur(liste, "Tom", 60606, 4);
    ajoutelecteur(liste, "Pierre", 51247, 5);
    // *****************************************


    // Initialisation du menu principal à l'aide d'une boucle do while afin de rentrer au moins une fois dans le menu
    do {
        // Affichage du menu principal à l'aide du fichier interface_presidentielle.h
        affiche_menu();

        // Récupération de la réponse de l'utilisateur
        scanf("%d", &rep);

        // Affichage d'une ligne vide
        printf("\n");

        // Vérification de la réponse de l'utilisateur si elle est mauvaise la remettre à -1
        if (rep > NUM_REP_MAX || rep < NUM_REP_MIN) rep = -1;

        /*
         * On passe à l'affichage de chaque fonction en fonction de la réponse de l'utilisateur
         * Et de l'affichage du message d'erreur en cas de mauvaise réponse (default)
         * A l'aide de switch permettant de gérer les différents cas
         */
        switch (rep) {
            case 1 :
                // On ne fait rien (pas de break) afin de passer dans le cas 2
            case 2:
                // Affichage d'un message dynamique en fonction de la réponse de l'utilisateur
                if (rep==1) printf("\t------ Entrer les electeurs ------\n");
                else printf("\t------ Ajouter les electeurs ------\n");

                // Création d'un nouvel élécteur
                rep = 1;

                do {
                    // Affichage de la liste des candidats
                    affiche_candidat();

                    // On initialise le nom de l'électeur
                    char nom[Taille_MAX_NOM];
                    printf("Veuillez saisir le nom de l'electeur :\n");
                    scanf("%s", &nom);
                    while (getchar() != '\n');

                    // On initialise le cin de l'électeur en appelant la fonction saisie_electeur_cin
                    long cin = saisie_electeur_cin();


                    // On initialise le vote de l'électeur
                    int vote = 0;
                    printf("Veuillez saisir le choix de l'electeur (1 a 5) :\n");
                    scanf("%d", &vote);
                    if (vote > 5 || vote <= 0) {
                        // Tout autre vote que 1 à 4 sera considéré comme un vote blanc donc vote = 5, vérification supplémentaire à l'affichage
                        vote = 5;
                    }

                    // On ajoute l'électeur à la liste principale
                    ajoutelecteur(liste, nom, cin, vote);
                    printf("Informations ajoutees :\n");
                    printf("\tNom : %s\n", nom);
                    printf("\tCIN : %ld\n", cin);
                    printf("\tChoix : %d\n", vote);
                    sleep(2);

                    do {
                        if (rep > 1 || rep < 0) {
                            printf("\nErreur de saisie, veuillez recommencer\n");
                            printf("Voulez-vous ajouter un autre electeur ? (1 pour oui, 0 pour non)\n");
                            scanf("%d", &rep);
                        } else {
                            printf("Voulez-vous ajouter un autre electeur ? (1 pour oui, 0 pour non)\n");
                            scanf("%d", &rep);
                        }
                    } while (rep != 0 && rep != 1);
                } while(rep != 0);
                break;

            case 3 :
                // Affichage d'un message informatif pour l'utilisateur
                printf("\t------ Supprimer un electeur ------\n");

                // On initialise le cin de l'électeur en appelant la fonction saisie_electeur_cin
                long cin_electeur_supprimer = saisie_electeur_cin();

                // On supprime l'électeur de la liste principale
                supprime_electeur(liste, cin_electeur_supprimer);
                sleep(2);
                break;

            case 4 :
                // Affichage d'un message informatif pour l'utilisateur
                printf("\t------ Supprimer le dernier electeur ------\n");

                // On supprime le dernier électeur de la liste principale
                supprime_dernier_elec(liste);
                sleep(2);
                break;

            case 5 :
                // Affichage d'un message informatif pour l'utilisateur
                printf("\t------ Rechercher un electeur ------\n");

                // On initialise le cin de l'électeur en appelant la fonction saisie_electeur_cin
                long cin_electeur_rechercher = saisie_electeur_cin();

                // On recherche l'électeur dans la liste principale
                trouve_electeur(liste, cin_electeur_rechercher);
                sleep(3);
                break;

            case 6 :
                // Affichage d'un message informatif pour l'utilisateur
                printf("\t------ Affichage de la liste des electeurs ------\n");

                // On affiche la liste des électeurs
                afficheliste(*liste);
                sleep(5);
                break;

            case 7 :
                // Affichage d'un message informatif pour l'utilisateur
                printf("\t------ Calculer le nombre des electeurs ------\n");

                // On initialise le nombre d'électeurs
                int nb_electeurs = 0;
                nb_electeurs = compte_electeur(liste);

                // On affiche le nombre d'électeurs
                printf("Le nombre d'electeur est de : %d\n", nb_electeurs);
                sleep(2);
                break;

            case 8:
                // Affichage d'un message informatif pour l'utilisateur
                printf("\t------ Decoupage de la liste ------\n");

                // On initialise les trois sous-listes en découpant la liste principale
                decoupeliste(*liste, liste_gauche, liste_droite, liste_blanc);

                // On affiche les options supplémentaires avec une boucle do while
                printf("Vous pouvez effectuer une action supplementaire.\n");

                do {
                    // On affiche le menu secondaire
                    affiche_menu_secondaire();

                    // On récupère le choix de l'utilisateur
                    scanf("%d", &rep_menu_8);
                    switch (rep_menu_8) {
                        case 1:
                            // Affichage d'un message informatif pour l'utilisateur
                            printf("\t------ Tri des sous listes ------\n");

                            // On trie les sous-listes
                            triliste(liste_gauche);
                            triliste(liste_droite);
                            triliste(liste_blanc);
                            sleep(2);
                            break;

                        case 2:
                            // Affichage d'un message informatif pour l'utilisateur
                            printf("\t------ Affichage des sous listes ------\n");

                            // On affiche les sous-listes
                            printf("\nListe gauche :\n");
                            afficheliste(*liste_gauche);

                            printf("\nListe droite :\n");
                            afficheliste(*liste_droite);

                            printf("\nListe blanc :\n");
                            afficheliste(*liste_blanc);

                            sleep(5);
                            break;
                        case 3:
                            // Affichage d'un message informatif pour l'utilisateur
                            printf("\t------ Fusion des sous listes ------\n");

                            printf("On fusionne les sous-listes en une liste que l'on trie:");
                            // On fusionne les sous-listes vers la liste gauche
                            *fusion = fusionlistes(liste_gauche, *liste_droite);

                            // Une fois la fusion faite, on libère la mémoire des sous-listes
                            printf("On libere la memoire des sous-listes:");
                            libereliste(*liste_gauche);
                            *liste_gauche = NULL;
                            *liste_droite = NULL;

                            // On rend posssible le calcul du pourcentage
                            calcul_pourcentage_possible = 1;
                            printf("\n");
                            sleep(2);
                            break;
                        case 4:
                            // Affichage d'un message informatif pour l'utilisateur
                            affiche_message_quitter();
                            break;
                        default:
                            // Affichage d'un message informatif pour l'utilisateur
                            affiche_message_erreur (NUM_REP_MIN, 4);
                            break;
                    }
                } while (rep_menu_8 != 4); // Tant que l'utilisateur ne quitte pas le menu secondaire, on continue la boucle
                break;

            case 9 :
                // Affichage d'un message informatif pour l'utilisateur
                printf("\t------ Calcul des pourcentages ------\n");

                // On vérifie que le calcul du pourcentage est possible
                if (calcul_pourcentage_possible == 1) {
                    // On initialise les deux pourcentages
                    int nb_electeurs_gauche = 0;
                    int nb_electeurs_droite = 0;

                    // On calcule le nombre d'électeurs (ayant voté à gauche ou à droite)
                    int nb_electeur = compte_electeur(fusion);

                    // On calcule le nombre d'électeurs ayant voté à gauche
                    nb_electeurs_gauche = compteGD(*fusion);

                    // On en déduit le nombre d'électeurs ayant voté à droite
                    nb_electeurs_droite = nb_electeur - nb_electeurs_gauche;

                    // On calcule puis on affiche le pourcentage de gauche
                    float pourcentage_gauche = ((float) nb_electeurs_gauche / (float) nb_electeur) * 100;
                    printf("Le pourcentage d'electeurs de gauche est de : %.3f %\n", pourcentage_gauche);

                    // On calcule puis on affiche le pourcentage de droite
                    float pourcentage_droite = ((float) nb_electeurs_droite / (float) nb_electeur) * 100;
                    printf("Le pourcentage d'electeurs de droite est de : %.3f %\n", pourcentage_droite);
                    sleep(3);
                }
                else {
                    // Si le calcul du pourcentage n'est pas possible, on affiche un message d'erreur
                    printf("Vous ne pouvez pas calculer les pourcentages car les listes n'ont pas ete fusionnes.\n");

                    //  On guide l'utilisateur pour qu'il puisse faire une fusion des sous-listes pour pouvoir calculer les pourcentages
                    printf("Veuillez selectionner 8 puis 3 puis revenir effectuer les calculs.\n");
                    sleep(3);
                }
                break;

            case 10 :
                // Affichage d'un message informatif pour l'utilisateur
                printf("\t------ Tri de la liste principale ------\n");

                // On trie la liste principale
                triliste(liste);
                // On affiche la liste triée
                afficheliste(*liste);
                sleep(5);
                break;

            case 11 :
                // Affichage d'un message informatif pour l'utilisateur
                printf("\t------ Liberation des listes ------\n");

                // On libère les listes et on affiche un message de confirmation
                printf("Liberation de la liste principale:");
                libereliste(*liste);
                printf("\nLiberation de la liste gauche:");
                libereliste(*liste_gauche);
                printf("\nLiberation de la liste droite:");
                libereliste(*liste_droite);
                printf("\nLiberation de la liste fusion:");
                libereliste(*liste_blanc);

                *liste = NULL;
                *liste_gauche = NULL;
                *liste_droite = NULL;
                *liste_blanc = NULL;
                printf("\n\n");
                break;



            case NUM_REP_MAX :
                // Affichage d'un message informatif pour l'utilisateur à l'aide de la fonction affiche_message_quitter
                affiche_message_quitter();
                break;

            default:
                // Affichage d'un message informatif pour l'utilisateur à l'aide de la fonction affiche_message_erreur
                affiche_message_erreur(NUM_REP_MIN, NUM_REP_MAX);
                break;
        }
    } while (rep != NUM_REP_MAX); // Tant que l'utilisateur ne quitte pas le programme

    // Affiche le message de fin
    printf("===========================\tFIN\t===========================\n");

    // Retourne le code de sortie
    return 0;
}

