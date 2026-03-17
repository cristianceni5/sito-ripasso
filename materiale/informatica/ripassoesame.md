# Guida allo Studio del C: Esempi e Teoria (dal Libro)

Questo documento analizza i tuoi script di esempio (.c) e i file del parziale (.pdf) e li collega direttamente alle definizioni formali, alle categorie sintattiche e alle produzioni BNF del libro *Fondamenti di Programmazione* (Sezioni 1.3, 1.4 e 1.5, fino a pag. 112), con un focus speciale sugli argomenti del parziale:

---

## 0. Concetti Chiave del Parziale

### Sintassi vs. Semantica (Sez. 1.4.1 e 1.4.6)

- **Sintassi (BNF)**: È la grammatica (la "forma"). L'albero sintattico (costruito con `<decl>`, `<expr>`, `<var>`, ecc.) verifica se la frase è legale.  
- **Semantica (Valori)**: È il significato (valore calcolato) di ogni nodo. L'esame chiede di annotare l'albero sintattico con i valori.

#### Esempio (da Fig. 1.11 del libro)

Se `a = 5`, `b = 10` e l'espressione è `a + b`, l'albero annotato sarebbe:

```
  a     +     b
  |     |     |
<var>   |   <var>
val:5   |   val:10
  |     |     |
<expr> <op2> <expr>
val:5   |   val:10
  |     |     |
   \    |    /
    \   |   /
     <expr>
     val:15
```

---

## 0.5 Regole di Precedenza (Sintesi)

### Per le DICHIARAZIONI (<decl>) (Sez. 1.5.4)

Priorità (Alta → Bassa):

1. Parentesi `<decl>` — forza la priorità.  
2. Suffissi `[]` e `()` — letti da sinistra a destra.  
3. Prefissi `*` — letti da destra a sinistra.

**Esempi:**

```c
int *A[10];     // A -> A[10] (Array) -> *A[10] (Puntatore)
int (*A)[10];   // A -> *A (Puntatore) -> (*A)[10] (Array)
```

### Per le ESPRESSIONI (<expr>) (Sez. 1.5.2)

Priorità (Alta → Bassa):

1. Parentesi `()`, accesso `[]`, chiamata `()`, accesso `.` e `->`
2. Unari: `!`, `*`, `&`, `++`, `--`, `sizeof`
3. Moltiplicativi: `*`, `/`, `%`
4. Additivi: `+`, `-`
5. Relazionali: `<`, `>`, `<=`, `>=`
6. Uguaglianza: `==`, `!=`
7. Logici: `&&` poi `||`
8. Assegnamento: `=`, `+=`, `-=` (priorità bassissima)

**Esempi:**

```c
*p = a + b;    // a + b (Addizione) -> *p = ... (Assegnamento)
*p + a;        // *p (Dereferenziazione) -> ... + a (Addizione)
```

---

## 1. Puntatori (Sezione 1.5.3)

Un puntatore è una variabile il cui valore è l'indirizzo di un'altra variabile.

### Esempio 1: Puntatori Base (da `testPuntatori.c`)

```c
#include <stdio.h>

int main()
{
    printf("===Test dei puntatori Ceni dhn===\n");

    int x = 50;
    int *ptrX = &x; // Puntatore a x, che con & prende il valore dell'indirizzo di x

    printf("Valore di x: %d\n", x);
    printf("Indirizzo di x: %p\n", &x);
    printf("Indirizzo di ptrX: %p\n", ptrX);
    printf("Valore puntato da ptrX: %d\n", *ptrX);
}
```

#### Teoria

1. **Dichiarazione (`int *ptrX`):**  
   Produzione: `<decl> ::= * <decl>`  
   La parte `*ptrX` è il `<decl>`. L'albero sintattico si costruisce riducendo `ptrX` a `<identifier>` e poi combinandolo con `*`.

2. **Operatore di Indirizzo (`&x`):**  
   Produzione: `<expr> ::= &<var>`  
   Restituisce l'indirizzo della variabile.

3. **Dereferenziazione (`*ptrX`):**  
   Produzione: `<var> ::= *<expr>`  
   Significa “la variabile puntata da `ptrX`”.

---

## 2. Array (Sezione 1.5.4)

Un array è un insieme di variabili dello stesso tipo, memorizzate in locazioni contigue.

### Esempio 2a: Array 1D e 2D (da `testArray.c`)

