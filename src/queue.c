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

// Fila de prioridade simplesmente encadeada e com limite de tamanho

/*
    @brief inicia a fila
    @return fila criada
*/
QUEUE* init_queue(){
    QUEUE *queue = (QUEUE*) calloc(1, sizeof(QUEUE));
    queue->size = 0;
    queue->head = NULL;

    return queue;
}

/*
    @brief fila esta vazia
    @param queue fila de pacientes
    @return true se estiver vazia, false se nao estiver vazia
*/
bool is_queue_empty(QUEUE *queue){
    return queue->size == 0;
}

/*
    @brief insercao ordenada com base no level do paciente
    @param queue fila de pacientes
    @param level nivel de prioridade
    @return true se inseriu, false se houve erro
*/
bool enqueue(QUEUE *queue, PATIENT *patient, int level){
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
    } else if (level < queue->head->level) { // Se o level for menor que o do primeiro elemento da fila
        n->next = queue->head;
        queue->head = n;
    } else {
        NODE *p = queue->head;
        while (p->next != NULL && p->next->level <= level) { // Procura o local para inserir o paciente
            p = p->next;
        }

        n->next = p->next;
        p->next = n;
    }

    queue->size += 1;
    return true;
}

/*
    @brief busca o tamanho da fila
    @param queue fila de pacientes
    @return tamanho da fila
*/
int get_queue_size(QUEUE *queue){
    return queue->size;
}

/*
    @brief Busca se um paciente esta na fila
    @param queue fila de pacientes
    @param id id do paciente a ser buscado
    @return true se o paciente esta na fila, false caso contrario
*/
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

/*
    @brief tira um paciente da fila
    @param queue fila de pacientes
    @return ponteiro para o paciente removido
*/
PATIENT* dequeue(QUEUE *queue){
    if (queue == NULL || queue->head == NULL) return NULL;

    NODE *n = queue->head;
    PATIENT *p = n->patient;

    queue->head = n->next;

    queue->size -= 1;
    free(n);

    return p;
}

/*
    @brief busca o level da primeira pessoa na fila
    @param queue fila de pacientes
    @return level do primeiro da fila
*/
int get_next_level(QUEUE *queue){
    if(is_queue_empty(queue) || queue->head == NULL){
        return 0;
    }

    return queue->head->level;
}
 
/*
    @brief printa a fila
    @param queue fila de pacientes
    @return
*/
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

/*
    @brief busca se a fila esta cheia
    @param queue fila de pacientes
    @return false para fila nao cheia, true para fila cheia
*/
bool is_queue_full(QUEUE *queue){
    return queue->size >= DEFAULT_MAX_SIZE;
}

/*
    @brief deleta a fila
    @param queue fila de pacientes
    @return
*/
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

