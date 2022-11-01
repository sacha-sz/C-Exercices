#include "texte.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_MOT 30
#define MAX_LIGNE 1000

/*********************         Fonctions de base (sans modifications)         ****************************/



t_ListePositions* creer_liste_positions (void)
{
    // Alloue et initialise une liste chaînée de positions
    t_ListePositions *liste = malloc(sizeof(t_ListePositions));

    if (liste != NULL)
    {
        liste->debut = NULL;
        liste->nb_elements = 0;
    }

    return liste;
}


int ajouter_position (t_ListePositions *listeP,int ligne, int ordre, int num_phrase)
{
    // Test d'existence de la liste et des valeurs à y ajouter
    if (listeP == NULL)
    {
        printf("Erreur : liste de positions non initialisee\n");

        return 0;

    }

    if (ligne <= 0 || ordre <= 0 || num_phrase <= 0)
    {
        printf("Erreur : Valeur de position non valide\n");

        return 0;

    }

    // Allocation de la mémoire pour la nouvelle position
    t_position *nouvel_elt = malloc(sizeof(t_position));

    if (nouvel_elt == NULL)
    {
        printf("Erreur : Echec de l'allocation memoire\n");

        return 0;

    }

    // Initialisation de la nouvelle position
    nouvel_elt->numero_ligne = ligne;
    nouvel_elt->ordre = ordre;
    nouvel_elt->numero_phrase = num_phrase;
    nouvel_elt->suivant = NULL;


    // Initialisation de deux pointeurs temporaires pour parcourir la liste
    t_Position *actuel = listeP->debut;
    t_Position *precedent = NULL;

    if (actuel == NULL)
    {
        // Si la liste est vide, on ajoute directement l'élément

        listeP->debut = nouvel_elt;

    }
    else
    {
        // Sinon on parcourt la liste jusqu'à trouver la bonne place

        while (actuel != NULL && (actuel->numero_ligne < ligne || actuel->ordre < ordre))
        {
            // Parcours de la liste jusqu'à trouver la bonne place

            precedent = actuel;
            actuel = actuel->suivant;

        }

        if (actuel != NULL && actuel->ordre == ordre && actuel->numero_ligne == ligne)
        {
            // Deux éléments présents à la même position, erreur

            printf("Erreur : Deux positions identiques\n");
            return 0;
        }

        if (precedent == NULL)
        {
            // Insertion en tête de liste

            nouvel_elt->suivant = listeP->debut;
            listeP->debut = nouvel_elt;

        }
        else if (actuel == NULL)
        {
            // Insertion à la fin de la liste

            precedent->suivant = nouvel_elt;

        }
        else
        {
            // Sinon insertion au milieu de la liste

            nouvel_elt->suivant = actuel;
            precedent->suivant = nouvel_elt;

        }
    }

    // Incrémentation du nombre d'éléments
    listeP->nb_elements++;

    return 1;
}


t_Noeud* rechercher_mot (t_Index *index, char *mot_recherche)
{
    // Test d'existence de l'index et du mot recherché
    if (index == NULL || mot_recherche == NULL)
    {
        printf("Erreur : index ou mot non initialise\n");
        return NULL;
    }

    // Initialisation d'un pointeur temporaire pour parcourir l'index
    t_Noeud *noeud_actuel = index->racine;

    // On met le mot en minuscule
    mise_en_min(mot_recherche);

    // On parcourt l'index jusqu'à trouver le mot recherché
    while (noeud_actuel != NULL && strcmp(noeud_actuel->mot, mot_recherche) != 0)
    {
        // En fonction de l'ordre lexicographique, on se déplace dans l'index vers le fils gauche ou le fils droit

        if (strcmp(noeud_actuel->mot, mot_recherche) < 0)
        {
            noeud_actuel = noeud_actuel->filsDroit;
        }
        else
        {
            noeud_actuel = noeud_actuel->filsGauche;
        }
    }

    return noeud_actuel;
}


