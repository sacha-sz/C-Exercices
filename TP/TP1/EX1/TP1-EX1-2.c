#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x=0, y=0, temp=0;

    printf("Entrez la premiere valeur :");
    scanf("%d",&x);

    printf("\nEntrez la seconde valeur :");
    scanf("%d",&y);

    temp = x;
    x = y;
    y = temp;

    printf("\nLes deux valeurs sont maintenant: x=%d et y=%d\n", x, y);

    return 0;
}