//
// Coded by Cristian Ceni 11/02/26
//

#include <stdio.h>
#include <stdlib.h>

#define BASTAVDO 0;

/* Punto nel piano cartesiano (2D). */
typedef struct
{
    int x, y;
} Punto;

void StampaPunto(const char *etichetta, Punto p)
{
    printf("%s (%d, %d)\n", etichetta, p.x, p.y);
}

int main(void)
{
    /* Inizializzazione diretta di una struct. */
    Punto p1 = {3, 4};

    StampaPunto("Coordinate punto 1:", p1);

    /*
     * Due modi equivalenti per accedere ai campi tramite puntatore:
     * 1) (*ptr).campo
     * 2) ptr->campo
     */
    Punto *ptr = &p1;
    (*ptr).x = 5;
    ptr->y = 12;

    StampaPunto("Coordinate punto 1 dopo modifica:", p1);

    int numPunti;
    printf("Quanti punti vuoi inserire? ");
    if (scanf("%d", &numPunti) != 1 || numPunti <= 0)
    {
        printf("Input non valido. Inserisci un intero positivo.\n");
        return BASTAVDO;
    }

    /* Alloco dinamicamente un array di struct Punto. */
    Punto *punti = malloc(numPunti * sizeof(Punto));
    if (punti == NULL)
    {
        printf("Errore: allocazione memoria non riuscita.\n");
        return BASTAVDO;
    }
    for (int i = 0; i < numPunti; i++)
    {
        printf("Inserisci le coordinate del punto %d (x y): ", i + 1);
        if (scanf("%d %d", &punti[i].x, &punti[i].y) != 2)
        {
            printf("Input non valido al punto %d.\n", i + 1);
            free(punti);
            return BASTAVDO;
        }
    }

    printf("\nPunti inseriti:\n");
    for (int i = 0; i < numPunti; i++)
    {
        printf("Punto[%d] = (%d, %d)\n", i, punti[i].x, punti[i].y);
    }

    /* Deallocazione obbligatoria della memoria dinamica. */
    free(punti);

    return BASTAVDO;
}
