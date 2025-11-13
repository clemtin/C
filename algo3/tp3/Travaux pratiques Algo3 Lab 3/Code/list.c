/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)

 Implantation du TAD List vue en cours.
 */
/*-----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

typedef struct s_LinkedElement {
    int value;
    struct s_LinkedElement* previous;
    struct s_LinkedElement* next;
} LinkedElement;

/* Utilisation d’un sentinelle :
   Le sentinelle est un maillon spécial dont les pointeurs `next` et `previous`
   bouclent sur la tête et la queue de la liste.
*/
struct s_List {
    LinkedElement* sentinel;
    int size;
};

/*-----------------------------------------------------------------*/

typedef struct s_SubList{
	struct s_LinkedElement* head;
    struct s_LinkedElement* tail;
} SubList;

List* list_create(void) {
    // On alloue un seul bloc pour la structure et son sentinelle
    List* l = malloc(sizeof(struct s_List) + sizeof(struct s_LinkedElement));
    if (!l) return NULL;

    l->sentinel = (LinkedElement*)(l + 1);

    l->sentinel->previous = l->sentinel;
    l->sentinel->next = l->sentinel;
    l->size = 0;

    return l;
}

/*-----------------------------------------------------------------*/

List* list_push_back(List* l, int v) {
    LinkedElement* e = malloc(sizeof(LinkedElement));
    if (!e) return l;

    e->value = v;
    e->next = l->sentinel;
    e->previous = l->sentinel->previous;

    l->sentinel->previous->next = e;
    l->sentinel->previous = e;

    ++(l->size);
    return l;
}

/*-----------------------------------------------------------------*/

List* list_push_front(List* l, int v) {
    LinkedElement* e = malloc(sizeof(LinkedElement));
    if (!e) return l;

    e->value = v;
    e->next = l->sentinel->next;
    e->previous = l->sentinel;

    l->sentinel->next->previous = e;
    l->sentinel->next = e;

    ++(l->size);
    return l;
}

/*-----------------------------------------------------------------*/

List* list_pop_front(List* l) {
    assert(!list_is_empty(l));

    LinkedElement* e = l->sentinel->next;
    l->sentinel->next = e->next;
    e->next->previous = l->sentinel;

    free(e);
    --(l->size);
    return l;
}

/*-----------------------------------------------------------------*/

List* list_pop_back(List* l) {
    assert(!list_is_empty(l));

    LinkedElement* e = l->sentinel->previous;
    e->previous->next = l->sentinel;
    l->sentinel->previous = e->previous;

    free(e);
    --(l->size);
    return l;
}

/*-----------------------------------------------------------------*/

List* list_insert_at(List* l, int p, int v) {
    assert(p >= 0 && p <= l->size);

    LinkedElement* current = l->sentinel->next;
    while (p--) current = current->next;

    LinkedElement* e = malloc(sizeof(LinkedElement));
    if (!e) return l;

    e->value = v;
    e->next = current;
    e->previous = current->previous;

    current->previous->next = e;
    current->previous = e;

    ++(l->size);
    return l;
}

/*-----------------------------------------------------------------*/

List* list_remove_at(List* l, int p) {
    assert(p >= 0 && p < l->size);

    LinkedElement* current = l->sentinel->next;
    while (p--) current = current->next;

    current->previous->next = current->next;
    current->next->previous = current->previous;

    free(current);
    --(l->size);
    return l;
}

/*-----------------------------------------------------------------*/

int list_front(const List* l) {
    assert(!list_is_empty(l));
    return l->sentinel->next->value;
}

/*-----------------------------------------------------------------*/

int list_back(const List* l) {
    assert(!list_is_empty(l));
    return l->sentinel->previous->value;
}

/*-----------------------------------------------------------------*/

int list_at(const List* l, int p) {
    assert(!list_is_empty(l) && p >= 0 && p < l->size);

    LinkedElement* current = l->sentinel->next;
    while (p--) current = current->next;

    return current->value;
}

/*-----------------------------------------------------------------*/

bool list_is_empty(const List* l) {
    return (l == NULL || l->size == 0);
}

/*-----------------------------------------------------------------*/

int list_size(const List* l) {
    return (l ? l->size : 0);
}

/*-----------------------------------------------------------------*/

List* list_map(List* l, ListFunctor f, void* environment) {
    LinkedElement* current = l->sentinel->next;
    while (current != l->sentinel) {
        current->value = f(current->value, environment);
        current = current->next;
    }
    return l;
}

/*-----------------------------------------------------------------*/


/*-----------------------------------------------------------------*/

void list_delete(ptrList* l) {
    if (!l || !*l) return;

    LinkedElement* current = (*l)->sentinel->next;
    while (current != (*l)->sentinel) {
        LinkedElement* next = current->next;
        free(current);
        current = next;
    }
    free(*l);
    *l = NULL;
}

List* list_sort(List* l, OrderFunctor f) {
    (void)f; // pas encore implémenté
    return l;
}


SubList list_split(SubList l){
	if(!l.head || l.tail == l.head)
		return l;

	LinkedElement* start = l.head;
	LinkedElement* end = l.tail;

	while(start->next!=end && start->next != end->previous){
		start = start->next;
		end = end->previous;

	}

	SubList new;
	new.head=start;
	new.tail=end;
	return new;
}	


SubList list_merge(SubList leftlist, SubList rightlist, OrderFunctor f){
    SubList newS;
    newS.head = NULL;
    newS.tail = NULL;

    LinkedElement* left = leftlist.head;
    LinkedElement* right = rightlist.head;
    LinkedElement* result_head = NULL;
    LinkedElement* result_tail = NULL;

	
	while (left !=NULL && right != NULL){
		if(f(left->value,right->value)){
			// cas left 


		}

		else{

			// cas right
		}
	}
	
	

}