#include <stdlib.h>
#include <stdio.h>

typedef unsigned short int boolean;
#define TRUE 1
#define FALSE 0

struct list {
    int value;
    struct list * next_ptr;
};

void init(struct list ** ptr);
boolean pre_insert(struct list **ptrptr, int value);
boolean suf_insert(struct list **ptrptr, int value);
boolean ord_insert(struct list **ptrptr, int value);
boolean pre_remove(struct list **ptrptr, int * value);
boolean suf_remove(struct list **ptrptr, int * value);
boolean ord_remove(struct list **ptrptr, int target);
void visit(struct list *ptr);
void visit_back(struct list * ptr);
boolean search(struct list * ptr, int target);
boolean clone(struct list * src_ptr, struct list ** dst_ptr);
boolean clone2(struct list * src_ptr, struct list ** dst_ptr);

int main() {
    struct list * ptr, * dst_ptr, * dst2_ptr;
    int value;

    // init the list
    init(&ptr);

    // test pre-insert
    pre_insert(&ptr, 5);
    pre_insert(&ptr, 3);
    pre_insert(&ptr, 1);

    visit(ptr);

    // test suf-insert
    suf_insert(&ptr, 6);
    suf_insert(&ptr, 8);

    visit(ptr);

    // test ord-insert
    ord_insert(&ptr, 0);
    ord_insert(&ptr, 7);

    visit(ptr);

    // test remove
    pre_remove(&ptr,&value);
    printf("\nValue %d has been removed from the list",value);
    suf_remove(&ptr,&value);
    printf("\nValue %d has been removed from the list",value);
    ord_remove(&ptr,3);
    ord_remove(&ptr,7);

    visit(ptr);

    // test search
    if ( search(ptr,10) )
        printf("\nSearch termined with success!");
    else
        printf("\nSearch termined without success!");

    // test clone
    clone(ptr,&dst_ptr);
    visit(dst_ptr);
    // test clone2
    clone2(ptr,&dst2_ptr);
    visit(dst2_ptr);

    // test backward visit
    visit_back(dst2_ptr);

    printf("\n");
    //system("pause");
    return 0;
}

void init(struct list ** ptr)
{
    *ptr = NULL;
}

boolean pre_insert(struct list **ptrptr, int value)
{
    struct list * tmp_ptr;
    tmp_ptr = (struct list *)malloc(sizeof(struct list));
    if ( tmp_ptr != NULL ) {
        tmp_ptr->value = value;
        tmp_ptr->next_ptr = *ptrptr;
        *ptrptr = tmp_ptr;
        return TRUE;
    }
    else
        return FALSE;

}

boolean suf_insert(struct list **ptrptr, int value)
{
    while( *ptrptr != NULL )
        ptrptr = &((*ptrptr)->next_ptr);
    if ( pre_insert(ptrptr,value) )
        return TRUE;
    else
        return FALSE;
}

boolean ord_insert(struct list **ptrptr, int value)
{
    while( *ptrptr != NULL && (*ptrptr)->value < value )
        ptrptr = &((*ptrptr)->next_ptr);
    if ( pre_insert(ptrptr,value) )
        return TRUE;
    else
        return FALSE;
}

boolean pre_remove(struct list **ptrptr, int * value)
{
    struct list * tmp_ptr;

    if ( *ptrptr != NULL ) {
        tmp_ptr = *ptrptr;
        *value = tmp_ptr->value;
        *ptrptr = (*ptrptr)->next_ptr;
        free(tmp_ptr);
        return TRUE;
    }
    else
        return FALSE;
}

boolean suf_remove(struct list ** ptrptr, int * value)
{
    if ( *ptrptr != NULL ) {
        while( (*ptrptr)->next_ptr != NULL ) {
            ptrptr = &((*ptrptr)->next_ptr);
        }
        pre_remove(ptrptr,value);
        return TRUE;
    }
    else
        return FALSE;
}

boolean ord_remove(struct list ** ptrptr, int target)
{
    int value;
    boolean found = FALSE;

    if ( *ptrptr != NULL ) {
        while( *ptrptr != NULL && found == FALSE ) {
            if ((*ptrptr)->value == target) {
                pre_remove(ptrptr, &value);
                printf("\nValue %d has been removed from the list",value);
                found = TRUE;
            }
            else
                ptrptr = &((*ptrptr)->next_ptr);
        }
    }
    return found;
}

void visit(struct list * ptr)
{
    printf("\nList: ");
    while ( ptr != NULL ) {
        printf("%d ", ptr->value);
        ptr = ptr->next_ptr;
    }
}

// backward visit of the list. Elements are printed in reverse order
void visit_back(struct list * ptr)
{
    struct list * tmp_ptr;

    init(&tmp_ptr);
    while ( ptr != NULL ) {
        pre_insert(&tmp_ptr,ptr->value);
        ptr = ptr->next_ptr;
    }
    visit(tmp_ptr);
}

boolean search(struct list * ptr, int target)
{
    boolean found = FALSE;

    while( ptr != NULL && found == FALSE ) {
        if ( ptr->value == target )
            found = TRUE;
        else
            ptr = ptr->next_ptr;
    }
    return found;
}

boolean clone(struct list * src_ptr, struct list ** dst_list)
{
    boolean is_correct = TRUE;
    init(dst_list);
    // insert all the elements of the source list in the destination list
    while ( src_ptr != NULL && is_correct == TRUE ) {
        is_correct = suf_insert(dst_list,src_ptr->value);
        src_ptr = src_ptr->next_ptr;
    }
    return is_correct;
}

// clone with linear cost
boolean clone2(struct list * src_ptr, struct list ** dst_ptr)
{
    boolean is_correct = TRUE;
    init(dst_ptr);
    // insert all the elements of the source list in the destination list
    while ( src_ptr != NULL && is_correct == TRUE ) {
        is_correct = suf_insert(dst_ptr,src_ptr->value);
        // advance the pointer to the next_ptr filed of the last element of the list
        dst_ptr = &((*dst_ptr)->next_ptr);
        src_ptr = src_ptr->next_ptr;
    }
    return is_correct;
}
