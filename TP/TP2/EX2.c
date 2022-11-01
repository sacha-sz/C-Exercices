#include <stdio.h>
#include <stdlib.h>

#define NMAX 100
#define motMax 60
#define nbMax 20

struct Un_tableau_Entier
{
    int tab[NMAX];
    int ncase = 0;
};

struct Menu {
    char nom[motMax][nbMax];
    int n;
};

enum contenant = {vin, vinaigre, biere, huile};

typedef struct tonneau
{
    float d;
    float D;
    float L;
    contenant c;
}Tonneau;

double calcul_volume_val(Tonneau t)
{
    // En utilisant un passage par valeur
    return (3.14 * (t.D/2) * (t.D/2) * t.L);
}

double calcul_volume_ref(Tonneau *t)
{
    // En utilisant un passage par référence
    return (3.14 * ((*t).D/2) * ((*t).D/2) * (*t).L);
}

