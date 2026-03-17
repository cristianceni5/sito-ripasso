//
// Coded by Cristian Ceni 11/02/26
//

#include <stdio.h>
#include <stdlib.h>

#define BASTAVDO 0;

/* Array statico: la sua dimensione e nota a compile-time. */
int arrayFisso[5] = {0, 1, 2, 3, 4};

void StampaErroreMemoria(const char *tipoAllocazione)
{
    printf("Errore: allocazione memoria non riuscita (%s).\n", tipoAllocazione);
}

void StampaSezione(const char *titolo)
{
    printf("\n==================== %s ====================\n", titolo);
}

/* Stampa ordinata: una riga per indice, cosi e facile leggere i valori. */
void StampaArray(const char *nome, const int *array, int dimensione)
{
    printf("%s (dimensione = %d)\n", nome, dimensione);
    printf("Indice | Valore\n");
    printf("-------+-------\n");
    for (int i = 0; i < dimensione; i++)
    {
        printf("%6d | %d\n", i, array[i]);
    }
}

int main(void)
{
    int dimArrayFisso = sizeof(arrayFisso) / sizeof(arrayFisso[0]);
    int dimArrayMalloc = 10;
    int dimArrayCalloc = 15;
    int dimArrayRealloc = 20;
    int *mallocArray = NULL;
    int *callocArray = NULL;
    int memoriaOk = 1;

    StampaSezione("ARRAY FISSO");
    printf("Dimensione dichiarata  : %d\n", 5);
    printf("Dimensione con sizeof  : %d\n", dimArrayFisso);
    StampaArray("Contenuto array fisso", arrayFisso, dimArrayFisso);

    StampaSezione("MALLOC");
    mallocArray = malloc(dimArrayMalloc * sizeof(int));
    if (mallocArray == NULL)
    {
        StampaErroreMemoria("malloc");
        memoriaOk = 0;
    }
    else
    {
        for (int i = 0; i < dimArrayMalloc; i++)
        {
            /* Riempio l'array con valori progressivi. */
            mallocArray[i] = i;
        }
        StampaArray("Array allocato con malloc", mallocArray, dimArrayMalloc);
    }

    StampaSezione("CALLOC");
    if (memoriaOk)
    {
        callocArray = calloc(dimArrayCalloc, sizeof(int));
        if (callocArray == NULL)
        {
            StampaErroreMemoria("calloc");
            memoriaOk = 0;
        }
    }
    if (memoriaOk)
    {
        for (int i = 0; i < dimArrayCalloc; i++)
        {
            /* Sostituisco gli zeri iniziali di calloc con un pattern semplice. */
            callocArray[i] = i * 3;
        }
        StampaArray("Array allocato con calloc", callocArray, dimArrayCalloc);
    }

    StampaSezione("REALLOC");
    if (memoriaOk)
    {
        /*
         * Uso un puntatore temporaneo: se realloc fallisce, mallocArray resta valido
         * e posso liberarlo senza perdere il riferimento.
         */
        int *temp = realloc(mallocArray, dimArrayRealloc * sizeof(int));
        if (temp == NULL)
        {
            StampaErroreMemoria("realloc");
            memoriaOk = 0;
        }
        else
        {
            mallocArray = temp;
        }
    }
    if (memoriaOk)
    {
        for (int i = 0; i < dimArrayRealloc; i++)
        {
            mallocArray[i] = i * 2;
        }
        StampaArray("Array dopo realloc (da 10 a 20)", mallocArray, dimArrayRealloc);
    }

    /* Rilascio tutta la memoria dinamica allocata. */
    free(mallocArray);
    free(callocArray);

    return BASTAVDO;
}
