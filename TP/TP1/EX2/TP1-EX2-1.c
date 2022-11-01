#include <stdio.h>
#include <stdlib.h>

int main()
{
    char car;

    printf("Entez un caractere:");
    scanf("%c", &car);

    if (car>=97 && car<=122){
        printf("Caractere compris entre a et z. Caractere en minuscule.");
    };

    if (car>=65 && car<=90){
        printf("Caractere compris entre A et Z. Caractere en majuscule.");
    };

    if (car>=48 && car<=57){
        printf("Caractere compris entre 0 et 9. C'est un chiffre.");
    };

    return 0;
}

