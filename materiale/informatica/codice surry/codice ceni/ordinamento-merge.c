#include "ordinamento-lista.h"

static void merge(int *a, int left, int mid, int right, int *tmp) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = a[i++];
    }
    while (j <= right) {
        tmp[k++] = a[j++];
    }
    for (int t = left; t <= right; t++) {
        a[t] = tmp[t];
    }
}

static void merge_sort_range(int *a, int left, int right, int *tmp) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    merge_sort_range(a, left, mid, tmp);
    merge_sort_range(a, mid + 1, right, tmp);
    merge(a, left, mid, right, tmp);
}

void merge_sort(Lista *l) {
    int tmp[LISTA_MAX];
    if (l->size <= 1) {
        return;
    }
    merge_sort_range(l->data, 0, l->size - 1, tmp);
}

int main(void) {
    int valori[] = {8, 3, 5, 1, 9, 2, 6, 7, 4};
    Lista l;

    copia_da_array(&l, valori, (int)(sizeof(valori) / sizeof(valori[0])));
    stampa_lista(&l, "Prima (merge): ");
    merge_sort(&l);
    stampa_lista(&l, "Dopo  (merge): ");

    return 0;
}
