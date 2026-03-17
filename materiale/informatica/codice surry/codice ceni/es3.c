#include <stdio.h>
#include <stdlib.h> // Necessaria per malloc() e free() nel main

// 1. Definizione della struttura dati per la lista sequenziale [cite: 43, 44, 46, 47, 48]
typedef struct {
    float *a;
    int size;
    int capacity;
} ListaSeq;

// 2. Funzione di mutazione di stato (Swap) tramite passaggio per riferimento
void swap(float *x, float *y) {
    float t = *x;
    *x = *y;
    *y = t;
}

// 3. Sub-routine principale per partizionamento e calcolo media
int mediaPartiz(ListaSeq *L, float *outMedia) {
    // Programmazione difensiva: controlli di validità dei puntatori e della dimensione logica
    if (L == NULL || outMedia == NULL) return 0;
    if (L->a == NULL) return 0; // Corretto l'errore fatale del 'return;' void
    if (L->size <= 0) return 0;

    double somma = 0.0;

    // Calcolo della media con accumulatore a doppia precisione
    for (int i = 0; i < L->size; i++) {
        somma += L->a[i];
    }
    
    // Esportazione del dato tramite dereferenziazione del parametro formale
    *outMedia = (float)(somma / (double)L->size);
    printf("[DEBUG] Media aritmetica calcolata e dereferenziata: %.2f\n", *outMedia);

    // Inizializzazione cursori per algoritmo di partizione in-place
    int k = 0;
    int j = L->size - 1;

    printf("[DEBUG] Inizio partizionamento logico (Hoare scheme). Cursori: k=%d, j=%d\n", k, j);

    while (k < j) {
        // Scansione progressiva: salta gli elementi già correttamente posizionati
        while (k < j && L->a[k] < *outMedia) { 
            k++; 
        }
        // Scansione regressiva: identifica elementi fuori posto
        while (k < j && L->a[j] >= *outMedia) { 
            j--; 
        }
        
        // Dislocamento fisico in memoria
        if (k < j) {
            printf("[DEBUG] Rilevata inversione rispetto alla media. Swap indirizzi: &L->a[%d] (%.1f) <-> &L->a[%d] (%.1f)\n", k, L->a[k], j, L->a[j]);
            swap(&L->a[k], &L->a[j]);
            k++;
            j--;
        }
    }
    
    return 1;
}

// 4. Entry point e iniezione del caso di test dell'esame
int main() {
    ListaSeq L;
    float mediaCalcolata = 0.0;
    
    // Dataset di test prelevato dalla traccia dell'esame 
    float test_data[] = {3.0, 8.0, 5.0, 6.0, 7.0, 9.0, 2.0};
    int num_elements = sizeof(test_data) / sizeof(test_data[0]);

    // Allocazione dinamica nello heap
    L.size = num_elements;
    L.capacity = num_elements;
    L.a = (float *)malloc(L.capacity * sizeof(float));
    
    if (L.a == NULL) {
        printf("[ERRORE] Allocazione di memoria fallita.\n");
        return -1;
    }

    // Popolamento della struttura
    for (int i = 0; i < L.size; i++) {
        L.a[i] = test_data[i];
    }

    // Ispezione pre-elaborazione
    printf("--- STATO INIZIALE ---\nL = { ");
    for (int i = 0; i < L.size; i++) printf("%.1f ", L.a[i]);
    printf("}\n\n");

    // Invocazione della subroutine
    if (mediaPartiz(&L, &mediaCalcolata)) {
        // Ispezione post-elaborazione
        printf("\n--- RISULTATO FINALE ---\nMedia restituita al main: %.2f\n", mediaCalcolata);
        printf("L_modificata = { ");
        for (int i = 0; i < L.size; i++) printf("%.1f ", L.a[i]);
        printf("}\n");
    } else {
        printf("\n[ERRORE] Elaborazione fallita. Controllare i parametri passati.\n");
    }

    // Prevenzione memory leak
    free(L.a);
    L.a = NULL;

    return 0;
}