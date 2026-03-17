//
// Coded by Cristian Ceni 11/02/26
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Serve per sqrt (radice quadrata)

#define BASTAVDO 0;

/*
 * typedef:
 * crea un alias di tipo. In questo modo evitiamo di scrivere ogni volta
 * "struct ...", e il codice resta piu leggibile.
 */
typedef struct
{
    int x, y, z;
} Vettore;

Vettore vettore1, vettore2, vettore3;

/*
 * Modulo euclideo di un vettore in R^3: ||v|| = sqrt(x^2 + y^2 + z^2).
 * La funzione restituisce int per coerenza con il resto del programma:
 * la parte decimale viene troncata.
 */
int modulo(Vettore v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

/*
 * Tre vettori in R^3 sono linearmente indipendenti se il determinante
 * della matrice 3x3 (con i vettori come righe/colonne) e diverso da zero.
 */
int linearmenteIndipendenti(Vettore v1, Vettore v2, Vettore v3)
{
    // Formula esplicita del determinante 3x3.
    int det = v1.x * (v2.y * v3.z - v2.z * v3.y) - v1.y * (v2.x * v3.z - v2.z * v3.x) + v1.z * (v2.x * v3.y - v2.y * v3.x);
    return det != 0;
}

/* Ritorna 1 se il vettore e nullo, altrimenti 0. */
int vettoreNullo(Vettore v)
{
    return v.x == 0 && v.y == 0 && v.z == 0;
}

/*
 * Se a x b != 0, allora a e b non sono paralleli e quindi sono
 * linearmente indipendenti come coppia.
 */
int prodottoVettorialeNonNullo(Vettore a, Vettore b)
{
    int cx = a.y * b.z - a.z * b.y;
    int cy = a.z * b.x - a.x * b.z;
    int cz = a.x * b.y - a.y * b.x;
    return cx != 0 || cy != 0 || cz != 0;
}

/*
 * Dimensione dello spazio generato = rango dell'insieme {v1, v2, v3}.
 * Possibili valori: 0, 1, 2, 3.
 */
int dimensioneSpazioGenerato(Vettore v1, Vettore v2, Vettore v3)
{
    // Rango 3: tutti e tre indipendenti (determinante diverso da zero).
    if (linearmenteIndipendenti(v1, v2, v3))
    {
        return 3;
    }

    // Rango 2: esiste almeno una coppia di vettori indipendenti.
    if (prodottoVettorialeNonNullo(v1, v2) ||
        prodottoVettorialeNonNullo(v1, v3) ||
        prodottoVettorialeNonNullo(v2, v3))
    {
        return 2;
    }

    // Rango 1: tutti i vettori sono multipli tra loro ma almeno uno e' non nullo.
    if (!vettoreNullo(v1) || !vettoreNullo(v2) || !vettoreNullo(v3))
    {
        return 1;
    }

    // Rango 0: tutti i vettori nulli.
    return 0;
}

int main(void)
{
    /* Inizializzazione dei tre vettori di esempio. */
    vettore1.x = 1;
    vettore1.y = 0;
    vettore1.z = 1;

    vettore2.x = 1;
    vettore2.y = 0;
    vettore2.z = 1;

    vettore3.x = 0;
    vettore3.y = 1;
    vettore3.z = 0;

    // Modulo (lunghezza) di ciascun vettore.
    printf("Modulo del vettore 1: %d\n", modulo(vettore1));
    printf("Modulo del vettore 2: %d\n", modulo(vettore2));
    printf("Modulo del vettore 3: %d\n", modulo(vettore3));

    // Test di indipendenza lineare dell'intera terna.
    if (linearmenteIndipendenti(vettore1, vettore2, vettore3))
    {
        printf("I vettori sono linearmente indipendenti\n");
    }
    else
    {
        printf("I vettori sono linearmente dipendenti\n");
    }

    // Dimensione del sottospazio generato dai tre vettori (rango).
    int dimensione = dimensioneSpazioGenerato(vettore1, vettore2, vettore3);

    if (dimensione == 3)
    {
        printf("I vettori generano tutto lo spazio e sono di dimensione %d\n", dimensione);
    }
    else
    {
        printf("I vettori generano uno spazio di dimensione %d\n", dimensione);
    }

    return BASTAVDO;
}
