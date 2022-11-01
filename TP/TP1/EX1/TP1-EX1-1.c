#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x=0, y=0;

    printf("Entrez la premiere valeur : ");
    scanf("%d", &x);

    printf("Entrez la seconde valeur : ");
    scanf("%d", &y);

    printf("\nLes valeurs sont 1:%d; 2:%d\nLeur somme est :%d\n", x, y, x+y);

    return 0;
}