```c
#include <stdio.h>

int main()
{
    printf("===Test degli array Ceni dhn===\n");

    int arrayCeni[] = {10, 5, 20, 30, 40};
    for(int i = 0; i < 5; i++)
        printf("Elemento %d: %d\n", i, arrayCeni[i]);

    int matrice[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for(int r = 0; r < 3; r++)
        for(int c = 0; c < 3; c++)
            printf("Elemento [%d][%d]: %d\n", r, c, matrice[r][c]);

    return 0;
}
```

#### Teoria

1. **Dichiarazione Array:** `<decl> ::= <decl>[<const>]`  
   In `matrice[3][3]`, la regola è applicata ricorsivamente: “array di 3 array di 3 int”.  
2. **Accesso all’Array:** `<var> ::= <expr1>[<expr2>]`  
   `matrice[riga][colonna]` è un accesso annidato.

### Esempio 2b: Array e Puntatori (da `testPuntatori.c`)

```c
int y[4] = {1, 2, 3, 4};

printf("Indirizzo dell'array: %p\n", y);
printf("Indirizzo del primo elemento: %p\n", &y[0]);
printf("Valore y: %d\n", *y);
```

#### Teoria

- Il nome dell’array (`y`) è un valore costante: l’indirizzo del primo elemento (`&y[0]`).  
- `y[i]` ≡ `*(y + i)`, quindi `*y` ≡ `y[0]`.

---

## 3. Espressioni (Sezione 1.5.2)

Le espressioni `<expr>` sono i mattoni fondamentali del linguaggio.

### 3.1 Operatori ++ e --

```c
int a = 5;
int y = ++a; // prefisso
int z = a++; // suffisso
```

- `++a`: restituisce il valore già incrementato.  
- `a++`: restituisce il valore originale, prima dell’incremento.

### 3.2 Operatore sizeof

```c
sizeof(arrayCeni) / sizeof(arrayCeni[0]);
```

Restituisce la dimensione in byte dell’operando.  
Esempio: `20 / 4 = 5 elementi`.

---

## 4. Funzioni (Sezione 1.5.6)

Una funzione è un costrutto che partiziona il codice in moduli riutilizzabili.

### Esempio 3: Definizione e Chiamata (da `testFunzioni.c`)

```c
#include <stdio.h>

double calcoloTensione(double corrente, double resistenza)
{
    double calc = corrente * resistenza;
    return calc;
}

void ciao()
{
    printf("Ciao\n");
}

int main()
{
    double corrente = 5.0, resistenza = 10.0;
    double tensione = calcoloTensione(corrente, resistenza);
    printf("La tensione calcolata e': %.2f Volt\n", tensione);
    ciao();
}
```

#### Teoria

1. **Definizione:** `<function_definition> ::= <type><decl>(<formal_parameter_list>) {...}`  
2. **Chiamata:** `<expr> ::= <expr1>(<actual_parameter_list>)`  
3. **Parametri formali vs. attuali:** nomi nella definizione vs. valori passati nella chiamata.

---

## 5. Dati Strutturati (Sezione 1.5.7)

Una `struct` è un insieme di variabili di tipo diverso.

### Esempio 4a: Accesso Diretto (da `testStruct.c`)

```c
#include <stdio.h>

struct Persona {
    char nome[50];
    int eta;
    int lunghezzaPipo;
};

int main() {
    struct Persona persona1;
    persona1.eta = 25;
    persona1.lunghezzaPipo = 15;

    printf("Eta': %d\n", persona1.eta);
    printf("Lunghezza Pipo: %d\n", persona1.lunghezzaPipo);
}
```

### Esempio 4b: Accesso Tramite Puntatore (da `parziale1.c`)

```c
struct Lista {
    int valore;
    int besello;
};

struct Lista lista1;
struct Lista *ptrLista = &lista1;

(*ptrLista).valore += 5;
ptrLista->besello += 10;
```

#### Teoria

- `(*ptrLista).valore`: dereferenziazione esplicita.  
- `ptrLista->besello`: scorciatoia sintattica equivalente.

---

## 6. Istruzioni (Sezione 1.5.5)

Le istruzioni `<statement>` dirigono il flusso del programma.

### Tipologie principali

1. **Istruzione-espressione:** `<statement> ::= <expr>;`  
2. **Blocco:** `{ <statement> }`  
3. **Condizionale:** `if (<expr>) <statement> [else <statement>]`  
4. **Iterative:** `for`, `while`, `do ... while`  
5. **Salto:** `break`, `switch`

