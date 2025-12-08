#define DEFAULT_MAX_SIZE 15

#include <stdio.h>
#include <stdlib.h>

#include "../include/queue.h"
#include "../include/patient.h"

typedef struct _node {
    PATIENT *patient;
    int level;
    struct _node *next;
} NODE;

typedef struct _queue {
    NODE *head;
    int size;
} QUEUE;

QUEUE* init_queue(){
    QUEUE *queue = (QUEUE*) calloc(1, sizeof(QUEUE));
    queue->size = 0;
    queue->head = NULL;

    return queue;
}

bool is_queue_empty(QUEUE *queue){
    return queue->size == 0;
}

bool enqueue(QUEUE *queue, PATIENT *patient, int level){    //A insercao e feita ordenadamente de acordo com a prioridade (level)
    if (queue == NULL || queue->size >= DEFAULT_MAX_SIZE) {
        return false;
    }

    NODE *n = calloc(1, sizeof(NODE));
    if (!n) return false;
    n->patient = patient;
    n->level = level;
    n->next = NULL;

    if (queue->head == NULL) {
        queue->head = n;
    } else if (level < queue->head->level) {
        n->next = queue->head;
        queue->head = n;
    } else {
        NODE *p = queue->head;
        while (p->next != NULL && p->next->level <= level) {
            p = p->next;
        }

        n->next = p->next;
        p->next = n;
    }

    queue->size += 1;
    return true;
}

int get_queue_size(QUEUE *queue){
    return queue->size;
}

bool is_patient_in_queue(QUEUE *queue, int id){ //busca sequencial
    if(is_queue_empty(queue)){
        return false;
    }

    NODE *p = queue->head;

    while(p != NULL){
        if(get_patient_id(p->patient) == id){
            return true;
        }

        p = p->next;
    }

    return false;
}

PATIENT* dequeue(QUEUE *queue){
    if (queue == NULL || queue->head == NULL) return NULL;

    NODE *n = queue->head;
    PATIENT *p = n->patient;

    queue->head = n->next;

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
    int i = 0;

    while(p != NULL){
        printf("[%d] %s [nível %d]\n", i + 1, get_patient_name(p->patient), p->level);
        p = p->next;
        i += 1;
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

