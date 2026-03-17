# Guida Studio Dettagliata - Fondamenti C

Guida pensata per ripasso d'esame: ogni file e spiegato con logica, teoria, passaggi, output atteso e possibili domande.

## Indice
1. `ceni-logicapuntatori.c`
2. `ceni-liste.c`
3. `ceni-arraydinamici.c`
4. `ceni-puntatorifunzioni.c`
5. `ceni-struct.c`
6. `ceni-structpuntatori.c`
7. Teoria trasversale (che puo uscire all'esame)
8. Mini simulazione orale (domanda -> risposta)
9. Checklist finale
10. Teoria liste per l'esame (definizioni, costo, chiamate, side effects)

---

## 1) `ceni-logicapuntatori.c`

### Obiettivo reale del file
Capire cosa succede in memoria quando usi un puntatore per leggere e modificare una variabile.

### Passaggi del programma
1. Dichiara due interi globali `a` e `b` e due puntatori `pa` e `pb`.
2. In `main`, assegna `a = 10` e `b = 20`.
3. Salva gli indirizzi:
   - `pa = &a`
   - `pb = &b`
4. Stampa valore e indirizzo.
5. Modifica indiretta:
   - `*pa = 30`
   - `*pb = 40`
6. Verifica finale:
   - `a == *pa`
   - `b == *pb`

### Cosa devi sapere a memoria
- `a` e il valore.
- `&a` e l'indirizzo di `a`.
- `pa` contiene un indirizzo.
- `*pa` accede al valore memorizzato a quell'indirizzo.

### Errore tipico da evitare
Usare `*pa` prima di aver inizializzato `pa` con un indirizzo valido.

### Esempio output (semplificato)
```text
STATO INIZIALE: a=10, b=20
DOPO MODIFICA:  a=30, b=40
```

### Costo (tempo e spazio)
Nel codice attuale il numero di operazioni e fisso.
- Formula tempo: `T = c0 + c1` (costante).
- Complessita tempo: `Theta(1)`.
- Formula spazio extra: `S = c2` (solo poche variabili/puntatori).
- Complessita spazio: `Theta(1)`.

---

## 2) `ceni-liste.c`

### Obiettivo reale del file
Costruire manualmente una lista concatenata con due nodi e attraversarla.

### Struttura dati usata
```c
struct Nodo {
    int valoreNodo;
    struct Nodo *nodoSuccessivo;
};
```

### Passaggi del programma
1. Alloca due nodi in heap con `malloc`.
2. Se almeno un `malloc` fallisce, stampa errore e termina.
3. Collega i nodi:
   - `testaLista = nodo1`
   - `nodo1->nodoSuccessivo = nodo2`
   - `nodo2->nodoSuccessivo = NULL`
4. Scorre con `nodoCorrente` finche non trova `NULL`.
5. Stampa ogni `valoreNodo`.
6. Esegue `free(nodo1)` e `free(nodo2)`.

### Teoria fondamentale
- Lista concatenata: nodi non contigui in memoria.
- `NULL` segna la fine.
- Accesso al k-esimo nodo: lineare (`O(k)`).
- Inserimento in testa: costante (`O(1)`).

### Errore tipico da evitare
Dimenticare `free`: memory leak.

### Esempio output
```text
Nodo[0] -> valore: 10
Nodo[1] -> valore: 20
```

### Costo (tempo e spazio)
Sia `n` il numero di nodi della lista.
- Costruzione + scansione + deallocazione:
  `T(n) = c0 + c1*n + c2*n + c3*n + c4*n`
- Forma compatta:
  `T(n) = c0 + c*n`
- Complessita tempo: `Theta(n)`.
- Spazio per i nodi:
  `S(n) = n * sizeof(struct Nodo) + O(1)`
- Complessita spazio: `Theta(n)`.

Nel tuo file `n = 2`, quindi in pratica e tempo costante, ma la formula generale resta lineare.

---

## 3) `ceni-arraydinamici.c`

### Obiettivo reale del file
Confrontare array statico e dinamico e usare bene `malloc`, `calloc`, `realloc`.

### Sezione A - Array statico
- `int arrayFisso[5] = {0,1,2,3,4};`
- dimensione calcolata con:
```c
sizeof(arrayFisso) / sizeof(arrayFisso[0])
```

### Sezione B - `malloc`
- alloca 10 interi
- se `NULL`, segnala errore
- riempie con valori `0..9`

### Sezione C - `calloc`
- alloca 15 interi inizializzati a zero
- poi sovrascrive con `i * 3`

### Sezione D - `realloc`
- prova ad espandere l'array da 10 a 20
- usa variabile temporanea `temp`:
```c
int *temp = realloc(mallocArray, nuovaDimensione);
if (temp != NULL) mallocArray = temp;
```
Motivo: se fallisce, non perdi il vecchio puntatore valido.

### Sezione E - cleanup
- `free(mallocArray)`
- `free(callocArray)`

### Differenze che chiedono spesso
- `malloc`: memoria non inizializzata.
- `calloc`: memoria azzerata.
- `realloc`: puo restituire lo stesso indirizzo o uno nuovo.

### Errore tipico da evitare
Fare `mallocArray = realloc(mallocArray, ...)` senza `temp`.

### Costo (tempo e spazio)
Indichiamo con:
- `m` = dimensione array `malloc`
- `c` = dimensione array `calloc`
- `r` = dimensione finale dopo `realloc`

Tempo:
- Riempimento `malloc`: `m` iterazioni
- Riempimento `calloc`: `c` iterazioni
- Riempimento dopo `realloc`: `r` iterazioni
- Eventuale copia interna di `realloc`: fino a `min(m, r)` elementi

Formula:
`T(m,c,r) = a + b*m + d*c + e*r + f*min(m,r)`

Asintotica:
`T(m,c,r) = O(m + c + r)`

Spazio:
- Spazio finale dati utili:
  `S_finale = (r + c) * sizeof(int)`
- Picco teorico (se `realloc` sposta e copia):
  `S_picco <= (m + r + c) * sizeof(int) + overhead`

Asintotica spazio: `Theta(r + c)` per lo stato finale.

---

## 4) `ceni-puntatorifunzioni.c`

### Obiettivo reale del file
Capire la sintassi dei puntatori a funzione e vedere che la chiamata indiretta produce lo stesso risultato della diretta.

### Funzioni usate
- `QuadratoBinomio(a,b)` calcola `(a+b)^2 = a^2 + 2ab + b^2`.
- `NonSaprei(a,b,n)` calcola:
```text
sum_{i=0}^{n-1} (a+b)*i
```

### Dichiarazione chiave
```c
int (*puntatoreNiMuso)(int, int, int) = &NonSaprei;
```
Leggila cosi:
- `puntatoreNiMuso` e un puntatore
- a funzione che prende 3 `int`
- e ritorna `int`

### Tre chiamate equivalenti
- `NonSaprei(a,b,c)`
- `puntatoreNiMuso(a,b,c)`
- `(*puntatoreNiMuso)(a,b,c)`

### Dove si usa nella pratica
- callback (`qsort`, menu funzioni, strategy pattern in C)

### Costo (tempo e spazio)
Sia `n` il terzo parametro passato a `NonSaprei(a,b,n)`.
- `QuadratoBinomio`: `T_q(n) = c1` -> `Theta(1)`
- `NonSaprei`: `T_ns(n) = c2 + c3*n` -> `Theta(n)`

Nel `main`, `NonSaprei` viene chiamata piu volte (diretta + tramite puntatore), quindi:
`T_main(n) = a + k * T_ns(n)` con `k` costante.

Conclusione:
- Tempo totale: `Theta(n)`
- Spazio extra: `Theta(1)`

---

## 5) `ceni-struct.c`

### Obiettivo reale del file
Unire C e algebra lineare: modulo, indipendenza lineare, rango (dimensione spazio generato).

### Tipo dati
```c
typedef struct {
    int x, y, z;
} Vettore;
```
`typedef` evita di scrivere ogni volta `struct ...`.

### Funzione `modulo`
Calcola:
```text
||v|| = sqrt(x^2 + y^2 + z^2)
```
Nel file ritorna `int`, quindi troncamento della parte decimale.

### Funzione `linearmenteIndipendenti`
Calcola il determinante 3x3 dei tre vettori.
- `det != 0` -> indipendenti -> rango 3
- `det == 0` -> dipendenti

### Funzione `dimensioneSpazioGenerato`
Ritorna il rango con questa logica:
1. Se `det != 0`: rango `3`.
2. Altrimenti, se almeno una coppia ha prodotto vettoriale non nullo: rango `2`.
3. Altrimenti, se almeno un vettore non e nullo: rango `1`.
4. Altrimenti (tutti nulli): rango `0`.

### Perche funziona il prodotto vettoriale
Per due vettori in `R^3`:
- `a x b = 0` se sono paralleli (dipendenti)
- `a x b != 0` se non sono paralleli (indipendenti come coppia)

### Caso di test attuale del file
- `v1 = (1,0,1)`
- `v2 = (1,0,1)`
- `v3 = (0,1,0)`

Qui `v1` e `v2` coincidono, quindi non puoi avere rango 3.
`v3` aggiunge una direzione nuova -> rango finale `2`.

### Costo (tempo e spazio)
Nel file lavori sempre in `R^3` (dimensione fissa), quindi ogni funzione fa un numero costante di operazioni.
- `modulo`: `T = c1` -> `Theta(1)`
- determinante 3x3: `T = c2` -> `Theta(1)`
- prodotto vettoriale: `T = c3` -> `Theta(1)`
- `dimensioneSpazioGenerato`: combinazione di test costanti -> `Theta(1)`

Spazio extra:
- solo variabili locali scalari -> `Theta(1)`

Nota teorica generale (se la dimensione fosse `d` variabile):
- rango via eliminazione di Gauss: `O(d^3)`

---

## 6) `ceni-structpuntatori.c`

### Obiettivo reale del file
Usare puntatori a struct in modo pratico e gestire un array dinamico di punti.

### Tipo dati
```c
typedef struct {
    int x, y;
} Punto;
```

### Primo blocco
1. Crea `Punto p1 = {3,4}`.
2. Crea `Punto *ptr = &p1`.
3. Modifica campi con entrambe le sintassi:
   - `(*ptr).x = 5`
   - `ptr->y = 12`

### Secondo blocco
1. Legge `numPunti` da input.
2. Valida input (`scanf == 1` e `numPunti > 0`).
3. Alloca array dinamico:
```c
Punto *punti = malloc(numPunti * sizeof(Punto));
```
4. Legge tutte le coppie `(x,y)` con controllo `scanf == 2`.
5. Stampa i punti inseriti.
6. `free(punti)`.

### Perche questo esercizio e importante
Perche mette insieme:
- `typedef struct`
- puntatori e operatore `->`
- array dinamico di struct
- validazione input
- gestione memoria completa

### Errori tipici da evitare
- `ptr.x` quando `ptr` e puntatore (sbagliato, serve `ptr->x`).
- `sizeof(Punto*)` al posto di `sizeof(Punto)` in `malloc`.
- non controllare `scanf`.

### Costo (tempo e spazio)
Sia `n = numPunti`.
- Primo blocco su `p1` e `ptr`: costo costante `c0`.
- Lettura punti: `n` iterazioni.
- Stampa punti: `n` iterazioni.

Formula tempo:
`T(n) = c0 + c1*n + c2*n = c0 + c*n`

Asintotica tempo:
`Theta(n)`

Formula spazio:
`S(n) = n * sizeof(Punto) + O(1)`

Asintotica spazio:
`Theta(n)`

---

## 7) Teoria trasversale (che puo uscire all'esame)

### Stack vs heap
- Stack: automatico, veloce, vita legata al blocco.
- Heap: manuale, richiede `malloc/free`.

### Undefined behavior (UB) classico
- dereferenziare puntatore non valido
- usare memoria dopo `free`
- doppio `free`
- scrivere fuori dai limiti dell'array

### Complessita da ricordare
- Array: accesso indice `O(1)`.
- Lista: accesso sequenziale `O(n)`.
- Inserimento in testa lista: `O(1)`.

### Formulario rapido dei costi (questo progetto)
- `ceni-logicapuntatori.c`:
  `T = Theta(1)`, `S = Theta(1)`
- `ceni-liste.c`:
  `T(n) = c0 + c*n`, `S(n) = n*sizeof(Nodo) + O(1)`
- `ceni-arraydinamici.c`:
  `T(m,c,r) = a + b*m + d*c + e*r + f*min(m,r)`,
  `S_finale = (r+c)*sizeof(int)`
- `ceni-puntatorifunzioni.c`:
  `T(n) = Theta(n)` (dominata da `NonSaprei`), `S = Theta(1)`
- `ceni-struct.c`:
  `T = Theta(1)`, `S = Theta(1)` (dimensione fissa 3)
- `ceni-structpuntatori.c`:
  `T(n) = c0 + c*n`, `S(n) = n*sizeof(Punto) + O(1)`

---

## 8) Mini simulazione orale (domanda -> risposta)

1. Domanda: differenza tra `pa` e `*pa`?
   Risposta: `pa` contiene indirizzo; `*pa` e il valore in quell'indirizzo.

2. Domanda: quando `realloc` e pericoloso?
   Risposta: quando sovrascrivi subito il puntatore originale senza usare `temp`.

3. Domanda: differenza tra `(*ptr).x` e `ptr->x`?
   Risposta: nessuna, sono equivalenti; `->` e solo sintassi compatta.

4. Domanda: come riconosci se tre vettori in `R^3` sono indipendenti?
   Risposta: determinante 3x3 diverso da zero.

5. Domanda: se determinante e zero, il rango puo essere 2?
   Risposta: si, basta che almeno una coppia sia indipendente (prodotto vettoriale non nullo).

---

## 9) Checklist finale

1. Sai spiegare bene `&`, `*`, `->`.
2. Sai fare una lista concatenata base con `malloc` e `free`.
3. Sai distinguere `malloc`, `calloc`, `realloc` con esempio pratico.
4. Sai dichiarare un puntatore a funzione senza guardare appunti.
5. Sai calcolare/interpretare il rango di 3 vettori in `R^3`.
6. Sai fare input robusto con `scanf` controllando il valore di ritorno.

### Compilazione rapida
```bash
cc -Wall -Wextra -pedantic -std=c11 ceni-logicapuntatori.c -o ceni-logicapuntatori
cc -Wall -Wextra -pedantic -std=c11 ceni-liste.c -o ceni-liste
cc -Wall -Wextra -pedantic -std=c11 ceni-arraydinamici.c -o ceni-arraydinamici
cc -Wall -Wextra -pedantic -std=c11 ceni-puntatorifunzioni.c -o ceni-puntatorifunzioni
cc -Wall -Wextra -pedantic -std=c11 ceni-struct.c -o ceni-struct -lm
cc -Wall -Wextra -pedantic -std=c11 ceni-structpuntatori.c -o ceni-structpuntatori
```

---

## 10) Teoria liste per l'esame (definizioni, costo, chiamate, side effects)

### 10.1 Definizioni base da sapere
- Una lista e un ADT (Abstract Data Type): definisce operazioni e comportamento, indipendenti dall'implementazione.
- Operazioni tipiche: `init`, `isEmpty`, `search`, `insert`, `delete`, `get`, `set`, `print`.
- Ogni operazione si descrive con:
  - precondizioni
  - postcondizioni
  - side effects sulla struttura dati
  - costo e complessita

### 10.2 Modello generale di costo
Sia `x` l'input (per esempio `n`, `k`, `m`):

`C(x) = sum_j (c_j * f_j(x))`

- `c_j`: costo unitario dell'operazione elementare `j` (costante nel modello RAM).
- `f_j(x)`: numero di volte che l'operazione `j` viene eseguita.

Casi da distinguere:
- caso migliore
- caso medio
- caso peggiore

Notazioni asintotiche:
- `O(g(n))`: limite superiore.
- `Omega(g(n))`: limite inferiore.
- `Theta(g(n))`: ordine di crescita esatto (stesso superiore e inferiore).

### 10.3 Lista sequenziale (array contiguo)
Definizione:
- Elementi in memoria contigua.
- Accesso diretto con indice.

Costi tipici (con `n` elementi e posizione `i`):
- Accesso `L[i]`: `Theta(1)`.
- Ricerca lineare: `Theta(n)`.
- Inserimento in posizione `i`:
  `T_ins(i) = a + b*(n - i + 1)` (shift a destra).
- Cancellazione in posizione `i`:
  `T_del(i) = a + b*(n - i)` (shift a sinistra).
- Inserimento in coda: `Theta(1)` solo se c'e spazio gia allocato.
- Spazio: `Theta(m)` con capacita `m` (oppure `Theta(n)` se dinamico con crescita proporzionale).

Side effects tipici:
- cambia `n` (numero elementi)
- modifica il contenuto delle celle dopo la posizione coinvolta

Esempio prototipo + chiamate:
```c
typedef struct {
    int a[100];
    int n;
} ListSeq;

void initSeq(ListSeq *L);
int insertAtSeq(ListSeq *L, int pos, int x);
int deleteAtSeq(ListSeq *L, int pos, int *out);

ListSeq L;
initSeq(&L);
insertAtSeq(&L, 1, 7);
insertAtSeq(&L, 2, 3);
deleteAtSeq(&L, 1, NULL);
```

### 10.4 Lista collegata con array e indici (cursor list)
Definizione:
- Ogni nodo e in un array, con campi `info[idx]` e `next[idx]`.
- `head` punta al primo nodo usato.
- `free` punta al primo nodo libero.

Costi tipici:
- Accesso alla posizione `i`: `Theta(i)`, peggiore `Theta(n)`.
- Ricerca valore: `Theta(n)`.
- Inserimento/cancellazione in testa: `Theta(1)`.
- Inserimento/cancellazione dopo un nodo gia noto: `Theta(1)`.
- Se devi prima trovare il predecessore: costo totale `Theta(n)`.
- Spazio: `Theta(m)` con `m` capacita dell'array nodi.

Side effects tipici:
- aggiornamento di `head`
- aggiornamento di `free`
- modifica dei collegamenti `next[]`

Esempio prototipo + chiamate:
```c
#define MAXN 100
typedef struct {
    int info[MAXN];
    int next[MAXN];
    int head;
    int free;
} CursorList;

void initCursor(CursorList *L);
int pushFrontCursor(CursorList *L, int x);
int appendCursor(CursorList *L, int x);

CursorList C;
initCursor(&C);
pushFrontCursor(&C, 7);
pushFrontCursor(&C, 3);
appendCursor(&C, 5);
```

### 10.5 Lista collegata con puntatori
Definizione:
- Ogni nodo e allocato dinamicamente in heap.
- Nodo tipico: `info` + puntatore `next` (eventuale `prev`).

Costi tipici:
- Inserimento/cancellazione in testa: `Theta(1)`.
- Inserimento in coda: `Theta(1)` se tieni anche `tail`, altrimenti `Theta(n)`.
- Ricerca valore: `Theta(n)`.
- Accesso alla posizione `i`: `Theta(i)`, peggiore `Theta(n)`.
- Spazio: `Theta(n)` per i nodi effettivamente presenti.

Side effects tipici:
- cambiamenti di `head`/`tail`
- aggiornamento dei campi `next`
- eventuale deallocazione (`free`) nei delete

Esempio prototipo + chiamate:
```c
typedef struct Node {
    float val;
    struct Node *next;
} Node;

void pushFrontPtr(Node **head, float x);
int moveMatchesToTail(Node **LA, Node **LB, const float *target, int M);

Node *LA = NULL;
Node *LB = NULL;
float target[] = {2.0f, 1.0f};
pushFrontPtr(&LA, 3.0f);
pushFrontPtr(&LA, 2.0f);
moveMatchesToTail(&LA, &LB, target, 2);
```

### 10.6 Esempi formule sui tuoi esercizi tipo
- Inversione lista sequenziale di `n` elementi:
  `C(n) = a + b*floor(n/2)` -> `Theta(n)`, spazio extra `Theta(1)`.
- Sposta primi `K` elementi da testa a coda invertendoli (lista collegata):
  `C(n,K) = a + b*K + c*(n-K) + d*K = a + c*n + (b+d-c)*K`.
  Con `K <= n`, nel caso generale: `Theta(n)`.
- Filtraggio da `LA` a `LB` con array `target` di taglia `M` (controllo naive):
  `C(n,M) = a + n*(b + c*M + d)` -> `Theta(n*M)`.

### 10.7 Metodo "sempre valido" per rispondere al compito
1. Definisci bene le dimensioni input (`n`, `k`, `m`).
2. Elenca le operazioni elementari che conti.
3. Scrivi la formula `C(...) = sum c_j f_j(...)`.
4. Riduci al termine dominante.
5. Dichiara `O`, `Omega`, `Theta`.
6. Chiudi con side effects e invarianti mantenuti.
