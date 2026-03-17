//
// Coded by Cristian Ceni 10/02/26
//

#include <stdio.h>
#include <stdlib.h>

#define BASTAVDO 0;

// Dichiaro il Nodo della lista, con un intero e un puntatore al nodo
// successivo, questa sarà una lista concatenata, in cui ogni nodo punta al successivo,
// e l'ultimo nodo punta a NULL, per indicare la fine della lista
struct Nodo
{
    int valoreNodo;
    struct Nodo *nodoSuccessivo;
};

void StampaLista(const struct Nodo *testaLista)
{
    const struct Nodo *nodoCorrente = testaLista;
    int indice = 0;

    printf("\n=== LISTA CONCATENATA ===\n");
    while (nodoCorrente != NULL)
    {
        printf("Nodo[%d] -> valore: %d\n", indice, nodoCorrente->valoreNodo);
        nodoCorrente = nodoCorrente->nodoSuccessivo;
        indice++;
    }
}

int main(void)
{
    struct Nodo *testaLista = NULL;
    struct Nodo *nodo1 = NULL;
    struct Nodo *nodo2 = NULL;

    /* Alloco dinamicamente i due nodi della lista. */
    nodo1 = malloc(sizeof(struct Nodo));
    nodo2 = malloc(sizeof(struct Nodo));
    if (nodo1 == NULL || nodo2 == NULL)
    {
        printf("Errore: allocazione memoria non riuscita.\n");
        free(nodo1);
        free(nodo2);
        return BASTAVDO;
    }

    /* Collego i nodi: testa -> nodo1 -> nodo2 -> NULL. */
    testaLista = nodo1;
    nodo1->valoreNodo = 10;
    nodo1->nodoSuccessivo = nodo2;
    nodo2->valoreNodo = 20;
    nodo2->nodoSuccessivo = NULL;

    StampaLista(testaLista);

    /* Libero la memoria allocata dinamicamente. */
    free(nodo1);
    free(nodo2);

    return BASTAVDO;
}
