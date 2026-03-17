//
// Coded by Cristian Ceni 10/02/26
//

#include <stdio.h>
#define BASTAVDO 0;

/* (a + b)^2 = a^2 + 2ab + b^2 */
int QuadratoBinomio(int a, int b)
{
    int res = (a * a) + (2 * a * b) + (b * b);
    return res;
}

/*
 * Somma pesata:
 * res = sum_{i=0}^{n-1} (a + b) * i
 */
int NonSaprei(int a, int b, int n)
{
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        res += (a + b) * i;
    }

    return res;
}

void StampaSezione(const char *titolo)
{
    printf("\n==================== %s ====================\n", titolo);
}

void StampaRisultato(const char *etichetta, int valore)
{
    printf("%-45s : %d\n", etichetta, valore);
}

int main(void)
{
    /* Valori di input di esempio */
    int a = 40;
    int b = 50;
    int c = 10;

    int res = QuadratoBinomio(a, b);
    int res2 = NonSaprei(a, b, c);

    StampaSezione("CHIAMATA DIRETTA ALLE FUNZIONI");
    StampaRisultato("Risultato quadrato di binomio", res);
    StampaRisultato("Risultato NonSaprei(a, b, c)", res2);

    StampaSezione("PUNTATORE A FUNZIONE");

    /* Puntatore a funzione con stessa firma di NonSaprei(int, int, int). */
    int (*puntatoreNiMuso)(int, int, int) = &NonSaprei;
    printf("%-45s : %p\n", "Indirizzo funzione NonSaprei", (void *)puntatoreNiMuso);

    int res3 = puntatoreNiMuso(a, b, c);
    int res4 = (*puntatoreNiMuso)(a, b, c);
    StampaRisultato("Chiamata tramite puntatore", res3);
    StampaRisultato("Chiamata con dereference esplicito", res4);

    /* Verifica finale: chiamata diretta e tramite puntatore danno lo stesso output. */
    int res5 = NonSaprei(a, b, c);
    StampaRisultato("Chiamata diretta di confronto", res5);

    StampaSezione("FINE");
    printf("Esecuzione completata.\n");

    return BASTAVDO;
}
