#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x=0;

    printf("Entrez un entier :");
    scanf("%d", &x);

    if (x%2==0)
    {
        printf("Le nombre %d est pair",x);
    }
    else
    {
        printf("Le nombre %d est impair",x);
    }

    return 0;
}