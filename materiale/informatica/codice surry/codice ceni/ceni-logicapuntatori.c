//
// Coded by Cristian Ceni 10/02/26
//

#include <stdio.h>
#define BASTAVDO 0;

int a, b;     /* Due interi di esempio. */
int *pa, *pb; /* Puntatori che conterranno gli indirizzi di a e b. */

void StampaStato(const char *etichetta, int valore, const int *indirizzo)
{
    printf("%-20s valore = %-3d indirizzo = %p\n", etichetta, valore, (void *)indirizzo);
}

int main(void)
{
    a = 10;
    b = 20;

    /* I puntatori ora puntano alle variabili reali. */
    pa = &a;
    pb = &b;

    printf("\n=== STATO INIZIALE ===\n");
    StampaStato("Variabile a", a, pa);
    StampaStato("Variabile b", b, pb);

    /* Modifica indiretta: scrivo nei valori tramite dereferenziazione. */
    *pa = 30;
    *pb = 40;

    printf("\n=== DOPO MODIFICA TRAMITE PUNTATORI ===\n");
    StampaStato("Variabile a", a, pa);
    StampaStato("Variabile b", b, pb);

    printf("\n=== VERIFICA ===\n");
    printf("a = %d, *pa = %d\n", a, *pa);
    printf("b = %d, *pb = %d\n", b, *pb);

    printf("Ottimo e abbondante.");

    return BASTAVDO;
}
