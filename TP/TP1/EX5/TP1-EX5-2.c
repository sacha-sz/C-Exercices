#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void min_to_maj(char * mot); // Convertit un mot en majuscule
void min_to_maj_2(char * mot); // Convertit un mot en majuscule

int main () {
    char phrase [] = "Bonjour tout le monde ! Comment allez-vous ?";

    // Afficher la phrase
    printf("La phrase est initialement:\n\"%s\"\n", phrase);

    // Convertir la phrase en majuscule

    min_to_maj(phrase);
    min_to_maj_2(phrase);

    // Afficher la phrase
    printf("\nLa phrase est maintenant:\n\"%s\"\n", phrase);
}

void min_to_maj(char * mot)
{
    // For donc taille de mot connue avec strlen
    for (size_t i=0; i<strlen(mot); i++) {
        if (mot[i] >= 'a' && mot[i] <= 'z') {
            mot[i] -= 32;
        }
    }
}

void min_to_maj_2 (char * mot) {
    // While donc taille de mot inconnue
    while (*mot != '\0') {
        if (*mot >= 'a' && *mot <= 'z') {
            *mot -= 32;
        }
        mot++;
    }
}