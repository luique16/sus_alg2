#ifndef IO_H
    #define IO_H
    #include <stdbool.h>

    #include "list.h"
    #include "queue.h"

    bool save(LIST *list, QUEUE *queue, char *list_filename, char *queue_filename);
    bool load(LIST **list, QUEUE **queue, char *list_filename, char *queue_filename);
    void flush(void);
#endif
