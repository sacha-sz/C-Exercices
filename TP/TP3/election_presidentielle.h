#ifndef TP3_NF16_ELECTION_PRESIDENTIELLE_H
#define TP3_NF16_ELECTION_PRESIDENTIELLE_H

typedef struct electeur {
    char *nom;
    long cin_num;
    int choix;
    struct electeur *suivant;
} electeur;

typedef electeur * T_Electeur;

T_Electeur creationelecteur(void);
T_Electeur fusionlistes(T_Electeur *liste_gauche, T_Electeur liste_droite);

void afficheliste(T_Electeur liste_electeur);
void ajoutelecteur(T_Electeur *liste, char nom[], long cin, int vote);
void triliste(T_Electeur *liste);
void supprime_electeur(T_Electeur *liste, long cin);
void decoupeliste(T_Electeur liste, T_Electeur *liste_gauche, T_Electeur *liste_droite, T_Electeur *liste_blanc);
void libereliste (T_Electeur liste);
void supprime_dernier_elec (T_Electeur *liste);

int compteGD(T_Electeur liste);
int compte_electeur (T_Electeur *liste);
int trouve_electeur(T_Electeur *liste, long cin);


#endif //TP3_NF16_ELECTION_PRESIDENTIELLE_H
