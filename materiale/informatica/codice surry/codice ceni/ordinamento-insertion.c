#include <stdio.h>

void insertionSort(int L[], int n) {
    int i, j, chiave;

    for (i = 1; i < n; i++) {
        chiave = L[i];
        j = i - 1;

        while (j >= 0 && L[j] > chiave) {
            L[j + 1] = L[j];
            j--;
        }
        L[j + 1] = chiave;
    }
}

void stampa(int L[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", L[i]);
    }
    printf("\n");
}

int main(void) {
    int L[] = {8, 3, 5, 1, 9, 2, 6, 7, 4};
    int n = (int)(sizeof(L) / sizeof(L[0]));

    printf("Prima: ");
    stampa(L, n);

    insertionSort(L, n);

    printf("Dopo:  ");
    stampa(L, n);
    return 0;
}
