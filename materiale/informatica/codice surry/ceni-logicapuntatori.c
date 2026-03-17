//
// Coded by Cristian Ceni 10/02/26
//

#include <stdio.h>

int a, b;     // Dichiaro 2 interi
int *pa, *pb; // Dichiaro 2 puntatori ad interi

int main()
{
    a = 10; // Assegno 10 ad a
    b = 20; // Assegno 20 a b

    // Ora uso i puntatori e gli assegno l'indirizzo di a e b
    pa = &a;
    pb = &b;

    // Printiamo per vedere che succede
    printf("Il valore di a: %d - Il suo indirizzo: %p\n", a, pa);
    printf("Il valore di b: %d - Il suo indirizzo: %p\n", b, pb);

    // Modifico a e b tramite i puntatori
    *pa = 30; // Assegno 30 ad a tramite il puntatore
    *pb = 40; // Assegno 40 a b tramite il puntatore

    // Printiamo di nuovo per vedere i nuovi valori
    printf("Il nuovo valore di a: %d - Il suo indirizzo: %p\n", a, pa);
    printf("Il nuovo valore di b: %d - Il suo indirizzo: %p\n", b, pb);

    // Dimostro che a = *pa e b = *pb
    printf("a = %d, *pa = %d\n", a, *pa);
    printf("b = %d, *pb = %d\n", b, *pb);

    printf("Ottimo e abbondante.");

    return 0;
}

