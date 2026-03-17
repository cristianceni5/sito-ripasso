//
// Coded by Cristian Ceni 11/02/2026
//

// Includo le librerie per funzioni necessarie
#include <stdio.h>
#include <stdlib.h>

#define INVERTITA 1
#define FALLITA 0

// Dichiaro la lista sequenziale
typedef struct
{
    int *array;   // Puntatore all'array che conterrà gli elementi della lista
    int size;     // Numero di elementi attualmente nella lista
    int capacity; // Capacità massima dell'array
} ListaSequenziale;

int riempiLista(ListaSequenziale *lista)
{
    lista->array = (int *)malloc(7 * sizeof(int));
    if (lista->array == NULL)
    {
        lista->size = 0;
        lista->capacity = 0;
        return FALLITA;
    }

    lista->size = 0;
    lista->capacity = 7;

    lista->array[0] = 3;
    lista->array[1] = 8;
    lista->array[2] = 5;
    lista->array[3] = 6;
    lista->array[4] = 7;
    lista->array[5] = 9;
    lista->array[6] = 2;

    lista->size = 7;
    return INVERTITA;
}

int swapTuttiElementiLista(ListaSequenziale *lista)
{
    if (lista == NULL || lista->array == NULL || lista->size < 0 || lista->size > lista->capacity)
    {
        return FALLITA;
    }

    for (int i = 0; i < lista->size / 2; i++)
    {
        int temp = lista->array[i];
        lista->array[i] = lista->array[lista->size - 1 - i];
        lista->array[lista->size - 1 - i] = temp;
    }

    return INVERTITA;
}

int main(void)
{
    ListaSequenziale lista;
    if (riempiLista(&lista) == FALLITA)
    {
        fprintf(stderr, "Errore: allocazione memoria fallita.\n");
        return 1;
    }

    printf("Lista originale: ");
    for (int i = 0; i < lista.size; i++)
    {
        printf("%d ", lista.array[i]);
    }
    int esito = swapTuttiElementiLista(&lista);

    if (esito == INVERTITA)
    {
        // Stampa la lista invertita
        printf("Lista invertita: ");
        for (int i = 0; i < lista.size; i++)
        {
            printf("%d ", lista.array[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Si è verificato un errore durante l'inversione della lista.\n");
    }

    // Libera la memoria allocata per l'array
    free(lista.array);

    return 0;
}
