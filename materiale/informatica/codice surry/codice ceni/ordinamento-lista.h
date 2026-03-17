#ifndef ORDINAMENTO_LISTA_H
#define ORDINAMENTO_LISTA_H

#include <stdio.h>

#define LISTA_MAX 128

typedef struct {
    int data[LISTA_MAX];
    int size;
} Lista;

static inline void init_lista(Lista *l) {
    l->size = 0;
}

static inline int append_lista(Lista *l, int valore) {
    if (l->size >= LISTA_MAX) {
        return 0;
    }
    l->data[l->size] = valore;
    l->size++;
    return 1;
}

static inline void copia_da_array(Lista *l, const int *src, int n) {
    init_lista(l);
    for (int i = 0; i < n; i++) {
        if (!append_lista(l, src[i])) {
            break;
        }
    }
}

static inline void swap_int(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline void stampa_lista(const Lista *l, const char *titolo) {
    printf("%s", titolo);
    for (int i = 0; i < l->size; i++) {
        printf("%d", l->data[i]);
        if (i + 1 < l->size) {
            printf(" ");
        }
    }
    printf("\n");
}

#endif