int ajouter_noeud (t_Index *index, t_Noeud *noeud)
{
    if (index == NULL || noeud == NULL)
    {
        return 0;
    }

    if (index->racine == NULL)
    {
        index->racine = noeud;
    }
    else
    {
        // On récupère le noeud père où on doit ajouter le noeud ou le noeud déjà présent
        t_Noeud *pere = rechercher_mot_insertion(index, noeud->mot);
        if (pere->mot == noeud->mot)
        {
            // Le mot est déjà présent dans l'index
            printf("Le noeud %s est deja present dans l'index\n", noeud->mot);

            return 0;

        }
        else
        {
            // Si le noeud n'est pas déjà présent dans l'index on l'ajoute à la bonne place
            if (strcmp(pere->mot, noeud->mot) < 0)
            {
                pere->filsDroit = noeud;
            }
            else
            {
                pere->filsGauche = noeud;
            }
        }
    }
    return 1;
}


void afficher_index (t_Index *index)
{
    if (index == NULL)
    {
        return;
    }
    else
    {
        char first_letter[] = "."; // Caractère non présent dans l'alphabet pour afficher la première lettre d'un mot

        // Parcours de l'arbre en infixe pour afficher les mots dans l'ordre lexicographique
        parcours_infixe(index->racine, first_letter);
    }
}


void afficher_max_apparition(t_Index *index)
{
    if (index == NULL || index->racine == NULL)
    {
        // Cas où l'index est vide ou non initialisé
        printf("Erreur : index ou racine non initialise\n");
        return;
    }

    // On initialise la pile contenant tous les noeuds de l'arbre
    Pile *pile = empiler_arbre(index);

    // On suppose que le noeud avec le plus grand nombre d'occurences est la racine
    t_Noeud *noeud_max = index->racine;

    // On parcourt la pile
    while (!pile_vide(pile))
    {
        if (noeud_max->nb_occurences < depiler(pile)->nb_occurences)
        {
            // Si le nombre d'occurences du noeud actuel est plus petit que celui de la pile, on met à jour le noeud max
            noeud_max = depiler(pile);
        }
    }
    // On affiche le mot le plus fréquent
    afficher_noeud_max(noeud_max);
}


void construire_texte (t_Index *index, char *filename)
{
    if (index == NULL || filename == NULL)
    {
        printf("Erreur : index ou nom de fichier non initialise\n");
        return;
    }

    FILE * fichier = fopen(filename, "w");

    if (index->listeLigne == NULL) {
        printf("Erreur : liste de lignes non initialise\n");
        return;
    }

    // On parcourt la liste de lignes
    t_ListeLigne * listeLigneActuelle = index->listeLigne;

    while (listeLigneActuelle != NULL)
    {
        // On ajoute la ligne au fichier texte
        fprintf(fichier, "%s", listeLigneActuelle->ligne);

        // On passe à la ligne suivante
        listeLigneActuelle = listeLigneActuelle->ligneSuivante;
    }

    // On ferme le fichier
    fclose(fichier);
}


void afficher_occurences_mot (t_Index * index, char *mot)
{
    // On recherche le mot dans l'index, si il n'est pas présent on affiche un message d'erreur sinon on affiche les occurences
    mise_en_min(mot);

    t_Noeud * noeud = rechercher_mot(index, mot);

    if (noeud == NULL)
    {
        printf("Le mot %s n'est pas dans l'index\n", mot);
    }
    else
    {
        printf("Mot = \"%s\"\nOccurences = %d\n", mot, noeud->nb_occurences);
        printf("Il apparait dans les phrases suivantes :\n");
        afficher_liste_positions_phrase(noeud->positions, index);
    }
}


/*********************         Fonctions de bases (avec modifications)         ****************************/



t_Index* creer_index (void)
{
    // Alloue et initialise un index
    t_Index *index = malloc(sizeof(t_Index));

    if (index != NULL)
    {
        index->nb_mots_differents = 0;
        index->nb_mots_total = 0;

        index->racine = NULL;
        index->listeLigne = NULL;
        index->listePhrases = NULL;
    }

    return index;
}


