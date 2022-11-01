#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "time.h"

int fact1 (int nb);
int fact2 (int nb);
int fibo1 (int nb);
int fibo2(int n);

int main()
{
    int nb_fact =0;

    printf("Entrez votre nombre :\n");
    scanf("%d", &nb_fact);

    printf("Resultat avec fact1 : %d\n", fact1(nb_fact));
    printf("Resultat avec fact2 : %d\n", fact2(nb_fact));

    printf("Resultat avec fibo1 : %d\n", fibo1(nb_fact));
    printf("Resultat avec fibo2 : %d\n", fibo2(nb_fact));

    clock_t start, end;
    double elapsed;
    start = clock();
    printf("%ld\n",fibo2(nb_fact));
    end = clock();
    elapsed = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Premier temps:%f\n", elapsed);


    clock_t start_2, end_2;
    double elapsed_2;
    start_2 = clock();
    printf("%ld\n",fibo1(nb_fact));
    end_2 = clock();
    elapsed_2 = ((double)end_2 - start_2) / CLOCKS_PER_SEC;
    printf("Deuxieme temps :%f\n", elapsed_2);
    return 0;
}


int fact1 (int nb) {
    if (nb >= 0) {
        int factoriel_nb1 = 1;
        for (int compteur=2; compteur <= nb; compteur ++) {
            factoriel_nb1 *= compteur;
        }
        return factoriel_nb1;
    }
    return -1;
}


int fact2 (int nb) {
    if (nb >= 0) {
        if (nb <= 1){
            return 1;
        }
        return nb * fact2 (nb-1);
    }
    return -1;

}


int fibo1(int nb) {
    if (nb >= 0) {
        if (nb == 0 || nb == 1) {return nb;}
        else {
            return (fibo1(nb-1) + fibo1(nb-2));
        }
    }
    return -1;
}

int fibo2(int nb) {
    if (nb >= 0) {
        if (nb == 0 || nb == 1) {return nb;}
        else if (nb%2 != 0) {
            return pow(fibo2((nb-1)/2),2) + pow(fibo2((nb-1)/2 + 1),2);
        }
        else {
            return pow(fibo2(nb/2),2) + 2 * fibo2(nb/2 - 1) * fibo2(nb/2);
        }
    }
    return -1;
}