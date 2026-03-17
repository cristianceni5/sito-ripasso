#include <stdio.h>

void bubbleSort(int L[], int n) {
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (L[j] > L[j + 1]) {
                temp = L[j];
                L[j] = L[j + 1];
                L[j + 1] = temp;
            }
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

    bubbleSort(L, n);

    printf("Dopo:  ");
    stampa(L, n);
    return 0;
}
