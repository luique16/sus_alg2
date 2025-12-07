#define DEFAULT_MAX_SIZE 15

#include <stdio.h>
#include <stdlib.h>

#include "../include/queue.h"
#include "../include/patient.h"

typedef struct _node {
    PATIENT *patient;
    int level;
    struct _node *next;
    struct _node *prev;
} NODE;

typedef struct _queue {
    NODE *head;
    NODE *tail;
    int size;
} QUEUE;

QUEUE* init_queue(){
    QUEUE *queue = (QUEUE*) calloc(1, sizeof(QUEUE));
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

bool is_queue_empty(QUEUE *queue){
    return queue->size == 0;
}

bool enqueue(QUEUE *queue, PATIENT *patient, int level){
    if(queue == NULL || queue->size >= DEFAULT_MAX_SIZE){
        return false;
    }

    NODE *n = (NODE*) calloc(1, sizeof(NODE));
    n->patient = patient;
    n->level = level;
    n->next = NULL;
    
    if(is_queue_empty(queue)){
        queue->head = n;
        n->prev = NULL;
    }else {
        n->prev = queue->tail;
        queue->tail->next = n;
    }
    queue->tail = n;
    queue->size += 1;
    
    return true;
}

int get_queue_size(QUEUE *queue){
    return queue->size;
}

PATIENT* dequeue(QUEUE *queue){
    if (queue == NULL || queue->head == NULL) return NULL;

    NODE *n = queue->head;
    PATIENT *p = n->patient;

    queue->head = n->next;
    if (queue->head != NULL)
        queue->head->prev = NULL;
    else
        queue->tail = NULL;

    queue->size -= 1;
    free(n);

    return p;
}

int get_next_level(QUEUE *queue){
    if(is_queue_empty(queue) || queue->head == NULL){
        return 0;
    }

    return queue->head->level;
}
 
void print_queue(QUEUE *queue){
    if(is_queue_empty(queue)) {
        printf("(Sem pacientes na fila)\n");
        return;
    }

    NODE *p = queue->head;

    for(int i = 0; i < queue->size; i++){
        printf("[%d] %s\n", i + 1, get_patient_name(p->patient));
        p = p->next;
        if(p == NULL){
            break;
        }
    }
}

bool is_queue_full(QUEUE *queue){
    return queue->size >= DEFAULT_MAX_SIZE;
}

void delete_queue(QUEUE **queue){
    if (queue == NULL || *queue == NULL) return;

    NODE *curr = (*queue)->head;

    while (curr) {
        NODE *next = curr->next;
        free(curr);
        curr = next;
    }

    free(*queue);
    *queue = NULL;
}

