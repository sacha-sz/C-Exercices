#include "election_presidentielle.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


T_Electeur creationelecteur(void) {
    /************************************************
     *  Fonction :
     *      creationelecteur
     *  Objectif :
     *      Créer l'espace mémoire d'un électeur
     *  Entrée :
     *      Aucune
     *  Sortie :
     *      Un pointeur vers l'espace mémoire d'un électeur
     *  Fonctionnement :
     *      Alloue de l'espace mémoire pour un électeur à l'aide de malloc et affecte si possible la valeur de suivant à NULL
     ***********************************************/

    // Initialisation de l'espace nécessaire à la création d'un électeur
    electeur *electeur1 = malloc(sizeof(electeur));

    // Test du bon fonctionnement l'allocation
    if (electeur1 != NULL) {
        // Si l'allocation est bonne, on initialise le champ suivant de l'électeur
        electeur1->suivant = NULL;
    }

    // On retourne l'électeur créé (NULL, ou un electeur ayant le champ suivant initialisé)
    return electeur1;
}

void afficheliste(T_Electeur liste_electeur) {
    /************************************************
     *  Fonction :
     *      afficheliste
     *  Objectif :
     *      Afficher la liste des électeurs
     *  Entrée :
     *      Un pointeur vers la liste des électeurs
     *  Sortie :
     *      Aucune (affichage dans le terminal uniquement)
     *  Fonctionnement :
     *      Affiche les électeurs de la liste à l'aide de printf après avoir tester la non NULLité de la liste
     ************************************************/

    // Test de non nullité de la liste
    if (liste_electeur != NULL) {

        // On parcourt la liste
        while (liste_electeur != NULL) {
            // On affiche les informations de l'électeur
            printf("Nom : %s\n", liste_electeur->nom);
            printf("Cin : %ld\n", liste_electeur->cin_num);
            printf("Votant : %d\n\n", liste_electeur->choix);

            // On passe à l'électeur suivant
            liste_electeur = liste_electeur->suivant;
        }
        // On affiche un message de confirmation du bon déroulement de la fonction
        printf("\nVotre liste d'electeurs a ete affichee\n");
    }
    else {
        // Si la liste est vide, on affiche un message d'erreur (confirmant la fin de la fonction)
        printf("\nCette liste est  vide.\n");
    }
}

