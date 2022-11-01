#include <stdio.h>
#include <stdlib.h>

int main()
{
    float temperature_C, temperature_F;

    printf("Entrez la valeur de la temperature en Fahrenheit :");
    scanf("%f",&temperature_F);

    temperature_C = (5.0/9.0) * (temperature_F - 32.0);

    printf("La temperature en Celsius est de :%f C\n", temperature_C);

    return 0;
}