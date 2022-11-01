#ifndef TP4_NF16_TEXTE_H
#define TP4_NF16_TEXTE_H

/*******************************************************************************
 *                                                                             *
 *                            Structures de bases                              *
 *                                                                             *
 *******************************************************************************/

typedef struct t_position
{
    int numero_ligne;
    int ordre;
    int numero_phrase;

    struct t_position* suivant;

} t_position;

typedef t_position t_Position;

/*============================================================================*/

typedef struct t_listePositions
{
    int nb_elements;

    t_Position* debut;

} t_listePositions;

typedef t_listePositions t_ListePositions;

/*============================================================================*/

typedef struct t_noeud
{
    int nb_occurences;

    char* mot;

    t_listePositions * positions;

    struct t_noeud* filsGauche;
    struct t_noeud* filsDroit;

} t_noeud;

typedef t_noeud t_Noeud;



/*******************************************************************************
 *                                                                             *
 *                   Ajout des structures element et pile                      *
 *                                                                             *
 *******************************************************************************/

typedef struct element
{
    t_Noeud* noeud;

    struct element* suivant;

} element;

typedef element Element;

/*============================================================================*/

typedef struct pile
{
    int taille;

    Element* sommet;

} pile;

typedef pile Pile;



/*******************************************************************************
 *                                                                             *
 *      Ajout des structures t_listeLigne, t_liste_mot et t_listePhrases       *
 *     Pour gérer la réécriture dans un fichier et la gestion des phrases      *
 *                                                                             *
 *******************************************************************************/

typedef struct t_listeLigne
{
    char * ligne;

    struct t_listeLigne * ligneSuivante;

} t_listeLigne;

typedef t_listeLigne t_ListeLigne;

/*============================================================================*/

typedef struct t_liste_mot
{
    char *mot;

    struct t_liste_mot *suivant;

} t_liste_mot;

typedef t_liste_mot t_Liste_Mot;

/*============================================================================*/

typedef struct t_listePhrases
{
    t_Liste_Mot *debut;
    int num_phrase;
    struct t_listePhrases *suivante;
} t_listePhrases;

typedef t_listePhrases t_ListePhrases;




/*******************************************************************************
 *                                                                             *
 *               Modification de la structure de base de l'index               *
 *                       Ajout des lignes et des phrases                       *
 *                                                                             *
 *******************************************************************************/

typedef struct t_index
{
    struct t_noeud* racine;
    t_ListeLigne* listeLigne;
    t_ListePhrases * listePhrases;
    int nb_mots_differents;
    int nb_mots_total;
} t_index;

typedef t_index t_Index;


/*******************************************************************************
 *                                                                             *
 *                             Fonctions de base                               *
 *                            (sans modifications)                             *
 *                                                                             *
 *******************************************************************************/


t_ListePositions* creer_liste_positions (void);

/*============================================================================*/

int ajouter_position (t_ListePositions *listeP,int ligne, int ordre, int num_phrase);
int ajouter_noeud (t_Index *index, t_Noeud *noeud);

/*============================================================================*/

t_Noeud* rechercher_mot (t_Index *index, char *mot_recherche);

/*============================================================================*/

void afficher_index (t_Index *index);
void afficher_max_apparition(t_Index *index);
void construire_texte (t_Index *index, char *filename);
void afficher_occurences_mot (t_Index * index, char *mot);


/*******************************************************************************
 *                                                                             *
 *                             Fonctions de base                               *
 *                            (avec modifications)                             *
 *                                                                             *
 *******************************************************************************/


t_Index* creer_index (void);

/*============================================================================*/

int indexer_fichier (t_Index *index, char *filename);


/*******************************************************************************
 *                                                                             *
 *                             Fonctions ajoutées                              *
 *                                                                             *
 *******************************************************************************/


char mise_en_maj (char letter);

/*============================================================================*/

void mise_en_min (char *mot);
void liberation_index (t_Index *index);
void liberation_arbre (t_Noeud *noeud);
void liberer_phrase (t_listePhrases *liste);
void liberer_liste_ligne (t_ListeLigne *ligne);
void parcours_infixe (t_Noeud *noeud, char *first_letter);
void afficher_liste_positions(t_ListePositions *liste_positions);
void afficher_noeud (t_Noeud *noeud);
void empiler_infixe (Pile *pile, t_Noeud *noeud);
void empiler (Pile *pile, t_Noeud *noeud);
void afficher_noeud_max (t_Noeud *noeud);
void ajouter_mot(t_listePhrases* liste, char * mot);
void ajouter_phrase (t_Index * index, t_ListePhrases * liste);
void afficher_liste_positions_phrase (t_ListePositions *liste_positions, t_Index *index);
void affiche_phrase (t_ListePhrases *liste);
void affiche_liste_ligne(t_ListeLigne * listeLigne);
void afficher_noeud_recherche (t_Noeud *noeud);

/*============================================================================*/

int max(int a, int b);
int equilibre(t_Noeud *noeud);
int hauteur(t_Noeud *noeud);
int pile_vide (Pile *pile);
int ajouter_ligne(t_Index * index, char * ligne);

/*============================================================================*/

t_Noeud * rechercher_mot_insertion (t_Index *index, char *mot_recherche);
t_Noeud* depiler (Pile *pile);

/*============================================================================*/

Pile* empiler_arbre (t_Index *index);
Pile*  creer_pile (void);

/*============================================================================*/

Element* creer_element (t_Noeud *noeud);

/*============================================================================*/

t_ListePhrases * creer_liste_phrases (int num);

/*============================================================================*/

t_Liste_Mot * creer_liste_mot (char * premierMot);

/*============================================================================*/

t_ListeLigne * creer_liste_ligne (char * ligne);

#endif