void ajoutelecteur(T_Electeur *liste, char nom[], long cin, int vote) {
    /************************************************
     *  Fonction :
     *      ajoutelecteur
     *  Objectif :
     *      Ajouter un électeur à la liste des électeurs, dans l'ordre alphabétique
     *  Entrée :
     *      Un pointeur vers la liste des électeurs, le nom de l'électeur à ajouter, le cin de l'électeur à ajouter et le vote de l'électeur à ajouter
     *  Sortie :
     *      Aucune (affichage dans le terminal uniquement)
     *  Fonctionnement :
     *      On crée un électeur en mémoire puis on lui affecte les valeurs entrées en paramètre et on l'ajoute à la liste
     *      Pour l'ajouter, on parcourt la liste jusqu'à trouver l'électeur qui doit être placé après (en tête de liste ou en fin de liste ou entre deux électeurs)
     ***********************************************/
    T_Electeur t_elec = creationelecteur();
    if (t_elec != NULL) {
        // Initialisation des champs
        t_elec->cin_num = cin;

        if (vote > 5 || vote <= 0) {
            // Tout autre vote que 1 à 4 sera considéré comme un vote blanc donc vote = 5, vérification supplémentaire à la partie main
            vote = 5;
            t_elec->choix = vote;

        }
        else {
            t_elec->choix = vote;

        }


        // On copie le nom dans le champ nom de l'électeur dont l'espace mémoire est alloué
        t_elec->nom = malloc(strlen(nom) * sizeof (char));
        strcpy(t_elec->nom, nom);

        // On initialise le champ actuel de l'électeur
        T_Electeur actuel = *liste;

        // Si la liste est vide, on affecte directement l'électeur en tête de liste
        if (actuel==NULL){
            *liste = t_elec;
        }
        else {
            // Sinon, on parcourt la liste jusqu'à trouver soit le dernier électeur soit un électeur dont le nom est inférieur au nom de l'électeur à ajouter

            // On initialise le champ précédent, le précédent de l'électeur actuel
            T_Electeur precedent = NULL;

            // On parcourt la liste jusqu'à trouver soit le dernier électeur soit un électeur dont le nom est inférieur au nom de l'électeur à ajouter
            while (actuel != NULL && strcmp(actuel->nom, t_elec->nom) < 0) {
                // On affecte au champ précédent l'électeur actuel
                precedent = actuel;
                // On passe à l'électeur suivant
                actuel = actuel->suivant;
            }
            if (precedent==NULL) {
                // Si le champ précédent est NULL, c'est que l'électeur à ajouter est le premier de la liste
                // On affecte directement l'électeur en tête de liste
                t_elec -> suivant = *liste;
                *liste = t_elec;
            }
            else if (actuel==NULL) {
                // Si l'électeur actuel est NULL, c'est que l'électeur à ajouter est le dernier de la liste
                // On fait pointer le précédent vers l'électeur à ajouter
                precedent->suivant = t_elec;
            }
            else {
                // Sinon, on fait pointer le précédent vers l'électeur à ajouter et on fait pointer l'électeur à ajouter vers l'électeur actuel
                t_elec->suivant = actuel;
                precedent->suivant = t_elec;
            }
        }
    }
    else {
        // Si l'électeur n'a pas pu être créé, on affiche un message d'erreur (confirmant la fin de la fonction)
        printf("\nL'electeur n'a pas pu etre cree.\n");
    }
}

int compte_electeur (T_Electeur *liste) {
    /************************************************
     *  Fonction :
     *      compte_electeur
     *  Objectif :
     *      Compte le nombre d'électeurs dans la liste des électeurs
     *  Entrée :
     *      Un pointeur vers la liste des électeurs
     *  Sortie :
     *      Le nombre d'électeurs dans la liste
     *  Fonctionnement :
     *      On initialise le compteur à 0
     *      On parcourt la liste jusqu'à trouver le dernier électeur
     *      On incrémente le compteur
     ***********************************************/

    // On initialise le compteur
    int nb_electeur = 0;

    // On initialise le champ t_elec qui est l'électeur actuel
    T_Electeur t_elec = *liste;

    // On parcourt la liste jusqu'à trouver le dernier électeur
    while (t_elec != NULL) {
        // On incrémente le compteur tant qu'on n'est pas arrivé à la fin de la liste
        nb_electeur++;
        // On passe à l'électeur suivant
        t_elec = t_elec->suivant;
    }

    // On retourne le nombre d'électeurs (positif s'il y a des électeurs dans la liste ou 0 si la liste est vide)
    return nb_electeur;
}

