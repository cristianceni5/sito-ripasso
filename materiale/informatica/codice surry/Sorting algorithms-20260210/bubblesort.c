#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

void swap( int * V, int n1, int n2 );
void bubblesort( int * V, int N, int * Perm );

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
  bubblesort( V, N, Perm );
  
  // stampa vettore ordinato
  printf( "\nvettore ordinato: " );
  for ( count = 0; count < N; count ++ ) {
      printf( "%d ", V[Perm[count]] );
  }
  printf("\n\n");
  
  system( "PAUSE" );	
  return 0;
}

/* ordina con algoritmo bubblesort
*/
void bubblesort( int * V, int N, int * Perm )
{
  int iter, count;
  boolean swap_found;
  
  for ( count=0; count<N; count++ )
     Perm[count] = count;
  
  iter = 0;
  do {
      for (count=0, swap_found=FALSE; count<N-iter-1; count++) {
          if ( V[Perm[count]] > V[Perm[count+1]] ) {
              swap(Perm, count, count+1);
              swap_found = TRUE;
          }
      }
      iter ++;
  } while( swap_found == TRUE );
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
