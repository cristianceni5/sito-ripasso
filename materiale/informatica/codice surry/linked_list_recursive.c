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
boolean suf_insert_r(struct list **ptrptr, int value);
boolean ord_insert_r(struct list **ptrptr, int value);
boolean pre_remove(struct list **ptrptr, int * value);
boolean suf_remove_r(struct list **ptrptr, int * value);
boolean ord_remove_r(struct list **ptrptr, int target);
void visit_r(struct list *ptr);
void visit_back_r(struct list * ptr);
boolean search_r(struct list * ptr, int target, struct list ** ptrptr);
boolean search_r_return(struct list * ptr, int target);
boolean clone_r(struct list * src_ptr, struct list ** dst_ptr);
void sum_r_back(struct list * ptr, int * sum);
int sum_r_return(struct list * ptr);

int main() {
    struct list * ptr, * dst_ptr, * found_ptr;
    int value;

    // init the list
    init(&ptr);

    // test pre-insert
    pre_insert(&ptr, 5);
    pre_insert(&ptr, 3);
    pre_insert(&ptr, 1);

    printf("\nList: ");
    visit_r(ptr);

    // test suf-insert
    suf_insert_r(&ptr, 6);
    suf_insert_r(&ptr, 8);

    printf("\nList: ");
    visit_r(ptr);

    // test ord-insert
    ord_insert_r(&ptr, 0);
    ord_insert_r(&ptr, 7);
    printf("\nList: ");
    visit_r(ptr);

    // test remove
    pre_remove(&ptr,&value);
    printf("\nValue %d has been removed from the list",value);
    suf_remove_r(&ptr,&value);
    printf("\nValue %d has been removed from the list",value);
    printf("\nList: ");
    visit_r(ptr);
    if ( ord_remove_r(&ptr,3) )
        printf("\nValue %d has been removed from the list",3);
    printf("\nList: ");
    visit_r(ptr);
    if ( ord_remove_r(&ptr,7) )
        printf("\nValue %d has been removed from the list",3);
    printf("\nList: ");
    visit_r(ptr);

    // test search
    value = 5;
    if ( search_r(ptr,value,&found_ptr) )
        // the formatting string %p is used to print an address (in Hex form)
        printf("\nSearch of value %d terminateed with success! The address of the target element is %p",value,found_ptr);
    else
        printf("\nSearch of value %d terminated without success!",value);

    // test search return
    value = 5;
    if ( search_r_return(ptr,value) )
        // the formatting string %p is used to print an address (in Hex form)
        printf("\nSearch of value %d terminated with success!",value);
    else
        printf("\nSearch of value %d terminated without success!",value);

    // test recursive clone
    clone_r(ptr,&dst_ptr);
    printf("\nList cloned: ");
    visit_r(dst_ptr);

    // test backward visit
    printf("\nList cloned backward: ");
    visit_back_r(dst_ptr);

    // test recursive sum
    sum_r_back(ptr,&value);
    printf("\nThe sum of the list elements is %d",value);

    // test recursive sum with return value
    value = sum_r_return(ptr);
    printf("\nThe sum of the list elements is %d",value);

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

// suf insert in recursive form
boolean suf_insert_r(struct list **ptrptr, int value)
{
    if( *ptrptr != NULL )
        return suf_insert_r(&((*ptrptr)->next_ptr), value);
    else
        return pre_insert(ptrptr,value);
}

// ordered insert in recursive form
boolean ord_insert_r(struct list **ptrptr, int value)
{
    if( *ptrptr != NULL && (*ptrptr)->value < value )
        return ord_insert_r(&((*ptrptr)->next_ptr),value);
    else
        return pre_insert(ptrptr,value);
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

// suf remove in recursive form
boolean suf_remove_r(struct list ** ptrptr, int * value)
{
    if ( *ptrptr != NULL ) {
        if( (*ptrptr)->next_ptr != NULL ) {
            return suf_remove_r(&((*ptrptr)->next_ptr),value);
        }
        else
            return pre_remove(ptrptr,value);
    }
    else
        return FALSE;
}

// ordered remove in recursive form
boolean ord_remove_r(struct list ** ptrptr, int target)
{
    int value;

    if ( *ptrptr != NULL ) {
        if ((*ptrptr)->value == target)
            return pre_remove(ptrptr, &value);
        else
            return ord_remove_r(&((*ptrptr)->next_ptr), target);
    }
    return FALSE;
}

// visit in recursive form
void visit_r(struct list * ptr)
{
    if ( ptr != NULL ) {
        printf("%d ", ptr->value);
        // call the function itself on the next list element
        visit_r(ptr->next_ptr);
    }
}

// backward visit in recursive form
void visit_back_r(struct list * ptr)
{
    if ( ptr != NULL ) {
        // call the function itself on the next list element
        visit_back_r(ptr->next_ptr);
        printf("%d ", ptr->value);
    }
}

// search in recursive form. Returns the pointer to the target element
// of the list in the formal parameter list
boolean search_r(struct list * ptr, int target, struct list ** ptrptr)
{
    if( ptr != NULL ) {
        if ( ptr->value == target ) {
            // return the address to the element of the list with
            // the field value equal to the target
            *ptrptr = ptr;
            return TRUE;
        }
        else
            return search_r(ptr->next_ptr,target,ptrptr);
    }
    else
        return FALSE;
}

// search in recursive form
boolean search_r_return(struct list * ptr, int target)
{
    if( ptr != NULL ) {
        if ( ptr->value == target )
            return TRUE;
        else
            return search_r_return(ptr->next_ptr,target);
    }
    else
        return FALSE;
}

// clone the list using a recursive form. The function has linear cost
boolean clone_r(struct list * src_ptr, struct list ** dst_list)
{
    // insert all the elements of the source list in the destination list
    if ( src_ptr != NULL ) {
        // from the end of the source list insert elements in the destination list
        // using pre insert
        clone_r(src_ptr->next_ptr,dst_list);
        return pre_insert(dst_list,src_ptr->value);
    }
    else {
        // first arrive to the end of the source list and initialize the
        // destination list
        init(dst_list);
        return TRUE;
    }
}

void sum_r_back(struct list * ptr, int * sum)
{
    if( ptr != NULL ) {
        sum_r_back(ptr->next_ptr,sum);
        *sum += ptr->value;
    }
    else
        // initialize the sum
        *sum = 0;
}

int sum_r_return(struct list * ptr)
{
    if( ptr != NULL )
        // sum and propagate
        return ptr->value + sum_r_return(ptr->next_ptr);
    else
        // initialize the sum
        return 0;
}