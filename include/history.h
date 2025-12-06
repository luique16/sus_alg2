#ifndef HISTORY_H
    #define HISTORY_H

    #include <stdbool.h>

    typedef struct _history HISTORY;

    HISTORY* init_history();
    bool load_history(HISTORY *history, char *text);
    char* save_history(HISTORY *history);
    bool is_history_empty(HISTORY *history);
    bool is_history_full(HISTORY *history);
    void add_procedure_to_history(HISTORY *history, char *procedure);
    char* get_last_procedure(HISTORY *history);
    void pop_last_procedure(HISTORY *history);
    bool delete_history(HISTORY **history);
    void print_history(HISTORY *history);
#endif