int indexer_fichier (t_Index *index, char *filename)
{
    if (index == NULL || filename == NULL)
    {
        return 0;
    }


    FILE* input_file = fopen(filename, "r");

    if (input_file == NULL)
    {
        // Si le fichier n'a pas pu être ouvert
        printf("Erreur: le fichier %s n'a pas pu etre ouvert\n", filename);
        return 0;
    }

    // Initialisation des variables
    char ligne[MAX_LIGNE];

    int num_ligne = 1;
    int ordre = 1;
    int num_phrase = 1;

    // Variables supplémentaires pour savoir si nous sommes en fin de phrase ou non et la taille d'un mot
    int fin_phrase = 0;
    int taille_mot;

    // Initialisation de la constante de séparation des mots
    const char * sep = " ";
    t_listePhrases *phrase_courante=NULL;

    // On compte le nombre de mots dans le fichier
    int nb_mots_fichier = 0;
    int premiere_ligne = 1;
    int premier_mot = 1;

    while(fgets(ligne, MAX_LIGNE, input_file) != NULL)
    {
        if (premiere_ligne)
        {
            index->listeLigne = creer_liste_ligne(ligne);
            premiere_ligne = 0;
        }
        else
        {
            if (ajouter_ligne(index, ligne) == 0)
            {
                printf("Erreur: impossible d'ajouter la ligne\n");
                return 0;
            }
        }
        mise_en_min(ligne);

        if (ligne[strlen(ligne) - 1] == '\n')
        {
            // On enlève le \n à la fin de la ligne
            ligne[strlen(ligne) - 1] = '\0';
        }

        if (ligne[strlen(ligne) - 1] == ' ')
        {
            // On enlève le dernier espace, s'il y en a un à la fin de la ligne
            ligne[strlen(ligne) - 1] = '\0';
        }

        ordre = 1;

        char *mot = strtok(ligne, sep);


        while(mot != NULL)
        {
            taille_mot = strlen(mot);

            if (mot[taille_mot-1] == '\n')
            {
                mot[taille_mot-1] = '\0';
                taille_mot--;
            }


            if (mot[taille_mot-1] == '.')
            {
                mot[taille_mot-1] = '\0';
                fin_phrase = 1;
            }


            t_Noeud *noeud = rechercher_mot(index, mot);

            if (noeud == NULL)
            {
                //  Si le mot n'est pas dans l'index
                noeud = malloc(sizeof (t_Noeud));
                t_ListePositions *liste_positions = creer_liste_positions();

                if (noeud == NULL || liste_positions == NULL)
                {
                    printf("Erreur: impossible d'allouer de la memoire\n");
                    return 0;
                }

                noeud->mot = malloc(sizeof(mot));
                strcpy(noeud->mot, mot);

                noeud->nb_occurences = 1;
                noeud->filsGauche = NULL;
                noeud->filsDroit = NULL;

                ajouter_position(liste_positions, num_ligne, ordre, num_phrase);

                noeud->positions = liste_positions;

                if (ajouter_noeud(index, noeud) == 0)
                {
                    printf("Erreur: impossible d'ajouter le noeud\n");
                    return 0;
                }

                index->nb_mots_total++;
                index->nb_mots_differents++;
            }
            else
            {
                // Si le mot est dans l'index on ajoute la position dans la liste des positions et on incrémente le nombre d'occurences
                noeud->nb_occurences++;
                ajouter_position(noeud->positions, num_ligne, ordre, num_phrase);
                index->nb_mots_total++;
            }

            if (premier_mot == 1)
            {
                phrase_courante = creer_liste_phrases(num_phrase);
                ajouter_mot(phrase_courante, mot);
                premier_mot = 0;
            }
            else
            {
                ajouter_mot(phrase_courante, mot);
            }

            if (fin_phrase == 1)
            {
                num_phrase++;
                ajouter_phrase(index, phrase_courante);
                fin_phrase = 0;
                premier_mot = 1;
            }
            nb_mots_fichier++;
            ordre++;
            mot = strtok(NULL, sep);

        }
        num_ligne++;
    }

    fclose(input_file);  // On ferme le fichier
    return nb_mots_fichier;
}



/*********************         Fonctions ajoutées         ****************************/



void mise_en_min (char *mot)
{
    int i;

    // On parcourt le mot à la recherche des lettres en majuscule et on les remplace par leur minuscule

    for (i = 0; i < strlen(mot); i++)
    {
        if (mot[i] >= 'A' && mot[i] <= 'Z')
        {
            mot[i] += 32;
        }
    }
}


char mise_en_maj (char letter)
{
    // On retourne la lettre en majuscule

    if ('a' <= letter && letter <= 'z')
    {
        letter -= 32;
    }

    return letter;
}


int max(int a, int b)
{
    // Retourne le plus grand entre deux nombres

    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}


