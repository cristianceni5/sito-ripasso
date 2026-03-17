# Fondamenti di Informatica

![Surry](https://staticfanpage.akamaized.net/wp-content/uploads/sites/34/2025/02/Salvatore-Cinquegrana-1200x675.jpg)

---

09/10/25

## Espressioni

Un'espressione è una combinazione di variabili, costanti e operatori che produce un valore. In C, le espressioni possono avere **side-effect** (modificare lo stato di una variabile) o essere pure (restituire solo un valore).

``` bnf
<expr> ::= <var> | <const> | <var> ++ | ++ <var> | <var> -- | -- <var> |
```

### Gli unici operatori che fanno side-effect su una variabile sono

1. incremento ++
2. decremento --
3. assegnazione =

``` bnf
<var> = <expr> | <expr1><op2><expr2> | <op1><expr1>
```

### Gli operatori binari

### Aritmetici

``` bnf
<op2> ::= + | - | * | / | %
```

Operazioni fra int

``` c
int a;
int b;
int c;

a = 10;
b = 4;

c = a/b; //c sarà 2, perché si lavora fra interi
```

Operazioni fra int ma c float

``` c
int a;
int b;
float c;

a = 10;
b = 4;

c = a/b; //c sarà 2, perché si lavora fra interi anche se c è float
```

Operazioni fra int e float

``` c
int a;
float b;
int c;

a = 10;
b = 4;

c = a/b; //Operazione eseguita fra float (tipo più forte) ma c resta 2, viene troncata la parte decimale
```

Operazioni fra int e float con c float

``` c
int a;
float b;
float c;

a = 10;
b = 4;

c = a/b; //c sarà 2.5, dato che float prevale su int e c è comunque float
```

Forza dei tipi di dato

``` html2
int < float < double
short < int < long
unsigned < int
```

---

### Relazionali

Gli operatori relazionali eseguono **confronti** tra due valori e ritornano un risultato booleano (0 = falso, ≠0 = vero).

``` bnf
<op2> ::= < | <= | == | != | >= | >
```

**Importante**: In C non esiste un tipo `boolean` nativo. Il risultato dell'applicazione di un operatore relazionale è:

- `1` per **vero**
- `0` per **falso**

**Tabella degli operatori**:

- `a < b`: a minore di b
- `a <= b`: a minore o uguale a b
- `a == b`: a uguale a b
- `a != b`: a diverso da b
- `a >= b`: a maggiore o uguale a b
- `a > b`: a maggiore di b

``` c
int a = 10;
int b = 5;
int c;

c = a > b;   //c sarà 1 (vero, perché 10 > 5)
c = a == b;  //c sarà 0 (falso, perché 10 ≠ 5)
c = a >= b;  //c sarà 1 (vero, perché 10 ≥ 5)
```

**Attenzione**: Non confondere `=` (assegnazione) con `==` (confronto). `a = b` assegna il valore di b ad a, mentre `a == b` controlla se sono uguali.

---

### Logici

Gli operatori logici combinano valori booleani (risultati di confronti) per formare espressioni logiche complesse.

``` bnf
<op2> ::= && /*And*/ | || /*Or*/ | ! /*Not*/
```

**Regole di verità in C**:

- Un valore **≠0 è considerato VERO**
- Un valore **==0 è considerato FALSO**
- Il risultato è sempre **0 (falso) o 1 (vero)**

**Operatori**:

- `!a`: NOT logico (negazione). Ritorna 1 se a è falso, 0 se a è vero
- `a && b`: AND logico. Ritorna 1 solo se entrambi a e b sono veri
- `a || b`: OR logico. Ritorna 1 se almeno uno tra a e b è vero

``` c
int a = 7;
int b = 5;
int c;

c = !3.2;         //c è 0 (falso, perché 3.2 è vero quindi la negazione è falsa)
c = a > b && a;   //c è 1 (vero, perché 7>5 è vero AND 7 è vero)
c = a > 10 || b;  //c è 1 (vero, perché 5 è vero, quindi l'OR è vero)
```

### Op logico &&

L'AND logico ha una proprietà speciale: **short-circuit evaluation** (valutazione pigra).

Viene eseguita `expr1` e sono applicati i suoi side-effect (se presenti).
Se il valore restituito da `expr1` è **vero** (≠0) allora è eseguita anche `expr2`. **Altrimenti**, se `expr1` è **falsa** (==0), `expr2` **non viene mai valutata**.

Questa assimmetria è nota come **"short circuit"** ed è utile per ottimizzazione: se la prima condizione è falsa, non serve valutare la seconda.

``` c
int a = 6;
int b = 3;
int c;

c = a < b && a++;  //Se a < b è falso, a++ NON viene eseguito
                   //Poiché 6 < 3 è falso, a rimane 6
```

### Op logico ||

L'OR logico ha anch'esso **short-circuit evaluation**.

Viene eseguita `expr1` e sono applicati i suoi side-effect (se presenti).
Se il valore restituito da `expr1` è **vero** (≠0), `expr2` **non viene valutata** perché il risultato dell'OR è comunque vero.
Se `expr1` è **falso** (==0), allora è valutata `expr2` per determinare il risultato finale.

**Utilizzo pratico**:

```c
int *ptr;
if (ptr != NULL || *(ptr) == 5) {
    // se ptr è NULL, il secondo termine NON viene valutato
    // (evita dereferenziazione di puntatore NULL)
}
```

---

### Bit-a-bit

Operatori che lavorano direttamente sui **bit** individuali di una variabile. Molto efficienti e usati in programmazione di sistema, grafica e crittografia.

``` bnf
<op2> ::= & | | | << | >> | ^
```

**Operatori binari bit-a-bit**:

- `a & b` (AND): bit 1 solo se entrambi i bit sono 1
- `a | b` (OR): bit 1 se almeno uno dei bit è 1
- `a ^ b` (XOR): bit 1 se i bit sono diversi
- `a << n` (shift left): sposta i bit a sinistra di n posizioni (equivale a `a × 2^n`)
- `a >> n` (shift right): sposta i bit a destra di n posizioni (equivale a `a ÷ 2^n`)

**Operatore unario**:

- `~a` (NOT bit-a-bit): inverte tutti i bit (0→1, 1→0)

**Esempio**:

```c
int a = 5;      // 0101 in binario
int b = 3;      // 0011 in binario

int c = a & b;  // 0001 = 1
int d = a | b;  // 0111 = 7
int e = a ^ b;  // 0110 = 6
int f = a << 1; // 1010 = 10 (5 * 2)
int g = a >> 1; // 0010 = 2 (5 / 2)
```

### Gli operatori unari

``` bnf
<op1> ::= ! /*Not logico */ | ~ /*Negazione bit-a-bit/*
```

## Semantica

``` bnf
. Γ(<expr1><op2><expr2>) = Γ(<expr1>) <op2> Γ(expr2)
```

---

16/10/25

## Puntatori

I puntatori sono variabili che memorizzano **indirizzi di memoria** di altre variabili. Sono tipicamente di 32 bit (su sistemi a 32-bit) o 64 bit (su sistemi a 64-bit). Un puntatore può puntare a qualsiasi tipo di dato: int, float, char, struct, o anche void (puntatore generico). Sono fondamentali per la gestione dinamica della memoria e per passare variabili per riferimento.

``` bnf
<declaration> ::= <type><decl>
<decl> ::= <identifier> | * <decl>
```

``` c
int * ptr; //Var puntatore
int ** ptr2 //Vuole indirizzo di un puntatore
```

### Uso dei puntatori

Sul puntatore è possibile fare l'operazione di **dereferenziazione**

Mi permette di usare un puntatore per accedere ad una variabile nella memoria.

``` bnf
<var> ::= <identifier> | (<var>) | *<expr> //Espressione che restituisce un indirizzo
```

### Operatore indirizzo

Assegnare ad un puntatore un'altra variabile.

``` bnf
<expr> ::= ... | &<var>
```

``` c
int a;
int *ptr:

ptr = &a; //Assegno a ptr l'indirizzo di a
```

![puntatore memoria](https://www.fe.infn.it/u/spizzo/prog09/pict/memoria.gif)

Esempio:

``` c
void *ptr;
int m:
int n;

float x;
float y;

int select;

if(select)
{
    ptr = &m; //Assegno indirizzo var m
}
else
{ 
    ptr = &x //Assegno indirizzo var x
} 

//Il tipo non è importante

if(select)
{//n = m
    n = *((int*)ptr);
}
else
{ //y = x
    y = *((float*)ptr);
}

//Il tipo conta
```

- (int*) cast del puntatore. Puntatore a void è trasformato in puntatore a int.

- *dereferenzia l'indirzzo di una var intera.

### Cast di un puntatore

``` bnf
<expr> ::= ... | (<cast_type>) <expr>
<cast_type> ::= <type> | <cast_type>*
```

Rendere (int*) legale nella nostra grammatica.

---

## Array

Un array è un insieme ordinato di variabili dello **stesso tipo** memorizzate in posizioni **contigue** della memoria. Permette di accedere agli elementi tramite un nome collettivo e un indice numerico (base 0).

**Caratteristiche**:
- Tutte le variabili hanno lo stesso nome (identificatore dell'array)
- Sono indicate dal nome collettivo e un indice numerico progressivo
- L'allocazione è **statica** (fissata a compile-time) per array dichiarati come variabili locali
- Occupano spazio di memoria contiguità garantisce accesso rapido tramite aritmetica dei puntatori

Le variabili che compongono l'insieme sono allocate in posizioni contigue della memoria, quindi la dimensione totale è: `sizeof(tipo) × numero_elementi`.

### Dichiarazione

``` bnf
<declaration> ::= <type><decl>;
<decl> ::= <identifier> | *<decl> | <decl>[<const>]
```

``` c
int V[10]; //V è un array di 10 variabili di tipo int

float X[15]; //X è un array di 15 variabili float

int A[5][3]; //A è un array di 5 array di 3 variabili int, A matrice 5x3
```

---

### Array semplice

![array memoria](https://www.diag.uniroma1.it/~liberato/struct/array/statico2.gif)

---

### Array complesso

![array memoria](https://media.geeksforgeeks.org/wp-content/uploads/20220531171048/gfgpicmem-660x344.png)

---

### Albero sintattico

![albero array](screen/alberoarray.png)

Esempio
(occupa 24 byte in memoria) 3 x 4 B x 2

``` c
float **Z[3][2]; // Z è un array di 3 array di 2
//Doppi puntatori a float
```

``` bnf
<decl> ::= ... | (<decl>)
```

---

### Riferimento alle variabili di un array

``` bnf
<var> ::= ... | <expr1> [<expr2>]
```

è equivalente alla seguente scrittura *(expr1 + expr2) aritmetica dei puntatori.

- expr1 restituisce un indirizzo
- expr2 restituisce un intero

il nome di un array se usato in una espressione restituisce il valore l'indirizzo di inizio in memoria dell'array.

- expr1 può essere il nome dell'array

![ptr array](screen/ptrarray.png)

Puntatore ad un array

---

### Array multidimensionale

Per risolvere problemi con matrici

Esempio: Calcolo del prodotto fra A e B

![matrici](screen/matrici.png)

formano una matrice C 3x4.

Proviamo con il codice

``` c
int A[3][2];
int B[2][4];
int C[3][4];

int i; //Indice riga
int j; //Indice colonna
int k; //k per sommatoria

for(i = 0; i < 3; i++)
{
    for(j = 0; j < 4; j++)
    {
        C[i][j] = 0;

        for(k = 0; k < 2; k++)
        {
            C[i][j] += A[i][k] * B[k][j];
        }
    }
}

//Stampa C
```

---

20/10/25

## Grammatica delle istruzioni

Le istruzioni dirigono il **flusso di esecuzione** (control flow) di un programma. Una sequenza di istruzioni forma un blocco che viene eseguito in ordine sequenziale.

``` bnf
<statement> ::= <expr>; | <statement1><statement2> | {statement} //Graffe del C (compound)
```

**Tipi di statement**:

- **Semplice**: un'espressione seguita da `;` (es: `a = 5;`)
- **Composto**: multiple istruzioni racchiuse in `{ }` formano un blocco logico
- **Sequenza**: istruzioni eseguite una dopo l'altra

### Semantica istruzioni

Viene eseguita l'espressione ed i suoi eventuali side-effects sono applicati al momento dell'esecuzione. Il **controllo** del **flusso** è trasferito all'istruzione successiva (o al salto speciale se è presente una istruzione di controllo).

### Istruzione condizionale

``` c
if(expr_guardia)
{
    //Ti puzza l'ano
}
else
{
    //Ti puzza il culo
}
```

2 casi:

- solo if (solo una condizione)

``` bnf
<statement> ::= ... | if(<expr_guardia>)<statement>
```

- anche else

``` bnf
<statement> ::= ... | if(<expr_guardia>)<statement1> else<statement2>
```

Viene calcolata l'espressione di guardia se è vera (diverso da 0) viene eseguito:

``` bnf
<statement1>
```

altrimenti se presente else viene eseguita

``` bnf
<statement2>
```

### Istruzioni iterative

Permettono di **ripetere** blocchi di codice finché una condizione è soddisfatta.

``` bnf
<statement> ::= ... | for(<expr_int>; <expr_guard>; <expr_inc>)<statement> | while(<expr_guard>)<statement> | do(<statement>) while(<expr_guard>)
```

### for() — Ciclo controllato

**Sintassi**: `for(inizializzazione; condizione; aggiornamento) statement`

### Semantica for

1. Viene eseguita l'espressione di **inizializzazione** (`expr_int`) — **una sola volta** all'inizio
2. Viene valutata l'espressione di **guardia** (`expr_guard`)
3. Se la guardia è **vera** (≠ 0):
   - Viene eseguito lo statement del corpo del ciclo
   - Viene eseguita l'espressione di **aggiornamento** (`expr_inc`)
   - Ritorna al passo 2
4. Se la guardia è **falsa** (== 0), il controllo esce dal ciclo e passa all'istruzione successiva

**Esempio**: `for(i = 0; i < 10; i++)` stampa `i` da 0 a 9

### while() — Ciclo condizionale

Ripete uno statement finché la condizione rimane vera. La condizione è **controllata all'inizio**, quindi il corpo potrebbe non eseguirsi mai.

### do-while() — Ciclo con controllo al termine

Ripete uno statement almeno una volta, poi continua finché la condizione rimane vera. La condizione è **controllata al termine**.

---

23/10/25

### Istruzione di salto

``` bnf
<statement> ::= goto <label>; | break; | continue; | switch(<expr>){
    {case <const>: <statement>}
    [default: <statement>]
} | return[<expr>];
```

### goto

- **goto** permette di trasferire incondizionatamente il flusso di esecuzione del programma a un'altra istruzione, identificata da un'etichetta. Sebbene sia una funzionalità del linguaggio, il suo uso è fortemente sconsigliato dalla comunità dei programmatori.

```c
// ... codice
if (condizione) {
    goto etichetta;
}
// ... codice che viene saltato
etichetta:
// ... codice che viene eseguito dopo il salto
```

---

### break

- **break** serve per uscire immediatamente da un ciclo (for, while, do-while) o da un'istruzione switch. Quando l'esecuzione del programma incontra un break, il controllo viene trasferito alla prima istruzione che segue il blocco di codice in cui si trova il break

---

### continue

- L'istruzione **continue** nel linguaggio C serve a saltare l'iterazione corrente di un ciclo e passare immediatamente a quella successiva. A differenza dell'istruzione break, che termina l'intero ciclo, continue interrompe solo l'esecuzione del blocco di codice rimanente nell'iterazione in corso e riprende con l'iterazione successiva.

---

### switch

- **switch** L'istruzione switch nel linguaggio C è una struttura di controllo che permette di eseguire diversi blocchi di codice in base al valore di una singola variabile o espressione. È un'alternativa più leggibile e pulita a una lunga serie di istruzioni if-else if.

```c
switch (espressione) {
    case valore1:
        // blocco di codice da eseguire se l'espressione è uguale a valore1
        break;
    case valore2:
        // blocco di codice da eseguire se l'espressione è uguale a valore2
        break;
    // ... altri case ...
    default:
        // blocco di codice da eseguire se nessun case corrisponde
}
```

## Funzioni

Una funzione è un **blocco di codice riutilizzabile** che esegue un compito specifico. È una sorta di **goto** con ritorno: trasferisce il controllo del flusso di esecuzione ad un frammento di codice e lo riottiene indietro al termine dell'esecuzione.

**Componenti di una funzione**:

- **Tipo di ritorno**: il tipo di dato che la funzione restituisce (es: `int`, `void`, `float`)
- **Nome**: identificatore univoco della funzione
- **Parametri**: variabili d'ingresso passate alla funzione (lista opzionale)
- **Corpo**: blocco di codice che esegue le operazioni
- **Return**: restituisce un valore al chiamante (opzionale se tipo è `void`)

**Vantaggi dell'uso delle funzioni**:

- **Modularità**: Permette di suddividere un programma complesso in parti più piccole e gestibili.
- **Riutilizzo del codice**: Consente di scrivere un blocco di codice una sola volta e di richiamarlo più volte.
- **Chiarezza**: Rende il codice più leggibile e facile da capire, in quanto ogni funzione ha un nome che ne descrive lo scopo.
- **Debugging**: Facilita l'isolamento e la correzione di errori.
- **Manutenzione**: Modificare una funzione centralizza i cambiamenti.

![funzioni](<screen/Screenshot 2025-10-23 alle 09.14.12.png>)

```c
// 1. Prototipo della funzione
// Dichiara una funzione che accetta due interi e restituisce un intero.
int somma_numeri(int a, int b);

int main() {
    int risultato;
    int numero1 = 10;
    int numero2 = 5;

    // 3. Chiamata alla funzione
    risultato = somma_numeri(numero1, numero2);

    printf("La somma è: %d\n", risultato);
    return 0;
}

// 2. Definizione della funzione
// Implementa il codice per sommare due interi.
int somma_numeri(int a, int b) {
    int somma;
    somma = a + b;
    return somma;
}
```

---

30/10/25

## Grammatica del C

```bnf
<program>::= { <declaration> | <function_definition> | <directive> | typedef <type> <identifier>; }
```

**typedef** — Definizione di tipo personalizzato

La parola chiave `typedef` (abbreviazione di "type definition") serve a creare un **sinonimo o alias** per un tipo di dato già esistente. L'obiettivo principale è rendere il codice più leggibile, portabile e semplice da gestire.

**Vantaggi**:

- Migliora la leggibilità — `boolean` è più chiaro di `unsigned short int`
- Facilita manutenzione — cambiare il tipo sottostante richiede modifica in un solo punto
- Portabilità — adatta i tipi a diverse piattaforme
- Compattezza — evita di digitare tipi complessi ripetutamente

```c
typedef unsigned short int boolean;
boolean a;  // equivalente a: unsigned short int a;
```

**Uso con struct e union**:

```c
typedef struct {
    int x;
    int y;
} Point;  // d'ora in poi possiamo usare Point invece di struct { ... }
```

typedef può essere usato per dare un nome più significativo a un tipo di dato base, come int, char o float, oppure a tipi complessi come struct e pointer.

Esempi:

```c
#define TRUE 1
#define FALSE 0

typedef unsigned short int boolean;

int main()
{
    boolean a;
    a = TRUE;
}
```

## Nota sulle funzioni

### Variabili statiche

Sono variabili dichiarate all'interno delle funzioni (modificatore **static**). Sono inizializzate una sola volta e mantengono il loro valore nelle chiamate successive.
Allocate nel segmento dati **non** nello stack

```c
void f(int a)
{
    static int count;
    count = 0;

    count ++;
    //Conta quante volte viene chiamata la funzione
}
```

---

## Dati strutturati (struct)

Un dato strutturato (o **struct**) è un insieme di variabili anche di tipo **diverso** raggruppate sotto un unico nome. Ogni elemento della struttura è chiamato **membro** o **campo** e viene identificato da un nome simbolico, non da un indice numerico come negli array.

**Caratteristiche**:

- Permette di combinare tipi diversi (int, float, char, array, puntatori, altre struct) in un unico dato
- Le variabili possono essere allocate in posizioni di memoria **non necessariamente contigue** (il compilatore ottimizza l'allineamento)
- L'accesso ai campi avviene tramite l'operatore `.` (per variabili) o `->` (per puntatori a struct)
- Utili per rappresentare entità complesse (es: persona con nome, età, indirizzo)

### Grammatica

- definizione

- dichiarazione

- riferimento

### Definizione

```bnf
<struct_definition> ::= struct <identifier> {{<type><decl>;}};
```

```c
struct Point
{
    float x;
    float y;
};
```

### Dichiarazione

```bnf
<type> ::= ... | struct <identifier>
```

```c
struct Point pt1; //Dichiare una va di tipo struct Point
struct Point pt2;
struct Point points[10]; //Array di tipo struct Point
struct Point *ptr; //Puntatore ad una var struct Point
```

posso pure:

```c
typedef struct Point Punto; //Punto è un alias per struct Point
```

### Riferimento/Uso

```c
struct Persona 
{
    char nome[50];
    int eta;
    float stipendio;
} persona1, persona2;

persona1.eta = 30;
printf("Età: %d\n", persona1.eta);
```

![funzioni](<screen/Screenshot 2025-10-30 alle 09.28.15.png>)

---

## Esercizi

### (es) riferimento a variabile

```c
(A[count].ptr) -> codice
```

### Definizioni e definizioni

```c
struct record 
{
    struct noninativo *ptr;
};

struct nominativo
{
    int codice;
};
```

```c
struct record A[128];
int count;
```

### Quesiti

- correttezza sintattica con albero sint.

- semantica.

- produzioni della grammatica coinvolte.

### Albero sintattico ex

![albero ex1 surry](<screen/Screenshot 2025-10-30 alle 10.00.44.png>)

---

13/11/25

## Lista sequenziale

Una lista sequenziale è un'implementazione **statica** di lista usando un array (buffer). Gli elementi sono memorizzati in posizioni contigue, e la gestione della lista avviene tramite **indici** (head/tail per coda circolare).

![lista](<screen/Screenshot 2025-11-13 alle 08.35.27.png>)

![alt text](<screen/Screenshot 2025-11-13 alle 09.06.30.png>)

**Struttura dati**:

```c
struct list{
    int *buffer;     // array dinamico che contiene gli elementi
    int size;        // capacità massima della lista
    int head;        // indice del primo elemento (testa)
    int tail;        // indice della prima posizione libera (coda)
}
```

**Stato della lista**:
- **Lista vuota**: `tail == head` (nessun elemento)
- **Lista piena**: `(tail + 1) % size == head` (una posizione libera per il wrapping circolare)
- **Un elemento**: `(head + 1) % size == tail`

### Cancellazione in coda

```c
boolean suf_consume(struct list *ptr, int *value){
    if(ptr->head != ptr->tail)
    {
        ptr->tail = (ptr->tail-1 + ptr->size)%ptr->size;

        *value = ptr->buffer[ptr->tail];

        return TRUE;
    }

    return FALSE;
}
```

### Operazione di ricerca

effettua la ricerca di un elemento finché non viene trovato

![alt text](<screen/Screenshot 2025-11-13 alle 09.05.28.png>)

```c
boolean search(struct list *ptr, int target)
{
    int position;
    boolean found;
    position = ptr->head;
    found = FALSE;

    while(position != ptr->tail && found == FALSE)
    {
        if(ptr->buffer[position] == target)
        {
            found = TRUE;
        }
        else
        {
            position = (position +1)%ptr->size;
        }
    }

    return found;
}
```

---

### Vantaggi/svantaggi

- ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ allocazione della memoria eseguita una volta sola in `init`(riduce interazione con sistema operativo).

- ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ accesso diretto agli elementi (es: `ins/canc` in coda).

- ( ˘︹˘ ) l'allocazione fatta una volta solo implica dimensione fissata dell'array (max numero elementi).

- ( ˘︹˘ ) la gestione implicata della relazione di successione implica ad esempio che l'inserimento in ordine richieda lo spostamento degli elementi.

---

## Liste collegate

Una lista collegata è un'implementazione **statica** (ma logicamente dinamica) che usa un array di record, dove ogni record contiene un dato e un **indice al prossimo elemento**. La relazione di successione è codificata esplicitamente tramite indici, non tramite posizioni contigue di memoria.

**Vantaggi rispetto a lista sequenziale**:

- Inserimento/rimozione in posizione intermedia senza spostamenti
- Uso efficiente dello spazio (no "buchi" come in coda circolare piena)

![alt text](<screen/Screenshot 2025-11-13 alle 10.04.07.png>)

**Struttura dati**:

```c
struct record{
    int value;   // dato memorizzato
    int next;    // indice del prossimo record (-1 = fine lista)
}

struct list{
    struct record *buffer;  // array di record
    int free;               // indice del primo record libero
    int first;              // indice del primo elemento della lista
    int size;               // capacità massima
}
```

**Gestione memoria**: Il campo `free` punta al primo record disponibile. I record liberi formano una catena interna ("free list") per recupero veloce.

---

21/11/25

## Vantaggi/svantaggi lista collegata con array ed indici

- ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ allocazione statica riduce interazione con sistema operativo.

- ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ inserimento in ordine non richiede lo spostamento di elementi.

- ( ˘︹˘ ) allocazione statica della memoria implica dimensione (size) dell'array fissata all'origine.

- ( ˘︹˘ ) Non ho accesso diretto agli elementi.

---

## Lista collegata con puntatori

### Idea

Una lista collegata con **puntatori** è un'implementazione **dinamica** dove gli elementi sono memorizzati in posizioni qualunque della memoria (allocati dinamicamente con `malloc`). Ogni nodo contiene un dato e un **puntatore al nodo successivo**.

**Vantaggi**:

- Nessun limite di dimensione prefissata
- Inserimento/rimozione efficiente in qualsiasi posizione
- Uso di memoria dinamico e flessibile

**Svantaggi**:

- Non c'è accesso diretto agli elementi (è necessario attraversare la lista)
- Overhead di memoria per i puntatori
- Maggiore complessità implementativa

### Principio di funzionamento

Gli elementi della lista sono memorizzati in posizioni qualunque della memoria.

- Utilizza un **puntatore** per collegare ogni elemento al successore (tramite campo `next`)

`{31, 25, 19, 27}`:

![alt text](<screen/Screenshot 2025-11-21 alle 17.31.04.png>)

![alt text](<screen/Screenshot 2025-11-21 alle 17.34.31.png>)

triangolino -> puntatore.

---

```c
struct list{
    int value;
    struct list *next;
}
```

---

### Funzione di inizializzazione

```c
void init(struct list **ptr){
    *ptr = NULL;
}
```

---

### Funzione inserimento in testa

![alt text](<screen/Screenshot 2025-11-21 alle 18.05.19.png>)

```c
void pre_insert(struct list **ptr, int value)
{
    struct list *tmp;
    tmp = (struct list *)malloc(sizeof(struct list));
    tmp -> value = value;
    tmp -> next = *ptr;
    *ptr = tmp;
}
```

---

### Funzione cancellazione in testa

![alt text](<screen/Screenshot 2025-11-21 alle 18.22.29.png>)

![text](<screen/Screenshot 2025-11-21 alle 18.25.06.png>)

---

24/11/25

### Funzione inserimento in coda

![alt text](<screen/Screenshot 2025-11-24 alle 16.29.47.png>)

```c
void suf_insert(struct list **ptr, int value)
{
    /*1*/while(*ptr != NULL)
    {
        ptr =&((*ptr)->next);
    }

    /*2*/pre_insert(ptr, value);
}
```

---

### Inserimento in ordine

```c
void ord_insert(struct list **ptr, int value)
{
    while(*ptr != NULL && (*ptr)->value < value)
    {
        ptr =& ((*ptr)->next);
    }
}
```

## Esercizio tipo

- Funzione di cancellazione in coda

```c
int main()
{
    struct list *ptr;
    init(&ptr);
    pre_insert(&ptr, 5);
    pre_insert(&ptr, 7);
    pre_insert(&ptr, 3);
    //{3, 5, 7}

    //visit(ptr);
    //pre_consume(&ptr);
}
```

---

### Inserimento in testa che usa il valore di ritorno per aggiornare il puntatore alla testa della lista

```c
struct list *pre_insert_return(struct list *ptr, int value)
{
    struct list *tmp;
    tmp = (struct list*)malloc(sizeof(struct list));
    tmp->value = value;
    tmp->next = ptr;
    return tmp;
}

int main()
{
    struct list *ptr;
    init($ptr);
    ptr = pre_insert_return(ptr, 6);
}
```

---

### Funzione di clonazione di una lista collegata con puntatori

![alt text](<screen/Screenshot 2025-11-24 alle 17.14.44.png>)

```c
void clone(struct list *src_ptr, struct list **dst_ptr)
{
    init(dst_ptr);
    while(src_ptr != NULL)
    {
        suf_insert(dst_ptr, src_ptr->value);
        src_ptr = src_ptr->next;
    }
}
```

### Stima num. op. `clone()`

`C = C1 + (S + C1) + (2S + C1) + ... + ((N-1)S + C1)`

`S`= costo per inserire elemento dst_ptr

`C1`= costo per inserire con pre_insert in dst_ptr

`N`= numero elementi src_ptr

---

## Vantaggi/svantaggi dhn

- ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ numero massimo di elementi non prefissato.

- ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ inserimento in posizione intermedia non richiede spostamento degli elementi.

- ( ˘︹˘ ) allocazione dinamica aumenta l'interazione con il sistema operativo.

- ( ˘︹˘ ) non abbiamo accesso diretto agli elementi.

---

## Ricorsione

La ricorsione è un paradigma di programmazione dove un'entità (funzione o tipo) **fa riferimento a se stessa**. È un meccanismo potente per risolvere problemi che hanno struttura auto-simile o richiedono suddivisione ricorsiva.

**Applicazioni comuni**:

- Traversamento di alberi e grafi
- Ordinamento (merge sort, quick sort)
- Parsing e compilazione
- Ricerca e backtracking
- Problemi matematici (fattoriale, Fibonacci)

### Ricorsione nella definizione di un dato

La definizione di un dato è ricorsiva se fa riferimento a se stessa in modo **diretto** o per il tramite di ulteriori definizioni. È essenziale usare **puntatori** per evitare dimensione infinita.

```c
struct list 
{
    int value;
    struct list *next;
} //Corretto

struct list_impossibile
{
    int value;
    struct list_impossibile a;
} //NoOOOOOOoooOOOO

//nel primo esempio dico che è un puntatore con *, quindi gli alloco 4B

//nel secondo non so che tipo sia
```

### Ricorsione nelle funzioni

Una funzione è ricorsiva se fa riferimento a se stessa in modo **diretto** (la funzione richiama se stessa) o per il tramite della chiamata da altre funzioni **indiretto**.

Si applica quando è necessario trattare una molteplicita di elementi. Una chiamata ricorsiva tratta un elemento dell'insieme e demanda la trattazione degli altri elementi alle chiamate ricorsive.

### Lista collegata con puntatori

- init KO
- visit OK
- search OK
- pre_insert/pre_consume KO
- suf_insert/suf_consume OK

---

04/12/25

## Ordinamento

### Selection (sequential) sort

riduce il problema dell'ordinamento alla **ricerca del massimo** ed allo **swap**

![alt text](<screen/Screenshot 2025-12-04 alle 08.40.57.png>)

**Principio**: ad ogni iterazione, trova l'elemento massimo (o minimo) nell'array non ordinato e lo posiziona alla fine (o all'inizio) della porzione ordinata, spostando via gli elementi già ordinati.

**Algoritmo** (ordinamento crescente):

1. Cerca il massimo nell'array da indice 0 a `n-1`
2. Scambia il massimo con l'elemento in posizione `n-1`
3. Riduci l'intervallo di ricerca a `[0, n-2]`
4. Ripeti fino a ordinare tutto l'array

**Complessità**:

- **Tempo**: O(n²) nel caso medio e pessimo (sempre `n-1 + n-2 + ... + 1 = n(n-1)/2` confronti)
- **Spazio**: O(1) — ordinamento in place
- **Swap**: `n-1` swap nel caso pessimo

**Caratteristiche**:

- ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ Semplice da implementare e capire
- ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ Non richiede memoria aggiuntiva (in-place)
- ( ˘︹˘ ) Inefficiente per array grandi (O(n²))
- ( ˘︹˘ ) Non è stabile — l'ordine relativo di elementi uguali potrebbe cambiare

**Esempio**: array `[5, 2, 8, 1, 9]`

- Iter 1: trova 9, swap con indice 4 → `[5, 2, 8, 1, 9]` (nessun cambio, è già al posto)

- Iter 2: trova 8, swap con indice 3 → `[5, 2, 1, 8, 9]`

- Iter 3: trova 5, swap con indice 2 → `[1, 2, 5, 8, 9]`

- Iter 4: trova 2, swap con indice 1 → `[1, 2, 5, 8, 9]`

- Iterazione finale: array ordinato

**Codice**:

```c
void selection_sort(int *V, int N, int **perm)
{
    int iter, count, count_of_max;

    *perm = (int*)malloc(sizeof(int)*N);

    for(count = 0; count < N; count ++)
    {
        (*perm)[count]=count;
    }

    for(iter = 0; iter < N-1, iter++)
    {
        for(count = 1; count_of_max = 0; count < N-iter; count++)
        {
            if(V[(*perm)[count_of_max]]< V[(*perm)[count]])
            {
                count_of_max = count;
            }
        }

        swap(*perm, count, count_of_max);
    }
}

void swap(int *V, int n1, int n2)
{
    int tmp;
    tmp = V[n1];
    V[n1] = V[n2];
    V[n2] = tmp;
}
```

## Bubblesort

**Ordinamento per affioramento a bolla** (bubble sort)

Bubblesort è un algoritmo di ordinamento semplice che ripetutamente attraversa la lista, confronta elementi adiacenti e li scambia se sono nell'ordine sbagliato. L'algoritmo prende il nome dal fatto che gli elementi più grandi "affiorano" verso la fine dell'array, come bolle in acqua.

### Principio

Ad ogni passata, l'algoritmo confronta ogni coppia di elementi adiacenti e li scambia se il primo è maggiore del secondo. Dopo `k` passate complete, i `k` elementi più grandi sono già nelle loro posizioni finali (ordinati) alla fine dell'array.

### Algoritmo (ordinamento crescente)

1. **Passata esterna**: Per `i` da 0 a `n-2`
2. **Passata interna**: Per `j` da 0 a `n-1-i`
   - Confronta `A[j]` con `A[j+1]`
   - Se `A[j] > A[j+1]`, scambia i due elementi
3. **Ottimizzazione**: Se in una passata non ci sono stati swap, l'array è già ordinato (uscita anticipata)

### Complessità

* **Tempo (caso pessimo)**: O(n²) — quando l'array è ordinato in ordine inverso
* **Tempo (caso medio)**: O(n²) — nella maggior parte dei casi
* **Tempo (caso migliore)**: O(n) — quando l'array è già ordinato (con ottimizzazione)
* **Spazio**: O(1) — ordinamento in place
* **Numero di confronti**: esattamente `(n-1) + (n-2) + ... + 1 = n(n-1)/2`

### Caratteristiche

- ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ Molto semplice da implementare
- ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ Non richiede memoria aggiuntiva (in-place)
- ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ **È stabile** — mantiene l'ordine relativo di elementi uguali
- ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ Può terminare anticipatamente se l'array diventa ordinato
- ( ˘︹˘ ) Molto inefficiente per array grandi (O(n²))
- ( ˘︹˘ ) Peggiore di Selection Sort in pratica (più swap, meno stabile di altri algoritmi)

### Esempio passo-passo: array `[5, 2, 8, 1, 9]`

**Passata 1**: Confronta coppie adiacenti, il massimo (9) affonda in fondo
- `[5, 2, 8, 1, 9]` confronta 5 e 2 → scambia → `[2, 5, 8, 1, 9]`
- `[2, 5, 8, 1, 9]` confronta 5 e 8 → no swap → `[2, 5, 8, 1, 9]`
- `[2, 5, 8, 1, 9]` confronta 8 e 1 → scambia → `[2, 5, 1, 8, 9]`
- `[2, 5, 1, 8, 9]` confronta 8 e 9 → no swap → `[2, 5, 1, 8, 9]`
- **Fine passata 1**: `[2, 5, 1, 8, 9]` — 9 è a posto

**Passata 2**: 8 affonda verso la sua posizione (n-2)
- `[2, 5, 1, 8, 9]` confronta 2 e 5 → no swap
- `[2, 5, 1, 8, 9]` confronta 5 e 1 → scambia → `[2, 1, 5, 8, 9]`
- `[2, 1, 5, 8, 9]` confronta 5 e 8 → no swap
- **Fine passata 2**: `[2, 1, 5, 8, 9]`

**Passata 3**:
- `[2, 1, 5, 8, 9]` confronta 2 e 1 → scambia → `[1, 2, 5, 8, 9]`
- `[1, 2, 5, 8, 9]` confronta 2 e 5 → no swap
- **Fine passata 3**: `[1, 2, 5, 8, 9]`

**Passata 4**:
- `[1, 2, 5, 8, 9]` — nessun swap, array ordinato!

### Codice C

```c
// Bubblesort semplice
void bubble_sort(int *V, int N)
{
    int i, j, tmp;
    
    for (i = 0; i < N - 1; i++)
    {
        for (j = 0; j < N - 1 - i; j++)
        {
            if (V[j] > V[j + 1])
            {
                // Swap
                tmp = V[j];
                V[j] = V[j + 1];
                V[j + 1] = tmp;
            }
        }
    }
}
```

```c
// Bubblesort con ottimizzazione (uscita anticipata)
void bubble_sort_optimized(int *V, int N)
{
    int i, j, tmp;
    int swapped;
    
    for (i = 0; i < N - 1; i++)
    {
        swapped = 0;  // Flag per controllare se c'è stato almeno uno swap
        
        for (j = 0; j < N - 1 - i; j++)
        {
            if (V[j] > V[j + 1])
            {
                tmp = V[j];
                V[j] = V[j + 1];
                V[j + 1] = tmp;
                swapped = 1;
            }
        }
        
        // Se nessuno swap, l'array è già ordinato
        if (!swapped)
            break;
    }
}
```

### Confronto con Selection Sort

| Aspetto | Bubblesort | Selection Sort |
|---------|-----------|-----------------|
| **Complessità** | O(n²) in tutti i casi | O(n²) in tutti i casi |
| **Stabilità** | ✓ Stabile | ✗ Non stabile |
| **Numero swap** | Molti (peggio) | Pochi (migliore) |
| **Caso migliore** | O(n) con ottimizzazione | O(n²) sempre |
| **Pratica** | Lento, evitare | Migliore di bubble, ma ancora lento |
| **Uso educativo** | Buono per imparare | Buono per imparare confronti/swap |

### Quando usare Bubblesort

- **Da evitare** in produzione per array grandi
- **Accettabile** per array molto piccoli (< 50 elementi)
- **Utile** solo a scopo educativo per comprendere algoritmi di ordinamento
- **Preferire** algoritmi come Quicksort (O(n log n) medio), Mergesort (O(n log n)) o Heapsort (O(n log n)) per usi reali