int trouve_electeur(T_Electeur *liste, long cin) {
    /************************************************
     *  Fonction :
     *      trouve_electeur
     *  Objectif :
     *      Trouve un électeur dans la liste des électeurs
     *  Entrée :
     *      Un pointeur vers la liste des électeurs
     *      Un numéro de cin de l'électeur à trouver
     *  Sortie :
     *      Un entier qui indique si l'électeur a été trouvé ou non (1 si oui, 0 si non)
     *  Fonctionnement :
     *      On initialise le champ t_elec qui est l'électeur actuel
     *      On parcourt la liste jusqu'à trouver le dernier électeur ou un électeur dont le numéro de cin est égal au numéro de cin de l'électeur à trouver
     *      Si l'électeur a été trouvé, on affiche ses informations puis on retourne 1
     *      Sinon, on affiche un message d'erreur et on retourne 0
     ***********************************************/

    // On initialise le champ t_elec qui est l'électeur actuel
    T_Electeur t_elec = *liste;

    // On parcourt la liste jusqu'à trouver l'électeur dont le numéro de cin est celui recherché ou jusqu'à trouver le dernier électeur
    while (t_elec != NULL && t_elec->cin_num != cin) {
        // On passe à l'électeur suivant
        t_elec = t_elec->suivant;
    }

    // On retourne 1 si l'électeur a été trouvé, 0 sinon et on affiche un message approprié
    if (t_elec == NULL) {
        printf("\nL'electeur avec le numero de cin %ld n'a pas ete trouve.\n", cin);

        return 0;
    }
    else {
        // L'électeur a été trouvé
        printf("\nL'electeur avec le numero de cin %ld a ete trouve.\nVoici ses informations :\n", cin);

        // On affiche les informations de l'électeur
        printf("\tNom : %s\n", t_elec->nom);
        printf("\tCin : %ld\n", t_elec->cin_num);
        printf("\tVotant : %d\n\n", t_elec->choix);
        // On retourne 1
        return 1;
    }
}

void supprime_electeur(T_Electeur *liste, long cin) {
    /************************************************
     *  Fonction :
     *      supprime_electeur
     *  Objectif :
     *      Supprime un électeur dans la liste des électeurs
     *  Entrée :
     *      Un pointeur vers la liste des électeurs
     *      Le numéro de cin de l'électeur à supprimer
     *  Sortie :
     *      Aucune (affichage sur le terminal uniquement)
     *  Fonctionnement :
     *      On initialise le champ t_elec qui est l'électeur actuel
     *      On parcourt la liste jusqu'à trouver le dernier électeur ou un électeur dont le numéro de cin est égal au numéro de cin de l'électeur à supprimer
     *      Si l'électeur a été trouvé, on supprime l'électeur
     *      Sinon, on affiche un message d'erreur (si la liste est vide ou si l'électeur n'a pas été trouvé)
     ***********************************************/

    // On initialise t_elec pointant vers le début de la liste et precedent pointant vers l'électeur précédent initialisé à NULL
    T_Electeur t_elec = *liste;
    T_Electeur precedent = NULL;

    // Test de la non-nullité de la liste
    if (t_elec != NULL) {
        // On parcourt la liste jusqu'à trouver l'électeur avec son cin et dans le cas échéant jusqu'à la fin
        while (t_elec->suivant != NULL && t_elec->cin_num != cin) {
            // On affecte au champ précédent l'électeur  et on passe à l'électeur suivant
            precedent = t_elec;
            t_elec = t_elec->suivant;
        }

        // Une fois la fin boucle while finie nous sommes soit au niveau de l'électeur soit à la fin de la liste

        // Test de la position de sortie de la boucle
        if (precedent == NULL && t_elec->cin_num == cin) {
            // Si nous voulons supprimer le premier électeur

            // *liste va pointer vers l'électeur suivant
            *liste = t_elec->suivant;

            // On libère ensuite la mémoire
            free(t_elec);
            printf("\nL'electeur avec le numero de cin %ld a ete supprime.\n", cin);
        }
        else if (t_elec->cin_num == cin) {
            // Si nous voulons supprimer un électeur et que nous ne sommes pas en début de liste

            // L'électeur précédent va pointer vers l'électeur suivant
            precedent->suivant = t_elec->suivant;

            // On libère ensuite la mémoire
            free(t_elec);
            printf("\nL'electeur avec le numero de cin %ld a ete supprime.\n", cin);
        }
        else {
            // Si on est arrivé à la fin de la liste et que l'électeur n'a pas été trouvé, on affiche un message
            printf("\nCette personne n'existe pas\n");
        }
    }
    else {
        // Affiche un message en cas de liste vide
        printf("La liste est vide\n");
    }
}

