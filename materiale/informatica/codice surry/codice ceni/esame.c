//
// Coded by Cristian Ceni 15/02/2026
//

#include <stdio.h>
#include <stdlib.h>

// Definizione del record come da specifiche dell'esame
typedef struct Node {
    float val;
    struct Node *next;
} Node;

/**
 * Esercizio 5: Fonde LA e LB alternandone gli elementi.
 * Complessità: O(min(n, m)) - Spazio: O(1)
 */
Node* interleave(Node *LA, Node *LB) {
    // Se una delle due liste è nulla, restituisco l'altra (base case)
    if (LA == NULL) return LB;
    if (LB == NULL) return LA;

    // Puntatori di supporto per scorrere le liste senza perdere i riferimenti
    Node *currA = LA; // Puntatore al nodo corrente di LA
    Node *currB = LB; // Puntatore al nodo corrente di LB
    Node *nextA, *nextB; // Variabili temporanee per salvare i puntatori successivi

    // Iteriamo finché entrambe le liste hanno elementi disponibili
    while (currA != NULL && currB != NULL) {
        // Salviamo il riferimento al prossimo elemento di LA e LB prima di modificare i link
        nextA = currA->next;
        nextB = currB->next;

        // Effettuiamo il ricollegamento: il nodo di B deve seguire quello di A
        currA->next = currB;
        
        // Se A aveva un nodo successivo, inseriamo quel nodo dopo quello di B
        if (nextA != NULL) {
            currB->next = nextA;
        } else {
            // Se LA è terminata, attacchiamo il resto di LB in coda e interrompiamo
            currB->next = nextB;
            break; 
        }

        // Avanziamo i puntatori correnti ai nodi che avevamo salvato precedentemente
        currA = nextA;
        currB = nextB;
    }

    // Restituiamo la testa della lista LA, che ora contiene anche i nodi di LB
    return LA;
}

// Funzione di utilità per creare un nuovo nodo (per il test)
Node* crea_nodo(float v) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->val = v;
    n->next = NULL;
    return n;
}

// Funzione di utilità per stampare la lista
void stampa_lista(Node* h) {
    while (h) {
        printf("[%.1f] -> ", h->val);
        h = h->next;
    }
    printf("NULL\n");
}

int main() {
    // Simulazione Caso Esempio: LA={2,4,6,1}, LB={1,5,3,7,4,8}
    Node* LA = crea_nodo(2); LA->next = crea_nodo(4); LA->next->next = crea_nodo(6); LA->next->next->next = crea_nodo(1);
    Node* LB = crea_nodo(1); LB->next = crea_nodo(5); LB->next->next = crea_nodo(3); LB->next->next->next = crea_nodo(7); LB->next->next->next->next = crea_nodo(4); LB->next->next->next->next->next = crea_nodo(8);

    printf("Lista LA originale: "); stampa_lista(LA);
    printf("Lista LB originale: "); stampa_lista(LB);

    LA = interleave(LA, LB);

    printf("\nLista finale risultante: ");
    stampa_lista(LA);

    return 0;
}