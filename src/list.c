#include "../include/list.h"
#include "../include/patient.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _node {
    PATIENT *patient;
    struct _node *next;
    struct _node *prev;
} NODE;

typedef struct _list {
    NODE *head;
    NODE *end;
    int size;
} LIST;

// Vamos fazer uma lista duplamente encadeada e nao ordenada

LIST* init_list(){
    LIST* l = (LIST *) calloc(1, sizeof(LIST));
    l->head = NULL;
    l->end = NULL;
    l->size = 0;

    return l;
}


bool is_list_empty(LIST *list){
    if(list->size != 0){
        return false;
    }else{
        return true;
    }
}

int get_list_size(LIST *list){
    return list->size;
}

void add_patient(LIST *list, PATIENT *patient){
    NODE *n = (NODE*) calloc(1, sizeof(NODE));
    n->next = NULL;
    n->patient = patient;

    if(is_list_empty(list) == true){
        list->head = n;
        n->prev = NULL;
    }else {
        list->end->next = n;
        n->prev = list->end;
    }

    list->end = n;

    list->size += 1;
}

PATIENT* get_patient_by_id(LIST *list, int patient_id){
    NODE *p = list->head;

    for(int i = 0; i < list->size; i++){
        if(p == NULL){
            return NULL;
        }

        if(get_patient_id(p->patient) == patient_id){
            return p->patient;
        }

        p = p->next;
    }

    return NULL;
}

PATIENT* get_patient_by_name(LIST *list, char *name){
    NODE *p = list->head;

    for(int i = 0; i < list->size; i++){
        if(p == NULL){
            return NULL;
        }

        if(strcmp(get_patient_name(p->patient), name) == 0){
            return p->patient;
        }

        p = p->next;
    }

    return NULL;
}

void remove_patient(LIST *list, int patient_id){
    NODE* p = list->head;

    for(int i = 0; i < list->size; i++){
        if(p == NULL){
            return;
        }

        if(get_patient_id(p->patient) == patient_id){
            break;
        }

        p = p->next;
    }

    if (p->prev)
        p->prev->next = p->next;
    else
        list->head = p->next;

    if (p->next)
        p->next->prev = p->prev;
    else
        list->end = p->prev;

    list->size -= 1;

    delete_patient(&(p->patient));

    free(p);
}

PATIENT* get_first(LIST *list){
    if(is_list_empty(list)){
        return NULL;
    }

    return list->head->patient;
}

PATIENT* get_last(LIST *list){
    if(is_list_empty(list)){
        return NULL;
    }

    return list->end->patient;
}

void print_list(LIST *list){
    NODE *p = list->head;

    if(is_list_empty(list)){
        printf("(Sem pacientes cadastrados)\n");
        return;
    }

    for(int i = 0; i < list->size && p != NULL; i++){
        printf("[ID: %d] %s\n", get_patient_id(p->patient), get_patient_name(p->patient));
        p = p->next;
    }
}

bool delete_list(LIST **list){
    NODE *curr = (*list)->head;

    while (curr) {
        NODE *next = curr->next;
        if (curr->patient != NULL) {
            delete_patient(&(curr->patient));
        }
        free(curr);
        curr = next;
    }

    free(*list);

    *list = NULL;

    return true;
}