void decoupeliste(T_Electeur liste, T_Electeur *liste_gauche, T_Electeur *liste_droite, T_Electeur *liste_blanc) {
    /************************************************
     *  Fonction :
     *      decoupeliste
     *  Objectif :
     *      Découpe la liste des électeurs en trois listes (gauche, droite et blanc)
     *  Entrée :
     *      Une liste d'électeurs à découper et les trois listes à remplir (avec un pointeur pour chaque liste)
     *  Sortie :
     *      Aucune (affichage sur le terminal uniquement)
     *  Fonctionnement :
     *      On initialise le champ t_elec qui est l'électeur actuel
     *      On parcourt la liste jusqu'à trouver le dernier électeur
     *      A chaque fois qu'on trouve un électeur, on l'ajoute à la liste correspondante
     ***********************************************/

    // On initialise t_elec pointant vers le début de la liste
    T_Electeur t_elec = liste;

    // On parcourt la liste jusqu'à trouver le dernier électeur
    while (t_elec != NULL) {
        // On teste le vote de l'électeur et on l'ajoute à la liste correspondante

        // On ajoute l'électeur à la liste gauche s'il a voté 1 ou 3
        if (t_elec->choix == 1 || t_elec->choix == 3){
            // On appelle la fonction ajoutelecteur pour ajouter l'électeur à la liste gauche
            ajoutelecteur(liste_gauche, t_elec->nom, t_elec->cin_num, t_elec->choix);
        }
        // On ajoute l'électeur à la liste droite s'il a voté 2 ou 4
        else if (t_elec->choix == 2 || t_elec->choix == 4){
            // On appelle la fonction ajoutelecteur pour ajouter l'électeur à la liste droite
            ajoutelecteur(liste_droite, t_elec->nom, t_elec->cin_num, t_elec->choix);
        }
        // On ajoute l'électeur à la liste blanc dans tous les autres cas (vote = 5)
        else {
            // On appelle la fonction ajoutelecteur pour ajouter l'électeur à la liste blanc
            ajoutelecteur(liste_blanc, t_elec->nom, t_elec->cin_num, t_elec->choix);
        }

        // On passe à l'électeur suivant
        t_elec = t_elec->suivant;
    }
    // On affiche un message pour indiquer que la liste a été découpée
    printf("\nLa liste a ete decoupee\n");
}

