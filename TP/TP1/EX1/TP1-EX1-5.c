#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x=0;

    printf("Entrez un entier :");
    scanf("%d", &x);

    printf("\n\nNos resultats :\n\toctal : %o\n\tdecimal: %d\n\thexadecimal:%x",x,x,x);

    return 0;
}