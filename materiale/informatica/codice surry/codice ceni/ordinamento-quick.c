#include "ordinamento-lista.h"

static int partitiona(int *a, int low, int high) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            swap_int(&a[i], &a[j]);
        }
    }
    swap_int(&a[i + 1], &a[high]);
    return i + 1;
}

static void quick_sort_range(int *a, int low, int high) {
    if (low < high) {
        int p = partitiona(a, low, high);
        quick_sort_range(a, low, p - 1);
        quick_sort_range(a, p + 1, high);
    }
}

void quick_sort(Lista *l) {
    if (l->size <= 1) {
        return;
    }
    quick_sort_range(l->data, 0, l->size - 1);
}

int main(void) {
    int valori[] = {8, 3, 5, 1, 9, 2, 6, 7, 4};
    Lista l;

    copia_da_array(&l, valori, (int)(sizeof(valori) / sizeof(valori[0])));
    stampa_lista(&l, "Prima (quick): ");
    quick_sort(&l);
    stampa_lista(&l, "Dopo  (quick): ");

    return 0;
}
