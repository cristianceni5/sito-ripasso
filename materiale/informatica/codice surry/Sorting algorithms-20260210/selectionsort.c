#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

void swap( int * V, int n1, int n2 );
void selectionsort( int * V, int N, int * Perm );

int main(int argc, char *argv[])
{
  int N;
  int count;
  int * V, * Perm;
  
  // lettura della lunghezza del vettore
  printf( "inserisci dimensione del vettore ==> " );
  scanf( "%d", &N );
  
  // allocazione del vettore da ordinare e del vettore delle permutazioni degli indici
  V = (int *) malloc( sizeof(int) * N );
  Perm = (int *) malloc( sizeof(int) * N );
  
  // lettura degli elementi del vettore
  for ( count = 0; count < N; count++ ) {
      printf( "inserisci elemento %d ==> ", count);
      scanf( "%d", &V[count] );
  }
  
  // stampa del vettore
  printf( "\nvettore: " );
  for( count = 0; count < N; count ++ ) {
       printf( "%d ", V[count] );
  }
  printf("\n");

  // chiamata della funzione di ordinamento
  selectionsort( V, N, Perm );
  
  // stampa vettore ordinato
  printf( "\nvettore ordinato: " );
  for ( count = 0; count < N; count ++ ) {
      printf( "%d ", V[Perm[count]] );
  }
  printf("\n\n");
  
  system( "PAUSE" );	
  return 0;
}

/* ordina con algoritmo selectionsort
*/
void selectionsort( int * V, int N, int * Perm )
{
    int iter, count, count_of_max;

    for ( count=0; count<N; count++ )
        Perm[count] = count;
  
    for ( iter=0; iter<N-1; iter++ ) {
        for (count=1, count_of_max=0; count<N-iter; count++) {
            if (V[Perm[count]] > V[Perm[count_of_max]])
                count_of_max = count;
        }
        swap(Perm,count_of_max,N-iter-1);
    }
}

/* esegue swap tra due elementi di un vettore
*/
void swap( int * V, int n1, int n2 )
{
  int tmp;
   
  tmp = V[n1];
  V[n1] = V[n2];
  V[n2] = tmp;
}
