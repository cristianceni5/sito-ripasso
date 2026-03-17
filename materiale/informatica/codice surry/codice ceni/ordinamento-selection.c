#include <stdio.h>

void selectionSort(int L[], int n) {
    int i, j, min, temp;

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (L[j] < L[min]) {
                min = j;
            }
        }
        if (min != i) {
            temp = L[i];
            L[i] = L[min];
            L[min] = temp;
        }
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

    selectionSort(L, n);

    printf("Dopo:  ");
    stampa(L, n);
    return 0;
}
