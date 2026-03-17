#include <stdlib.h>
#include <stdio.h>

typedef unsigned short int boolean;
#define TRUE 1
#define FALSE 0

struct record {
    int value;
    int next;
};

struct list {
    struct record * buffer;
    int size;
    int first;
    int free;
};

void init(struct list * ptr, int size);
boolean pre_insert(struct list * ptr, int value);
boolean suf_insert(struct list * ptr, int value);
boolean ord_insert(struct list * ptr, int value);
boolean pre_remove(struct list * ptr, int * value);
boolean suf_remove(struct list * ptr, int * value);
boolean ord_remove(struct list * ptr, int target);
void visit(struct list * ptr);
boolean search(struct list * ptr, int target);

int main() {
    struct list ptr;
    int size = 10;
    int value;

    init(&ptr,size);

    // test pre_insert
    pre_insert(&ptr, 7);
    pre_insert(&ptr, 5);
    pre_insert(&ptr, 3);
    pre_insert(&ptr, 1);

    visit(&ptr);

    // test suf_insert
    suf_insert(&ptr, 8);

    visit(&ptr);

    // test ord_insert
    ord_insert(&ptr, 4);
    ord_insert(&ptr, 0);
    ord_insert(&ptr, 9);
    visit(&ptr);

    // test search
    if ( search(&ptr,4) )
        printf("\nSearch termined with success!");
    else
        printf("\nSearch termined without success!");

    // test pre-remove
    pre_remove(&ptr,&value);
    printf("\nValue %d has been removed from the list",value);
    visit(&ptr);

    // test suf-remove
    suf_remove(&ptr,&value);
    printf("\nValue %d has been removed from the list",value);
    visit(&ptr);

    // test ord-remove
    ord_remove(&ptr,1);
    visit(&ptr);
    ord_remove(&ptr,8);
    visit(&ptr);
    ord_remove(&ptr,5);
    visit(&ptr);
    ord_remove(&ptr,7);
    visit(&ptr);
    ord_remove(&ptr,3);
    visit(&ptr);
    suf_remove(&ptr,&value);
    printf("\nValue %d has been removed from the list",value);
    visit(&ptr);
    suf_remove(&ptr,&value);
    printf("\nValue %d has been removed from the list",value);
    visit(&ptr);

    printf("\n");
    //system("pause");
    return 0;
}

void init(struct list * ptr, int size)
{
    int i;
    ptr->buffer = (struct record *)malloc(sizeof(struct record)*size);
    ptr->size = size;
    ptr->first = size;
    ptr->free = 0;
    for (i=0;i<size;i++)
        ptr->buffer[i].next = i+1;
}

void visit(struct list * ptr)
{
    int position;
    printf("\nList: ");
    position = ptr->first;
    while( position != ptr->size ) {
        printf("%d ",ptr->buffer[position].value);
        position = ptr->buffer[position].next;
    }
}

boolean pre_insert(struct list * ptr, int value)
{
    int moved;

    if ( ptr->free != ptr->size ) { // not full
        printf("\ninsert values %d",value);
        moved = ptr->free;
        ptr->free = ptr->buffer[ptr->free].next;
        // insert new value
        ptr->buffer[moved].value = value;
        ptr->buffer[moved].next = ptr->first;
        ptr->first = moved;
        return TRUE;
    }
    return FALSE;
}

boolean suf_insert(struct list * ptr, int value)
{
    int moved, * position;

    if ( ptr->free != ptr->size ) { // not full
        printf("\ninsert values %d",value);
        moved = ptr->free;
        ptr->free = ptr->buffer[ptr->free].next;
        position = &(ptr->first);
        while ( *position != ptr->size )
            position = &(ptr->buffer[*position].next);
        // insert new value
        ptr->buffer[moved].value = value;
        ptr->buffer[moved].next = ptr->size;
        *position = moved;
        return TRUE;
    }
    return FALSE;
}

boolean ord_insert(struct list * ptr, int value)
{
    boolean found = FALSE;
    int moved, * position;

    if ( ptr->free != ptr->size ) { // lista non piena
        printf("\ninsert values %d",value);
        moved = ptr->free;
        ptr->free = ptr->buffer[ptr->free].next;
        position = &(ptr->first);
        while ( *position != ptr->size && ptr->buffer[*position].value < value )
            position = &(ptr->buffer[*position].next);
        // insert
        ptr->buffer[moved].value = value;
        ptr->buffer[moved].next = *position;
        *position = moved;
        return TRUE;
    }
    return FALSE;
}

boolean pre_remove(struct list * ptr, int * value)
{
    int moved;

    if ( ptr->first != ptr->size ) { // not empty
        // make available to the caller the value which is removed
        moved = ptr->first;
        *value = ptr->buffer[ptr->first].value;
        ptr->first = ptr->buffer[ptr->first].next;
        ptr->buffer[moved].next = ptr->free;
        ptr->free = moved;
        return TRUE;
    }
    else
        return FALSE;
}

boolean suf_remove(struct list * ptr, int * value)
{
    int moved, * position;

    if ( ptr->first != ptr->size ) { // not empty
        position = &(ptr->first);
        // move to the last element of the list
        while ( ptr->buffer[*position].next != ptr->size )
            position = &(ptr->buffer[*position].next);
        // make available to the caller the value which is removed
        moved = *position;
        *value = ptr->buffer[*position].value;
        *position = ptr->buffer[moved].next;
        ptr->buffer[moved].next = ptr->free;
        ptr->free = moved;
        return TRUE;
    }
    else
        return FALSE;
}

// remove the first element of the list with value equal to the target
boolean ord_remove(struct list * ptr, int target)
{
    int moved, * position;
    boolean found = FALSE;

    if ( ptr->first != ptr->size ) { // not empty
        position = &ptr->first;
        // move to the last element of the list
        while ( ptr->buffer[*position].next != ptr->size && found == FALSE ) {
            if (ptr->buffer[*position].value == target)
                found = TRUE;
            else
                position = &(ptr->buffer[*position].next);
        }
        if ( found == TRUE ) {
            moved = *position;
            *position = ptr->buffer[moved].next;
            ptr->buffer[moved].next = ptr->free;
            ptr->free = moved;
            printf("\nValue %d has been removed from the list", target);
        }
    }
    return found;
}

boolean search(struct list * ptr, int target)
{
    boolean found = FALSE;
    int position;

    position = ptr->first;
    while ( position != ptr->size && found == FALSE ) {
        if ( ptr->buffer[position].value == target )
            found = TRUE;
        else
            position = ptr->buffer[position].next;
    }
    return found;
}