void liberation_index (t_Index *index)
{
    if (index == NULL)
    {
        printf("Erreur : index deja vide\n");
        return;
    }

    // Liberation des listes de lignes et de phrases
    liberer_liste_ligne(index->listeLigne);
    liberer_phrase(index->listePhrases);

    // Liberation de l'arbre de l'index
    liberation_arbre(index->racine);

    // Liberation de l'index
    free(index);
}


void liberation_arbre (t_Noeud *noeud)
{
    if (noeud == NULL)
    {
        // Cas où le noeud est déjà NULL, cas limite
        return;
    }

    // Liberation des fils gauche et droit
    liberation_arbre(noeud->filsGauche);
    liberation_arbre(noeud->filsDroit);

    // Liberation de la liste de positions du noeud
    t_Position *position_actuelle = noeud->positions->debut;

    while(position_actuelle != NULL)
    {
        // On libère la position actuelle
        // On stocke de manière temporaire la position actuelle, on passe à la suivante, puis on libère la position actuelle

        t_Position * temp = position_actuelle;

        position_actuelle = position_actuelle->suivant;

        free(temp);
    }

    // On libère la position de début
    free(noeud->positions);

    // On libère le mot du noeud
    free(noeud->mot);

    // On libère le noeud
    free(noeud);
}


void liberer_phrase (t_listePhrases *liste)
{
    if (liste == NULL) {
        return;
    }

    // On libère la dernière phrase de la liste puis on passe à la phrase précédente (via la fonction recursive)
    liberer_phrase (liste->suivante);

    // On libère la phrase actuelle

    // Liberation de la liste des mots
    t_Liste_Mot *mot_actuel = liste->debut;

    while (mot_actuel != NULL)
    {

        // On libère le mot actuel
        // On stocke de manière temporaire le mot actuel, on passe au suivant, puis on libère le mot actuel

        t_Liste_Mot * temp = mot_actuel;

        mot_actuel = mot_actuel->suivant;

        free(temp);
    }

    // On libère la liste des mots
    free(liste);
}


void liberer_liste_ligne (t_ListeLigne *ligne)
{
    if (ligne == NULL)
    {
        return;
    }
    // On libère la dernière ligne de la liste puis on passe à la ligne précédente (via la fonction recursive)
    liberer_liste_ligne (ligne->ligneSuivante);

    // On libère la ligne actuelle
    free(ligne->ligne);
    free(ligne);
}


int hauteur(t_Noeud *noeud)
{
    if (noeud == NULL)
    {
        // Si le noeud est NULL, on retourne -1
        return -1;
    }
    else
    {
        // Sinon nous sommes à une feuille ou dans l'arbre
        // On retourne la hauteur maximale entre les deux fils

        int hauteurGauche = hauteur(noeud->filsGauche);
        int hauteurDroit = hauteur(noeud->filsDroit);

        return 1 + max(hauteurGauche, hauteurDroit);
    }
}


int equilibre(t_Noeud *noeud)
{
    if (noeud == NULL)
    {
        // Si le noeud est NULL, on retourne -1
        return -1;
    }
    else
    {
        // Sinon nous sommes à une feuille ou dans l'arbre
        // On retourne la différence entre la hauteur du fils gauche et le fils droit
        // Si elle est supérieure à 1, alors l'arbre est non-équilibré et nous retournons -2

        int hauteurGauche = equilibre(noeud->filsGauche);
        int hauteurDroit = equilibre(noeud->filsDroit);

        if (abs(hauteurDroit - hauteurGauche) > 1 || hauteurDroit == -2 || hauteurGauche == -2)
        {
            // On retourne -2 si l'arbre est non-équilibré
            return -2;
        }

        // On retourne la hauteur maximale entre les deux fils
        return 1 + max(hauteurGauche, hauteurDroit);
    }
}


void parcours_infixe (t_Noeud *noeud, char *first_letter)
{
    if (noeud == NULL)
    {
        // Cas où le noeud est NULL, cas limite, on ne fait rien
        return;
    }

    parcours_infixe(noeud->filsGauche, first_letter);

    // Si la première lettre du mot est différente de la lettre précédente, on affiche la lettre
    if (mise_en_maj(noeud->mot[0]) != *first_letter)
    {
        // On affiche la première lettre du mot en majuscule
        printf("\n%c\n", mise_en_maj(noeud->mot[0]));

        // On change en mémoire la valeur de la première lettre du mot
        *first_letter = mise_en_maj(noeud->mot[0]);
    }

    // On affiche le noeud
    afficher_noeud(noeud);

    parcours_infixe(noeud->filsDroit, first_letter);
}


