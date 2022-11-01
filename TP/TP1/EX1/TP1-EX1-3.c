#include <stdio.h>
#include <stdlib.h>

int main()
{
    float x=0, y=0, pourcentage=0;

    printf("Entrez la valeur de x :");
    scanf("%f",&x);

    printf("Entrez la valeur de y:");
    scanf("%f",&y);

    pourcentage = x/y*100;

    printf("Le pourcentage est de :%f%\n", pourcentage);

    return 0;
}