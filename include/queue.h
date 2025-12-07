#ifndef QUEUE_H
    #define QUEUE_H
    #include <stdbool.h>
    #include "patient.h"

    typedef struct _queue QUEUE;

    QUEUE* init_queue();
    bool enqueue(QUEUE *queue, PATIENT *patient, int level);
    PATIENT* dequeue(QUEUE *queue);
    int get_next_level(QUEUE *queue);
    bool is_patient_in_queue(QUEUE *queue, int id);
    void delete_queue(QUEUE **queue);
    void print_queue(QUEUE *queue);
    bool is_queue_empty(QUEUE *queue);
    bool is_queue_full(QUEUE *queue);
    int get_queue_size(QUEUE *queue);
#endif