void triliste(T_Electeur *liste) {
    /************************************************
     *  Fonction :
     *      triliste
     *  Objectif :
     *      Trier la liste des électeurs par ordre croissant de cin à l'aide du tri à bulles
     *  Entrée :
     *      Une liste d'électeurs à trier
     *  Sortie :
     *      Aucune (affichage sur le terminal uniquement)
     *  Fonctionnement :
     *      On initialise le champ t_elec qui est l'électeur actuel
     *      Si le cin de l'électeur actuel est plus grand que le cin de l'électeur suivant, on échange les deux électeurs
     *      On parcourt la liste jusqu'à ce qu'elle soit triée (tri reste à vrai, aucun échange n'a été fait)
     ***********************************************/


    // On initialise t_elec pointant vers le début de la liste
    T_Electeur actuel = *liste;

    // On teste si la liste est vide ou si elle contient un seul élément
    if (actuel == NULL || actuel->suivant == NULL) {
        printf("\n\nLa liste est vide ou ne contient qu'un element, elle ne peut pas etre triee\n\n");
    }
    //  Si la liste contient au moins deux éléments
    else {
        // Nous allons utiliser le tri à bulles pour trier la liste

        // On initialise tri comme une variable booléenne (0 : non trié, 1 : trié) qui va nous permettre de savoir si la liste est triée ou non
        int tri = 0;

        // On initialise precedent et tmp qui permettront les échanges d'éléments
        T_Electeur precedent;
        T_Electeur tmp;

        // On parcourt la liste tant que la liste n'est pas triée
        while (tri == 0) {
            // On suppose que la liste est triée
            tri = 1;

            // On initialise precedent à NULL
            precedent = NULL;
            // On parcourt la liste en initialisant actuel à la première valeur
            actuel = *liste;

            // On parcourt la liste tant que l'élément actuel n'est pas le dernier
            while (actuel->suivant != NULL) {
                // On teste si le cin de l'élément actuel est plus petit que celui de l'élément suivant
                if (actuel->cin_num > actuel->suivant->cin_num) {
                    // On change la valeur de tri pour dire que la liste n'est pas triée
                    tri = 0;
                    // On échange les deux éléments

                    // Si le précédent est NULL, c'est que l'élément actuel est le premier de la liste
                    if (precedent == NULL) {
                        // On échange les deux éléments

                        // On affecte à tmp l'élément suivant de l'élément actuel
                        tmp = actuel->suivant;

                        // On fait pointer l'élément actuel vers l'élément suivant de l'élément suivant
                        actuel->suivant = actuel->suivant->suivant;

                        // On fait pointer l'élément suivant de l'élément suivant vers l'élément actuel
                        tmp->suivant = actuel;

                        // On change la valeur de precedent pour pointer vers l'élément tmp
                        precedent = tmp;

                        // On fait pointer la liste vers l'élément precedent
                        *liste = precedent;
                    } else {
                        // On échange les deux éléments

                        // On affecte à tmp l'élément suivant de l'élément actuel
                        tmp = actuel->suivant;

                        // On fait pointer l'élément actuel vers l'élément suivant de l'élément suivant
                        actuel->suivant = actuel->suivant->suivant;

                        // On fait pointer l'élément precedent vers l'élément tmp
                        precedent->suivant = tmp;

                        // On fait pointer l'élément tmp vers l'élément actuel
                        tmp->suivant = actuel;

                        // On fait pointer l'élément precedent vers l'élément tmp
                        precedent = tmp;
                    }
                }
                    // Si les éléments sont dans l'ordre, on passe à l'élément suivant
                else {
                    // On passe à l'élément suivant et on met à jour precedent
                    precedent = actuel;
                    actuel = actuel->suivant;
                }
            }
        }
        // On affiche un message de confirmation
        printf("\nLa liste a ete triee\n\n");
    }
}

T_Electeur fusionlistes(T_Electeur *liste_gauche, T_Electeur liste_droite) {
    /************************************************
    *  Fonction :
    *      fusionlistes
    *  Objectif :
    *      fusionner deux listes d'électeurs
    *  Entrée :
    *      deux listes d'électeurs (un pointeur vers la liste gauche et une liste droite)
    *  Sortie :
    *      une liste d'électeurs fusionnée
    *  Fonctionnement :
    *      On teste la non-NULLité des listes
    *      Si une des listes est NULL, on renvoie l'autre liste (si les deux sont NULL, cela renvoie NULL)
    *      Sinon, on parcourt la liste gauche jusqu'au dernier élément et on le fait pointer vers le premier élément de la liste droite
    ***********************************************/


   // On initialise actuel_gauche au pointeur de la liste gauche et actuel_droite au pointeur de la liste droite
   T_Electeur actuel_droite = liste_droite;
   T_Electeur actuel_gauche = *liste_gauche;

   // On teste l'existence de la liste gauche et de la liste droite
   if (actuel_droite == NULL) {
       // Si la liste droite n'existe pas, on retourne la liste gauche
       return actuel_gauche;
   }
   else if (actuel_gauche == NULL) {
       // Si la liste gauche n'existe pas, on retourne la liste droite
       return actuel_droite;
   }
   else {
       // Si les deux listes existent, on parcourt la liste gauche jusqu'au dernier élément
       while (actuel_gauche->suivant != NULL) {
           // On passe à l'électeur suivant
           actuel_gauche = actuel_gauche->suivant;
       }
       // On fait pointer le dernier élément de la liste gauche vers le premier de la liste droite
       actuel_gauche->suivant = actuel_droite;

       // On trie la liste fusionner
       triliste(&actuel_gauche);

       // On retourne la liste fusionner
       return actuel_gauche;
   }
}

