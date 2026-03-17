#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

void mergesort_r( int * V, int N, int * tmp );
void mergesort( int * V, int N );
void merge( int * V, int N, int N1, int * tmp );
boolean binary_search_r(int * V, int N, int target);
boolean binary_search(int * V, int N, int target);

int main( int argc, char *argv[] )
{
    int N;
    int count, target;
    int * V;

    // lettura della lunghezza del vettore
    printf( "inserisci dimensione del vettore ==> " );
    scanf( "%d", &N );

    // allocazione del vettore da ordinare e del vettore delle permutazioni degli indici
    V = (int *) malloc( sizeof(int) * N );
    // lettura degli elementi del vettore
    for ( count = 0; count < N; count++ ) {
        printf( "inserisci elemento %d ==> ", count);
        scanf( "%d", &V[count] );
    }

    // chiamata della funzione di ordinamento
    mergesort( V, N );

    // stampa vettore ordinato
    printf( "\nvettore ordinato: " );
    for ( count = 0; count < N; count ++ ) {
        printf( "%d ", V[count] );
    }
    printf("\n");

    printf( "\ninserisci valore target => ");
    scanf("%d",&target);

    // applica la ricerca sull'array ordinato
    // change here to switch between recursive and iterative
    // binary search solution
    if ( binary_search_r(V, N, target) )
    //if ( binary_search(V, N, target) )
        printf("\ntarget found! end with success");
    else
        printf("\ntarget not found! end without success");
    printf("\n\n");

    return 0;
}

boolean binary_search_r(int * V, int N, int target) {
    if (N > 0) {
        if ( V[N/2]==target )
            return TRUE;
        else {
            if ( V[N/2] > target )
                // search on the left array
                return binary_search_r(V,N/2,target);
            else
                // search on the right array
                return binary_search_r(&V[N/2+1],N-N/2-1,target);
        }
    }
    else
        return FALSE;
}

boolean binary_search(int * V, int N, int target) {
    int length, first;
    boolean found = FALSE;

    first = 0;
    length = N;
    while ( length > 0 && found == FALSE ) {
        if ( V[first+length/2] == target )
            found = TRUE;
        else {
            if ( V[first+length/2] > target )
                // search on the left array
                length = length/2;
            else {
                first = first + length/2 + 1;
                length = length - length/2 - 1;
            }
        }
    }
    return found;
}

/* funzione di facciata per la chiamata della funzione ricorsiva mergesort_r.
   Alloca e rilascia il vettore di appoggio usato per la fusione
*/
void mergesort( int * V, int N )
{
    int * tmp;
    tmp = (int *) malloc( sizeof(int) * N );
    mergesort_r( V, N, tmp );
    free( tmp );
}

/* ordina il vettore V applicando l'algoritmo mergesort.
   Il vettore tmp e' usato dalle diverse istanze
*/
void mergesort_r( int * V, int N, int * tmp )
{
    if ( N > 1 ) {
        mergesort_r( V, N/2, tmp );
        mergesort_r( &V[N/2], N-N/2, &tmp[N/2] );
        merge( V, N, N/2, tmp );
    }
}

/* esegue la fusione dei due semivettori di V di lunghezza N1 e N-N1
*/
void merge( int * V, int N, int N1, int * tmp )
{
    int l, r, count;

    //  copia il semivettore sinistro sul vettore di appoggio
    for ( count = 0; count < N1; count ++ )
        tmp[count] = V[count];

    l = 0;
    r = 0;
    while ( l < N1 && r < N-N1 ) {
        if ( tmp[l] < V[N1+r] ) {
            V[l+r] = tmp[l];
            l++;
        }
        else {
            V[l+r] = V[N1+r];
            r++;
        }
    }

    while ( l < N1 ) {
        V[l+r] = tmp[l];
        l++;
    }
}