void afficher_noeud (t_Noeud *noeud)
{
    if (noeud == NULL)
    {
        return;
    }
    // On met en majuscule la première lettre du mot
    noeud->mot[0] = mise_en_maj(noeud->mot[0]);

    printf("|-- %s\n", noeud->mot);

    // On remet en minuscule le mot
    mise_en_min(noeud->mot);

    // On affiche les positions
    afficher_liste_positions(noeud->positions);

    // On affiche un caractère pour séparer les mots
    printf("|\n");
}


void afficher_liste_positions(t_ListePositions *liste_positions)
{
    if (liste_positions == NULL)
    {
        // Cas où la liste est vide, cas limite, on ne fait rien
        return;
    }

    // Sinon on affiche la liste des positions

    // On initialise un pointeur sur la tête de la liste
    t_Position *position = liste_positions->debut;

    while (position != NULL)
    {
        // On affiche la position et on passe à la position suivante

        printf("|---- (l:%d, o:%d, p:%d)\n", position->numero_ligne, position->ordre, position->numero_phrase);
        position = position->suivant;
    }
}


void afficher_noeud_recherche (t_Noeud *noeud)
{
    if (noeud == NULL)
    {
        return;
    }

    // On affiche le mot du noeud, son nombre de positions et ses positions
    printf("Le mot %s apparait %d fois, aux positions :\n", noeud->mot, noeud->nb_occurences);

    printf("|\n");

    t_Position *position = noeud->positions->debut;

    while (position != NULL)
    {
        printf("|---- (l:%d, o:%d, p:%d)\n", position->numero_ligne, position->ordre, position->numero_phrase);
        position = position->suivant;
    }

    printf("|\n");
}


t_Noeud * rechercher_mot_insertion (t_Index *index, char *mot_recherche)
{
    // A la différence de la fonction rechercher_mot, cette fonction renvoie le noeud correspondant au mot ou au noeud parent de l'endroit où le mot doit être inséré

    if (index == NULL || mot_recherche == NULL)
    {
        printf("Erreur : index ou mot non initialise\n");
        return NULL;
    }

    // On met le mot recherche en minuscule
    mise_en_min(mot_recherche);

    // On initialise un pointeur sur la racine de l'arbre
    t_Noeud *noeud_actuel = index->racine;
    t_Noeud *pere = NULL;

    while (noeud_actuel != NULL)
    {
        pere = noeud_actuel;

        if (strcmp(noeud_actuel->mot, mot_recherche) < 0)
        {

            noeud_actuel = noeud_actuel->filsDroit;

        }
        else if (strcmp(noeud_actuel->mot, mot_recherche) > 0)
        {

            noeud_actuel = noeud_actuel->filsGauche;

        }
        else
        {
            // Le mot est déjà présent dans l'index
            return noeud_actuel;
        }
    }

    // On a trouvé le noeud parent où le mot doit être inséré
    return pere;
}


Pile* empiler_arbre (t_Index *index)
{
    // On crée une pile vide et on empile tous les noeuds de l'arbre à l'aide de la méthode infixe

    Pile *pile = creer_pile();

    if (pile == NULL) {
        printf("Erreur: impossible d'allouer de la memoire\n");
        return NULL;
    }

    empiler_infixe(pile, index->racine);

    return pile;
}


void empiler_infixe (Pile *pile, t_Noeud *noeud)
{
    // La pile est non null car testée dans la fonction qui l'appelle

    if (noeud == NULL)
    {
        // Cas où le noeud est non NULL, cas limite
        return;
    }

    // On parcourt l'arbre en infixe
    empiler_infixe(pile, noeud->filsGauche);
    // On empile le noeud actuel
    empiler(pile, noeud);
    empiler_infixe(pile, noeud->filsDroit);
}


Pile*  creer_pile (void)
{
    // On crée une pile vide, on alloue de la mémoire et on initialise les champs
    Pile *pile = malloc(sizeof (Pile));

    if (pile == NULL)
    {
        printf("Erreur: impossible d'allouer de la memoire\n");
    }
    else
    {
        pile->sommet = NULL;
        pile->taille = 0;
    }
    return pile;
}