int compteGD(T_Electeur liste){
   /************************************************
    *  Fonction :
    *      compteGD
    *  Objectif :
    *      Compte le nombre d'électeurs votant à gauche de la liste
    *  Entrée :
    *      Un pointeur vers la liste des électeurs
    *  Sortie :
    *      Un entier correspondant au nombre d'électeurs votant à gauche de la liste
    *  Fonctionnement :
    *      On parcourt la liste
    *      Si le vote de l'électeur est à gauche (choix 1 ou 3), on incrémente le compteur
    *      On retourne le compteur
    ***********************************************/

    // On initialise le compteur
    int nb_voix_gauche = 0;

    // On initialise t_elec comme l'élément actuel sur la liste
    T_Electeur t_elec = liste;

    // On parcourt la liste
    while (t_elec != NULL) {
        if(t_elec->choix == 1 || t_elec->choix == 3){
            // On incrémente le compteur si le choix est 1 ou 3 (vote gauche)
            nb_voix_gauche++;
        }
        // On passe à l'élément suivant
        t_elec = t_elec->suivant;
    }
    // On retourne le nombre de voix
    return nb_voix_gauche;
}

void libereliste (T_Electeur liste) {
    /************************************************
     *  Fonction :
     *      libereliste
     *  Objectif :
     *      Libère la mémoire allouée à la liste des électeurs
     *  Entrée :
     *      Un pointeur vers la liste des électeurs
     *  Sortie :
     *      Aucune (affichage sur le terminal uniquement)
     *  Fonctionnement :
     *      On parcourt la liste
     *      On libère la mémoire allouée à chaque élément, pour cela
     *          on la stocke dans un pointeur temporaire
     *          on passe à l'élément suivant
     *          on libère la mémoire allouée à l'élément stocké dans le pointeur temporaire
     ***********************************************/

    // On parcourt la liste
    while (liste != NULL) {
        // On initialise un pointeur temporaire
        T_Electeur tmp;

        // On stocke l'élément actuel dans une variable temporaire
        tmp = liste;

        // On passe à l'élément suivant
        liste = liste->suivant;

        // On libère la mémoire
        free(tmp);
    }
    // On affiche un message de fin de traitement
    printf("\nLa liste a ete liberee\n");
}

void supprime_dernier_elec (T_Electeur *liste) {
    /************************************************
     *  Fonction :
     *      supprime_dernier_elec
     *  Objectif :
     *      Supprime le dernier électeur de la liste
     *  Entrée :
     *      Un pointeur vers la liste des électeurs
     *  Sortie :
     *      Aucune (affichage sur le terminal uniquement)
     *  Fonctionnement :
     *      On parcourt la liste
     *      On stocke l'élément actuel dans une variable precedent
     *      On passe à l'élément suivant
     *      On supprime le dernier élément de la liste
     ***********************************************/

    // On initialise un pointeur actuel et un pointeur précédent
    T_Electeur t_elec = *liste;
    T_Electeur precedent = NULL;

    // Teste de la non-nullité de la liste
    if (t_elec != NULL) {
        // On parcourt la liste jusqu'à la fin
        while (t_elec->suivant != NULL) {
            // On affecte à précédent l'élément actuel
            precedent = t_elec;
            // On passe à l'élément suivant
            t_elec = t_elec->suivant;
        }
        // Test si la liste contient un seul élément
        if (precedent == NULL) {
            // On met à NULL la tête de liste
            *liste = NULL;
            free(t_elec);
        }
        else {
            // On supprime le dernier élément de la liste
            precedent->suivant = NULL;
            free(t_elec);
        }
        // On affiche un message de confirmation
        printf("\nL'electeur a ete supprime\n");
    }
    else {
        // On affiche un message d'erreur
        printf("\nLa liste est vide\n");
    }
}