### Esempio 5: Albero per `if (i < 4) { printf(...); }`

```
if (i < 4) { printf(...); }
 |
 <expr>
 |
 <statement>
```

### Esempio 6: Albero per `for (i=0; i<4; i++) {...}`

```
for (i=0; i<4; i++) { ... }
 |
 <expr> <expr> <expr> <statement>
```

---

## 7. Allocazione Dinamica (Sezione 1.5.4)

Permette di riservare memoria durante l’esecuzione del programma (heap).

### 7.1 Allocazione Statica

```c
float A[128];
int matrice[3][3];
```

### 7.2 Allocazione Dinamica

```c
float *A;
A = (float *)malloc(128 * sizeof(float));
```

### 7.3 Funzioni Fondamentali

#### malloc

```c
A = (float *)malloc(I * H * sizeof(float));
```

- `sizeof(float)` → numero di byte per tipo.  
- `malloc()` → restituisce un `void *`.  
- `(float *)` → converte in puntatore al tipo corretto.

#### Controllo fallimento

```c
*W = (int*) malloc(sizeof(int) * 2 * N);
if (*W == NULL) return FALSE;
```

#### free

```c
free(A);
```

Serve a liberare la memoria allocata dinamicamente.

### 7.4 Array Statici vs Dinamici

| Tipo | Dichiarazione | Assegnazione | Mutabilità |
|------|----------------|---------------|-------------|
| Statica | `float A[128];` | Fissa | Non modificabile |
| Dinamica | `float *A;` | `A = malloc(...)` | Assegnabile |

---

## 8. Traduzione C in Assembler MIPS (Sezione 1.3)

### 8.1 Concetti Chiave

- Il processore esegue **istruzioni macchina**, non codice C.  
- L’**assembler MIPS** è una rappresentazione simbolica di tali istruzioni.  
- Le variabili sono gestite tramite **registri** ($s0, $t1, ecc.).

### 8.2 Mapping C → MIPS

#### A. Aritmetica e Assegnamento

```asm
add  $s0, $s1, $s2     # a = b + c
addi $s0, $s1, 15      # a = b + 15
```

#### B. Accesso alla Memoria

```asm
lw $s0, 100($0)   # carica valore da memoria
sw $s0, 200($0)   # salva valore in memoria
```

#### C. Controllo del Flusso

```asm
bne $s1, $s2, fine_if  # if (i != j) goto fine_if
j fine_loop            # salto incondizionato
slt $t0, $s1, $t5      # set if less than
```

---

## 8.3 Analisi Esercizio 1 (dal Parziale)

Traduzione di un ciclo `for` C → MIPS:

```c
for (i=1, j=0; i<10; i++) {
    if (V[i] == W[j]) {
        W[j+1]++;
    } else {
        j += 2;
    }
    W[j] = V[i];
    W[j+1] = 1;
}
```

### Codice MIPS

```asm
addi $s0, $0, 1
addi $s1, $0, 0
addi $s2, $0, 500
addi $s3, $0, 540
addi $t0, $0, 10
addi $t1, $0, 1
addi $t2, $0, 2

start_loop:
    slt $t3, $s0, $t0
    beq $t3, $0, fine_loop

    sll $t4, $s0, 2
    addu $t5, $s2, $t4
    lw $t6, 0($t5)

    sll $t4, $s1, 2
    addu $t5, $s3, $t4
    lw $t7, 0($t5)

    bne $t6, $t7, ramo_else

    addi $t3, $s1, 1
    sll $t4, $t3, 2
    addu $t5, $s3, $t4
    lw $t6, 0($t5)
    addi $t6, $t6, 1
    sw $t6, 0($t5)
    j fine_if

ramo_else:
    add $s1, $s1, $t2

fine_if:
    sll $t4, $s1, 2
    addu $t5, $s3, $t4
    sll $t3, $s0, 2
    addu $t4, $s2, $t3
    lw $t6, 0($t4)
    sw $t6, 0($t5)

    addi $t3, $s1, 1
    sll $t4, $t3, 2
    addu $t5, $s3, $t4
    sw $t1, 0($t5)

    addi $s0, $s0, 1
    j start_loop

fine_loop:
```

---

**Fine del documento — Guida allo Studio del C**  
Autore: *Cristian Ceni*
