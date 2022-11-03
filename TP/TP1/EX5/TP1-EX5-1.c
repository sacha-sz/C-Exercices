#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    char *phrase = "Bonjour tout le monde. Bonsoir tout le monde.";
    char *prefixe = "Bon";

    int nb_prefixe = 0;
    int list_position[strlen(phrase)];

    // Ecrire un programme C qui détermine le nombre etla position d'une sous-chaîne dans une chaîne.

    for (size_t i=0, j=0; i<strlen(phrase); i++) {
        if (phrase[i] == prefixe[0]) {
            for (j = 0; j < strlen(prefixe); j++) {
                if (phrase[i + j] != prefixe[j]) {
                    break;
                }
            }
            if (j == strlen(prefixe)) {
                printf("Le préfixe %s est présent à la position %d\n", prefixe, i);
                list_position[nb_prefixe] = i;
                nb_prefixe++;
            }
            i += j;
        }
    }

    printf("Le préfixe \"%s\" est présent %d fois dans la phrase :\"%s\"\n", prefixe, nb_prefixe, phrase);
    printf("Les positions sont : ");
    for (size_t i=0; i<nb_prefixe; i++) {
        printf("%d ", list_position[i]);
    }

    return 0;
}