Element* creer_element (t_Noeud *noeud)
{
    // On crée un élément, on alloue de la mémoire et on initialise les champs
    Element *element = malloc(sizeof (Element));

    if (element == NULL)
    {
        printf("Erreur: impossible d'allouer de la memoire\n");
    }
    else
    {
        element->noeud = noeud;
        element->suivant = NULL;
    }

    return element;
}


int pile_vide (Pile *pile)
{
    // On teste si la pile est vide
    return (pile->taille == 0);
}


void empiler (Pile *pile, t_Noeud *noeud)
{
    if (pile_vide(pile))
    {
        // Cas où la pile est vide, on crée un élément et on l'empile sur le sommet

        pile->sommet = creer_element(noeud);

    }
    else
    {
        // Cas où la pile n'est pas vide, on crée un élément, on le fait pointer vers l'ancien sommet et on l'empile sur le sommet

        Element *element = creer_element(noeud);

        element->suivant = pile->sommet;

        pile->sommet = element;
    }

    // On incrémente la taille de la pile
    pile->taille++;
}


t_Noeud* depiler (Pile *pile)
{
    // On retourne le sommet de la pile et on le dépile

    if (pile_vide(pile))
    {
        return NULL;
    }
    else
    {
        t_Noeud* noeud = pile->sommet->noeud;
        pile->sommet = pile->sommet->suivant;
        pile->taille--;

        return noeud;
    }
}


void afficher_noeud_max (t_Noeud *noeud)
{
    // On affiche le mot le plus fréquent
    if (noeud == NULL)
    {
        return;
    }
    printf("Mot avec le plus d'occurences: %s\n", noeud->mot);
    printf("Nombre d'occurences: %d\n", noeud->nb_occurences);
    printf("Liste des positions: \n");
    afficher_liste_positions(noeud->positions);
}


t_ListePhrases * creer_liste_phrases (int num)
{
    // On initialise la liste de phrases et on initialise les champs
    t_ListePhrases *liste = malloc(sizeof(t_ListePhrases));
    if (liste != NULL)
    {
        liste->num_phrase = num;
        liste->suivante = NULL;
        liste->debut = NULL;
    }

    return liste;
}


t_Liste_Mot * creer_liste_mot (char * premierMot)
{
    // On initialise la liste de mots et on initialise les champs
    t_Liste_Mot *liste = malloc(sizeof(t_Liste_Mot));

    if (liste != NULL)
    {
        liste->suivant = NULL;
        liste->mot = malloc(sizeof(char) * strlen(premierMot));
        if (liste->mot != NULL)
        {
            strcpy(liste->mot, premierMot);
        }
        else
        {
            liste = NULL;
        }
    }

    return liste;
}


void ajouter_mot(t_listePhrases* liste, char * mot)
{
    if (liste == NULL || mot == NULL)
    {
        printf("liste ou mot non initialise\n");
        return;
    }

    // Sinon on ajoute le mot à la fin de la liste
    t_Liste_Mot * nouveauMot = creer_liste_mot(mot);

    if (liste->debut == NULL)
    {
        // Si la liste est vide on ajoute le mot en tête
        liste->debut = nouveauMot;
    }
    else
    {
        // Sinon on ajoute le mot à la fin de la liste
        t_Liste_Mot * mot_actuel = liste->debut;
        while (mot_actuel->suivant != NULL)
        {
            mot_actuel = mot_actuel->suivant;
        }
        mot_actuel->suivant = nouveauMot;
    }
}


void ajouter_phrase (t_Index * index, t_ListePhrases * liste)
{
    if (index == NULL || liste == NULL)
    {
        printf("index ou liste non initialise\n");
        return;
    }

    // Sinon on ajoute la liste de mots à la fin de la liste de phrases
    if (index->listePhrases == NULL)
    {
        // Si la liste est vide on ajoute la liste en tête
        index->listePhrases = liste;
    }
    else
    {
        // Sinon on ajoute la liste à la fin de la liste de phrases
        t_ListePhrases * listePhrasesActuelle = index->listePhrases;
        while (listePhrasesActuelle->suivante != NULL)
        {
            listePhrasesActuelle = listePhrasesActuelle->suivante;
        }
        listePhrasesActuelle->suivante = liste;
    }
}


