#include <stdio.h>
#include <stdlib.h>

int main () {
    // Faire le calcul de multiplication d'une matrice (M lignes, L colonnes) par une matrice(L, N) : résultat (M,N).

    // Déclaration des variables
    int M, L, N;

    // Saisie des valeurs
    printf("Saisir M : ");
    scanf("%d", &M);
    printf("Saisir L : ");
    scanf("%d", &L);
    printf("Saisir N : ");
    scanf("%d", &N);

    // Déclaration des tableaux
    int tab1[M][L];
    int tab2[L][N];

    // Remplissage du tableau 1 avec des valeurs aléatoires
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < L; j++) {
            tab1[i][j] = rand() % 10;
        }
    }

    // Remplissage du tableau 2 avec des valeurs aléatoires
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < N; j++) {
            tab2[i][j] = rand() % 10;
        }
    }

    // Affichage du tableau 1
    printf("Tableau 1 : \n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < L; j++) {
            printf("%d ", tab1[i][j]);
        }
        printf("\n");
    }

    // Affichage du tableau 2
    printf("Tableau 2 : \n");
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", tab2[i][j]);
        }
        printf("\n");
    }

    // Calcul de la multiplication des deux tableaux
    int tab3[M][N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            tab3[i][j] = 0;
            for (int k = 0; k < L; k++) {
                tab3[i][j] += tab1[i][k] * tab2[k][j];
            }
        }
    }

    // Affichage du tableau 3
    printf("Tableau 3 : \n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", tab3[i][j]);
        }
        printf("\n");
    }
}