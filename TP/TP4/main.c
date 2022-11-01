#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "interface_fichier.h"
#include "texte.h"

#define TAILLE_MAX 100
#define NUM_REP_MAX 9
#define NUM_REP_MIN 1


int main() {

    t_Index * index = creer_index();

    int debut = 1;
    int rep = -1;
    int nb_mots = 0;
    int fichier_indexe = 0;

    do {
        affiche_menu(debut);

        scanf("%d", &rep);

        if (rep > NUM_REP_MAX || rep < NUM_REP_MIN) rep = -1;

        switch (rep) {
            case 1:
                printf("\n\t------ Indexation  fichier ------\n\n");

                if (fichier_indexe == 0)
                {
                    printf("Entrez le nom du fichier a charger :\nAu format : nom.format\t\texemple:test.txt\n");
                    char file_name[TAILLE_MAX];
                    scanf("%s", file_name);
                    while (getchar() != '\n');


                    nb_mots = indexer_fichier(index, file_name);

                    if (nb_mots == 0)
                    {
                        printf("Erreur lors de l'indexation du fichier.\n");
                    }
                    else
                    {
                        printf("Le fichier a ete indexe.\n");
                        printf("Il contient %d mots au total dont %d mots distincts.\n", nb_mots, index->nb_mots_differents);
                        fichier_indexe = 1;
                    }
                }
                else
                {
                    printf("\tLe fichier est deja indexe.\n");
                    sleep(2);
                }

                break;


            case 2:
                printf("\n\t------ Caracteristiques de l'index ------\n\n");

                if (fichier_indexe == 0)
                {
                    printf("Vous devez d'abord indexer un fichier.\n");
                    sleep(2);
                }
                else
                {

                    int hauteur_arbre = hauteur(index->racine);
                    int est_equilibre = equilibre(index->racine);

                    printf("La hauteur de l'arbre est %d.\n", hauteur_arbre);
                    printf("Il y a %d mots dans l'index.\n", index->nb_mots_total);
                    printf("Il y a %d mots distincts dans l'index.\n", index->nb_mots_differents);

                    if (est_equilibre == -1)
                    {
                        printf("Erreur arbre\n");
                    }
                    else if (est_equilibre == -2)
                    {
                        printf("L'arbre n'est pas equilibre\n");
                    }
                    else
                    {
                        printf("L'arbre est equilibre\n");
                    }
                }
                break;


            case 3:
                printf("\n\t------ Afficher index ------\n\n");

                if (fichier_indexe == 0)
                {
                    printf("Vous devez d'abord indexer un fichier.\n");
                    sleep(2);
                }
                else
                {
                    afficher_index(index);
                    printf("Fin de l'affichage.\n");
                    sleep(5);

                }
                break;



            case 4:
                printf("\n\t------ Recherche de mots ------\n\n");

                if (fichier_indexe == 0)
                {
                    printf("Vous devez d'abord indexer un fichier.\n");
                    sleep(2);
                }
                else
                {
                    printf("Entrez le mot a rechercher :");

                    char research_word[TAILLE_MAX];

                    scanf("%s", research_word);
                    while (getchar() != '\n');

                    t_Noeud * noeud = rechercher_mot(index, research_word);

                    if (noeud == NULL) {
                        printf("Le mot %s n'est pas dans l'index.\n", research_word);
                    } else {
                        afficher_noeud_recherche(noeud);
                    }
                    sleep(5);
                }
                break;


            case 5:
                printf("\n\t------ Afficher le mot avec le maximum d'apparitions ------\n\n");

                if (fichier_indexe == 0)
                {
                    printf("Vous devez d'abord indexer un fichier.\n");
                    sleep(2);
                }
                else
                {
                    afficher_max_apparition(index);
                    sleep(5);
                }

                break;


            case 6:
                printf("\n\t------ Afficher le mot et les phrases dans lesquels il est present ------\n\n");

                if (fichier_indexe == 0)
                {
                    printf("Vous devez d'abord indexer un fichier.\n");
                    sleep(2);
                }
                else
                {
                    printf("Entrez le mot a rechercher :");

                    char research_word2[TAILLE_MAX];
                    scanf("%s", research_word2);
                    while (getchar() != '\n');

                    afficher_occurences_mot(index, research_word2);
                    sleep(5);
                }

                break;


            case 7:
                printf("\n\t------ Construire le texte a partir de l'index ------\n\n");

                if (fichier_indexe == 0) {
                    printf("Vous devez d'abord indexer un fichier.\n");
                    sleep(2);
                }
                else
                {
                    printf("Entrez le nom du fichier de sortie (fichier deja existant) :");
                    char file_name_out[TAILLE_MAX];
                    scanf("%s", file_name_out);
                    while (getchar() != '\n');

                    construire_texte(index, file_name_out);
                    printf("Construction du fichier reussie");
                }
                break;


            case 8:
                printf("\n\t\t\t------ Afficher le texte ------\n\n");

                if (fichier_indexe == 0) {
                    printf("Vous devez d'abord indexer un fichier.\n");
                    sleep(2);
                }
                else
                {
                    affiche_liste_ligne(index->listeLigne);
                    printf("\t\t\t------ Fin de l'affichage ------\n");
                    sleep(5);
                }

                break;


            case NUM_REP_MAX:
                printf("\n\t------ Quitter et liberation de la memoire ------\n\n");
                if (fichier_indexe == 1)
                {
                    liberation_index(index);
                    printf("\t\tFin de la liberation de la memoire.\n\n");
                }
                else
                {
                    printf("\t\tAucun fichier n'a ete indexe.\n");
                    printf("\t\tDans ce cas, il n'y a aucune liberation de la memoire.\n");
                }
                sleep(2);
                break;

            default:
                affiche_message_erreur(NUM_REP_MIN, NUM_REP_MAX);
                break;
        }
        debut = 0;
    } while(rep != NUM_REP_MAX);
    printf("\t------ Fin du programme ------\n");
    return 0;
}