void afficher_liste_positions_phrase (t_ListePositions *liste_positions, t_Index *index)
{
    // On affiche la liste des positions de la phrase et les phrases qui y sont associées
    if (liste_positions == NULL)
    {
        printf("La liste de positions est vide\n");
        return;
    }

    // On affiche la liste des positions de la phrase
    t_Position * position = liste_positions->debut;

    while (position != NULL)
    {
        t_ListePhrases * listePhrases = index->listePhrases;
        while (listePhrases != NULL && listePhrases->num_phrase < position->numero_phrase)
        {
            listePhrases = listePhrases->suivante;
        }

        if (listePhrases != NULL)
        {
            printf("| Ligne %d, mot %d, phrase %d : ", position->numero_ligne, position->ordre, position->numero_phrase);
            affiche_phrase(listePhrases);
        }

        position = position->suivant;
    }
}


void affiche_phrase (t_ListePhrases *liste)
{
    // On affiche la phrase en itérant sur la liste des mots
    if (liste == NULL)
    {
        printf("La liste de phrases est vide\n");
        return;
    }

    t_Liste_Mot *mot_actuel = liste->debut;
    printf("\"");

    int premier_mot = 1;

    while (mot_actuel != NULL)
    {
        if (premier_mot)
        {
            // Si c'est le premier mot, on affiche la première lettre en majuscule
            mot_actuel->mot[0] = mise_en_maj(mot_actuel->mot[0]);
            printf("%s ", mot_actuel->mot);
            mise_en_min(mot_actuel->mot);

            premier_mot=0;
        }
        else
        {
            if (mot_actuel->suivant != NULL)
            {
                // En milieu de phrase, on affiche le mot en minuscule et on met un espace
                printf("%s ", mot_actuel->mot);
            }
            else
            {
                // En dernier mot, on affiche le mot en minuscule et on met un point
                printf("%s.", mot_actuel->mot);
            }
        }

        mot_actuel = mot_actuel->suivant;
    }
    printf("\"\n");
}


void affiche_liste_ligne(t_ListeLigne * listeLigne)
{
    if (listeLigne == NULL)
    {
        // Cas où la liste est vide, cas limite, on ne fait rien
        return;
    }

    printf("%s", listeLigne->ligne); // On affiche la ligne

    affiche_liste_ligne(listeLigne->ligneSuivante); // On rappelle la fonction pour afficher la liste suivante
}


int ajouter_ligne(t_Index * index, char * ligne)
{
    if (index == NULL || ligne == NULL)
    {
        printf("Erreur: impossible d'ajouter la ligne\n");
        return 0;
    }

    // On crée la liste de ligne et on l'ajoute à la fin de la liste
    t_ListeLigne * nouvelleLigne = malloc(sizeof(t_ListeLigne));

    if (nouvelleLigne == NULL)
    {
        return 0;
    }

    nouvelleLigne->ligneSuivante = NULL;

    nouvelleLigne->ligne = malloc(sizeof(char) * strlen(ligne));

    if (nouvelleLigne->ligne == NULL)
    {
        return 0;
    }
    strcpy(nouvelleLigne->ligne, ligne);


    if (index->listeLigne == NULL)
    {
        // Si la liste est vide
        index->listeLigne = nouvelleLigne;
    }
    else
    {
        // Sinon on ajoute la ligne à la fin de la liste
        t_ListeLigne * listeLigneActuelle = index->listeLigne;

        while (listeLigneActuelle->ligneSuivante != NULL)
        {
            listeLigneActuelle = listeLigneActuelle->ligneSuivante;
        }
        listeLigneActuelle->ligneSuivante = nouvelleLigne;
    }
    return 1;
}


t_ListeLigne * creer_liste_ligne (char * ligne)
{
    // On crée une liste de lignes et on l'initialise

    t_ListeLigne *liste = malloc(sizeof(t_ListeLigne));

    if (liste != NULL)
    {
        liste->ligneSuivante = NULL;
        liste->ligne = malloc(sizeof(char) * strlen(ligne));

        if (liste->ligne != NULL)
        {
            strcpy(liste->ligne, ligne);
        }
        else
        {
            liste = NULL;
        }
    }
    return liste;
}