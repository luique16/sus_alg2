#ifndef QUEUE_H
    #define QUEUE_H
    #include <stdbool.h>
    #include "patient.h"

    typedef struct _queue QUEUE;

    QUEUE* init_queue();
    bool enqueue(QUEUE *queue, PATIENT *patient);
    PATIENT* dequeue(QUEUE *queue);
    void delete_queue(QUEUE **queue);
    void print_queue(QUEUE *queue);
    bool is_queue_empty(QUEUE *queue);
    bool is_queue_full(QUEUE *queue);
    int get_queue_size(QUEUE *queue);
#endif
